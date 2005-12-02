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

FontFace::FontFace(const FontFace& src)
{
  //Reference-counting, instead of copying by value:
  if(!src.m_cobject)
    m_cobject = 0;
  else
    m_cobject = cairo_font_face_reference(src.m_cobject);
}

FontFace::~FontFace()
{
  if(m_cobject)
    cairo_font_face_destroy(m_cobject);
}


FontFace& FontFace::operator=(const FontFace& src)
{
  //Reference-counting, instead of copying by value:

  if(this == &src)
    return *this;

  if(m_cobject == src.m_cobject)
    return *this;

  if(m_cobject)
  {
    cairo_font_face_destroy(m_cobject);
    m_cobject = 0;
  }

  if(!src.m_cobject)
    return *this;

  m_cobject = cairo_font_face_reference(src.m_cobject);

  return *this;
}

void* FontFace::get_user_data(const cairo_user_data_key_t *key)
{
  void* result = cairo_font_face_get_user_data(m_cobject, key);
  check_object_status_and_throw_exception(*this);
  return result;
}

void FontFace::set_user_data(const cairo_user_data_key_t* key, void *user_data, cairo_destroy_func_t destroy)
{
  const Status status = (Status)cairo_font_face_set_user_data(m_cobject, key, user_data, destroy);
  check_status_and_throw_exception(status);
}


} //namespace Cairo
