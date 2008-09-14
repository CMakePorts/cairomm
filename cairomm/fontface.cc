/* Copyright (C) 2005 The cairomm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <iostream>
#include <cairomm/context.h>
#include <cairomm/fontface.h>
#include <cairomm/scaledfont.h>
#include <cairomm/private.h>

namespace Cairo
{

FontFace::FontFace(cairo_font_face_t* cobject, bool has_reference)
: m_cobject(0)
{
  if(has_reference)
    m_cobject = cobject;
  else
    m_cobject = cairo_font_face_reference(cobject);
}

FontFace::~FontFace()
{
  if(m_cobject)
    cairo_font_face_destroy(m_cobject);
}

void FontFace::reference() const
{
 cairo_font_face_reference(m_cobject);
}

void FontFace::unreference() const
{
  cairo_font_face_destroy(m_cobject);
}

/*
void* FontFace::get_user_data(const cairo_user_data_key_t *key)
{
  void* result = cairo_font_face_get_user_data(m_cobject, key);
  check_object_status_and_throw_exception(*this);
  return result;
}

void FontFace::set_user_data(const cairo_user_data_key_t* key, void *user_data, cairo_destroy_func_t destroy)
{
  const ErrorStatus status = (ErrorStatus)cairo_font_face_set_user_data(m_cobject, key, user_data, destroy);
  check_status_and_throw_exception(status);
}
*/

FontType FontFace::get_type() const
{
  cairo_font_type_t font_type = cairo_font_face_get_type(m_cobject);
  check_object_status_and_throw_exception(*this);
  return static_cast<FontType>(font_type);
}

// 'Toy' fonts
RefPtr<ToyFontFace>
ToyFontFace::create(const std::string& family, FontSlant slant, FontWeight weight)
{
  return RefPtr<ToyFontFace>(new ToyFontFace(family, slant, weight));
}

ToyFontFace::ToyFontFace(const std::string& family, FontSlant slant, FontWeight weight) :
  FontFace(cairo_toy_font_face_create (family.c_str(),
                                       static_cast<cairo_font_slant_t>(slant),
           	                            static_cast<cairo_font_weight_t>(weight)),
           true /* has reference*/)
{
  check_status_and_throw_exception(cairo_font_face_status(m_cobject));
}

std::string ToyFontFace::get_family() const
{
  return std::string(cairo_toy_font_face_get_family(m_cobject));
}

FontSlant ToyFontFace::get_slant() const
{
  return FontSlant(cairo_toy_font_face_get_slant(m_cobject));
}

FontWeight ToyFontFace::get_weight() const
{
  return FontWeight(cairo_toy_font_face_get_weight(m_cobject));
}


//*************************//
// UserFont Implementation //
//*************************//
//This is defined here, so we can change it later without breaking public ABI.
class UserFontFace::PrivateData
{
public:
  SlotInit m_init_slot;
  SlotUnicodeToGlyph m_unicode_to_glyph_slot;
  SlotRenderGlyph m_render_glyph_slot;
  SlotTextToGlyphs m_text_to_glyphs_slot;
};

static const cairo_user_data_key_t user_font_key = {0};

static void
log_uncaught_exception(const char* message = 0)
{
  std::cerr << "*** cairomm: Uncaught exception in slot callback";
  if(message)
    std::cerr << ": " << message;

  std::cerr << std::endl;
}

cairo_status_t
UserFontFace::init_cb(cairo_scaled_font_t* scaled_font,
                       cairo_t *cr,
                       cairo_font_extents_t* metrics)
{
  cairo_font_face_t* face = cairo_scaled_font_get_font_face(scaled_font);
  // we've stored a pointer to the wrapper object in the C object's user_data
  UserFontFace* instance =
    static_cast<UserFontFace*>(cairo_font_face_get_user_data(face,
                                                             &user_font_key));

  if(instance && instance->m_priv && instance->m_priv->m_init_slot)
  {
    try
    {
      return (instance->m_priv->m_init_slot)(RefPtr<ScaledFont>(new ScaledFont(scaled_font)),
                                              RefPtr<Context>(new Context(cr)),
                                              static_cast<FontExtents&>(*metrics));
    }
    catch(const std::exception& ex)
    {
      log_uncaught_exception(ex.what());
    }
    catch( ... )
    {
      log_uncaught_exception();
    }
  }

  // this should never happen
  return CAIRO_STATUS_USER_FONT_ERROR;
}

cairo_status_t
UserFontFace::unicode_to_glyph_cb(cairo_scaled_font_t *scaled_font,
                                   unsigned long        unicode,
                                   unsigned long       *glyph)
{
  cairo_font_face_t* face = cairo_scaled_font_get_font_face(scaled_font);
  // we've stored a pointer to the wrapper object in the C object's user_data
  UserFontFace* instance =
    static_cast<UserFontFace*>(cairo_font_face_get_user_data(face,
                                                             &user_font_key));
  if(instance && instance->m_priv && instance->m_priv->m_unicode_to_glyph_slot)
  {
    try
    {
      return (instance->m_priv->m_unicode_to_glyph_slot)(RefPtr<ScaledFont>(new ScaledFont(scaled_font)),
                                                          unicode, *glyph);
    }
    catch(const std::exception& ex)
    {
      log_uncaught_exception(ex.what());
    }
    catch( ... )
    {
      log_uncaught_exception();
    }
  }

  // this should never happen
  return CAIRO_STATUS_USER_FONT_ERROR;
}

cairo_status_t
UserFontFace::text_to_glyphs_cb(cairo_scaled_font_t *scaled_font,
                                 const char *utf8,
                                 int utf8_len,
                                 cairo_glyph_t **glyphs,
                                 int *num_glyphs,
                                 cairo_text_cluster_t **clusters,
                                 int *num_clusters,
                                 cairo_bool_t *backward)
{
  cairo_font_face_t* face = cairo_scaled_font_get_font_face(scaled_font);
  // we've stored a pointer to the wrapper object in the C object's user_data
  UserFontFace* instance =
    static_cast<UserFontFace*>(cairo_font_face_get_user_data(face,
                                                             &user_font_key));

  if(instance && instance->m_priv && instance->m_priv->m_text_to_glyphs_slot)
  {
    try
    {
      std::vector<Glyph> glyph_v;
      std::vector<TextCluster> cluster_v;
      const std::string utf8_str(utf8, utf8 + utf8_len);
      bool local_backwards = false;

      ErrorStatus status =
        (instance->m_priv->m_text_to_glyphs_slot)(RefPtr<ScaledFont>(new
                                                                      ScaledFont(scaled_font)),
                                                   utf8_str,
                                                   glyph_v,
                                                   cluster_v,
                                                   local_backwards);

      // TODO: we re-allocate a new array and pass it back to the caller since
      // cairo will free the the returned array.  It sucks to do this excessive
      // allocation and copying, I don't see much alternative besides just
      // presenting a plain-C API.  If cairo didn't free the list, we could
      // possibly just pass back a .data() pointer or something...
      if(num_glyphs && glyphs)
      {
        *num_glyphs = glyph_v.size();
        if(!glyph_v.empty())
        {
          *glyphs = cairo_glyph_allocate(glyph_v.size());
          std::copy(glyph_v.begin(), glyph_v.end(), *glyphs);
        }
      }
      else
        return CAIRO_STATUS_USER_FONT_ERROR;

      // TODO: same for clusters
      if(num_clusters && clusters)
      {
        *num_clusters = cluster_v.size();
        if(!cluster_v.empty())
        {
          *clusters = cairo_text_cluster_allocate(cluster_v.size());
          std::copy(cluster_v.begin(), cluster_v.end(), *clusters);
        }
      }

      if(backward)
        *backward = local_backwards;

      return status;
    }
    catch(const std::exception& ex)
    {
      log_uncaught_exception(ex.what());
    }
    catch( ... )
    {
      log_uncaught_exception();
    }
  }

  // this should never happen
  return CAIRO_STATUS_USER_FONT_ERROR;
}

cairo_status_t
UserFontFace::render_glyph_cb(cairo_scaled_font_t  *scaled_font,
                               unsigned long         glyph,
                               cairo_t              *cr,
                               cairo_text_extents_t *metrics)
{
  cairo_font_face_t* face = cairo_scaled_font_get_font_face(scaled_font);
  // we've stored a pointer to the wrapper object in the C object's user_data
  UserFontFace* instance =
    static_cast<UserFontFace*>(cairo_font_face_get_user_data(face,
                                                             &user_font_key));
  if(instance && instance->m_priv && instance->m_priv->m_render_glyph_slot)
  {
    try
    {
      return (instance->m_priv->m_render_glyph_slot)(RefPtr<ScaledFont>(new ScaledFont(scaled_font)),
                                                      glyph, RefPtr<Context>(new Context(cr)),
                                                      static_cast<TextExtents&>(*metrics));
    }
    catch(const std::exception& ex)
    {
      log_uncaught_exception(ex.what());
    }
    catch( ... )
    {
      log_uncaught_exception();
    }
  }

  // this should never happen
  return CAIRO_STATUS_USER_FONT_ERROR;
}

RefPtr<UserFontFace> UserFontFace::create()
{
  return RefPtr<UserFontFace>(new UserFontFace());
}

UserFontFace::UserFontFace()
  : FontFace(cairo_user_font_face_create(), true /* has reference */),
    m_priv(new PrivateData())
{
  check_status_and_throw_exception(cairo_font_face_status(m_cobject));

  // store a pointer to the wrapper class in the user-data, so that when one of
  // the callback functions gets called (which has to be a plain-C function so
  // can't be a class member), we can get a reference to the wrapper class
  cairo_font_face_set_user_data(m_cobject, &user_font_key,
                                 (void*)this, (cairo_destroy_func_t) NULL);
}

UserFontFace::~UserFontFace()
{
  delete m_priv;
}

void UserFontFace::set_init_func(const SlotInit& init_func)
{
  if(!m_priv)
    return;

  // copy the new slot
  m_priv->m_init_slot = init_func;

  // register it with cairo
  cairo_user_font_face_set_init_func(cobj(), init_cb);
}

void UserFontFace::set_render_glyph_func(const SlotRenderGlyph& render_glyph_func)
{
  if(!m_priv)
    return;

  // copy the slot
  m_priv->m_render_glyph_slot = render_glyph_func;
  cairo_user_font_face_set_render_glyph_func(cobj(), render_glyph_cb);
}

void UserFontFace::set_unicode_to_glyph_func(const SlotUnicodeToGlyph& unicode_to_glyph_func)
{
  if(!m_priv)
    return;

  // copy the slot
  m_priv->m_unicode_to_glyph_slot = unicode_to_glyph_func;
  cairo_user_font_face_set_unicode_to_glyph_func(cobj(), unicode_to_glyph_cb);
}

void UserFontFace::set_text_to_glyphs_func(const SlotTextToGlyphs& text_to_glyphs_func)
{
  if(!m_priv)
    return;

  // copy the slot
  m_priv->m_text_to_glyphs_slot = text_to_glyphs_func;
  cairo_user_font_face_set_text_to_glyphs_func(cobj(), text_to_glyphs_cb);
}


#ifdef CAIRO_HAS_FT_FONT

RefPtr<FtFontFace>
FtFontFace::create(FT_Face face, int load_flags)
{
  return RefPtr<FtFontFace>(new FtFontFace(face, load_flags));
}

FtFontFace::FtFontFace(FT_Face face, int load_flags) :
  FontFace(cairo_ft_font_face_create_for_ft_face (face, load_flags),
           true /* has reference*/)
{
  check_status_and_throw_exception(cairo_font_face_status(m_cobject));
}

RefPtr<FtFontFace>
FtFontFace::create(FcPattern* pattern)
{
  return RefPtr<FtFontFace>(new FtFontFace(pattern));
}

FtFontFace::FtFontFace(FcPattern* pattern) :
  FontFace(cairo_ft_font_face_create_for_pattern (pattern),
           true /* has reference*/)
{
  check_status_and_throw_exception(cairo_font_face_status(m_cobject));
}

#endif // CAIRO_HAS_FT_FONT

} //namespace Cairo

// vim: ts=2 sw=2 et
