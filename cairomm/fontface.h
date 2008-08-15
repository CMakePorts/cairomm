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

#ifndef __CAIROMM_FONTFACE_H
#define __CAIROMM_FONTFACE_H

#include <string>
#include <cairomm/enums.h>
#include <cairomm/refptr.h>
#include <sigc++/slot.h>
#include <cairo.h>


namespace Cairo
{

class ScaledFont;
class Context;
typedef cairo_font_extents_t FontExtents; //A simple struct.
typedef cairo_text_extents_t TextExtents; //A simple struct.

/**
 * This is a reference-counted object that should be used via Cairo::RefPtr.
 */
class FontFace
{
protected:

  //TODO?: FontFace(cairo_font_face_t *target);

public:
  /** Create a C++ wrapper for the C instance. This C++ instance should then be given to a RefPtr.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit FontFace(cairo_font_face_t* cobject, bool has_reference = false);


  virtual ~FontFace();

  /* Don't wrap these until we know what they are good for.
  void* get_user_data(const cairo_user_data_key_t *key);

  void set_user_data(const cairo_user_data_key_t *key, void *user_data, cairo_destroy_func_t destroy);
  */

  FontType get_type() const;

  typedef cairo_font_face_t cobject;
  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline ErrorStatus get_status() const
  { return cairo_font_face_status(const_cast<cairo_font_face_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

  void reference() const;
  void unreference() const;

protected:

  cobject* m_cobject;
};


class ToyFontFace : public FontFace
{
public:
  static RefPtr<ToyFontFace> create(const std::string& family, FontSlant slant, FontWeight weight);
  std::string get_family() const;
  FontSlant get_slant() const;
  FontWeight get_weight() const;

protected:
  ToyFontFace(const std::string& family, FontSlant slant, FontWeight weight);
};


class UserFontFace : public FontFace
{
public:
  static RefPtr<UserFontFace> create();

  typedef sigc::slot<ErrorStatus,
                     const RefPtr<ScaledFont>&,
                     const RefPtr<Context>&,
                     FontExtents&> SlotInit;
  typedef sigc::slot<ErrorStatus,
                     const RefPtr<ScaledFont>&,
                     unsigned long /*unicode*/,
                     unsigned long& /*glyph*/> SlotUnicodeToGlyph;
  typedef sigc::slot<ErrorStatus,
                     const RefPtr<ScaledFont>&,
                     unsigned long /*glyph*/,
                     const RefPtr<Context>&,
                     TextExtents& /*metrics*/> SlotRenderGlyph;
  // FIXME: add SlotTextToGlyphs

  void set_init_func(const SlotInit& init_func);
  void set_render_glyph_func(const SlotRenderGlyph& render_glyph_func);
  void set_unicode_to_glyph_func(const SlotUnicodeToGlyph& unicode_to_glyph_func);
  // FIXME: add set_text_to_glyphs_func

  // FIXME: are these really useful?  What would you do with a sigc::slot when
  // you got it?
  const SlotInit* get_init_func() const;
  const SlotRenderGlyph* get_render_glyph_func() const;
  const SlotUnicodeToGlyph* get_unicode_to_glyph_func() const;
  // FIXME: add get_text_to_glyphs_func


  virtual ~UserFontFace();

protected:
  UserFontFace();

private:
  struct PrivateData;
  PrivateData* m_priv;

static cairo_status_t
init_cb(cairo_scaled_font_t* scaled_font,
        cairo_t *cr,
        cairo_font_extents_t* metrics);

static cairo_status_t
unicode_to_glyph_cb(cairo_scaled_font_t *scaled_font,
                    unsigned long        unicode,
                    unsigned long       *glyph);

static cairo_status_t
render_glyph_cb(cairo_scaled_font_t  *scaled_font,
                unsigned long         glyph,
                cairo_t              *cr,
                cairo_text_extents_t *metrics);
};

} // namespace Cairo

#endif //__CAIROMM_FONTFACE_H

// vim: ts=2 sw=2 et
