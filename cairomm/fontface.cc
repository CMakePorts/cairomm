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

#include <cairomm/fontface.h>
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


} //namespace Cairo

// vim: ts=2 sw=2 et
