#include <cairomm/pattern.h>
#include <cairomm/private.h>

namespace Cairo
{

Pattern::Pattern(cairo_pattern_t* cobject, bool has_reference)
: m_cobject(0)
{
  if(has_reference)
    m_cobject = cobject;
  else
    m_cobject = cairo_pattern_reference(cobject);
}

Pattern::Pattern(const Pattern& src)
{
  //Reference-counting, instead of copying by value:
  if(!src.m_cobject)
    m_cobject = 0;
  else
    m_cobject = cairo_pattern_reference(src.m_cobject);
}

Pattern::~Pattern()
{
  if(m_cobject)
    cairo_pattern_destroy(m_cobject);
}


Pattern& Pattern::operator=(const Pattern& src)
{
  //Reference-counting, instead of copying by value:

  if(this == &src)
    return *this;

  if(m_cobject == src.m_cobject)
    return *this;

  if(m_cobject)
  {
    cairo_pattern_destroy(m_cobject);
    m_cobject = 0;
  }

  if(!src.m_cobject)
    return *this;

  m_cobject = cairo_pattern_reference(src.m_cobject);

  return *this;
}

Pattern Pattern::create_rgb(double red, double green, double blue)
{
  cairo_pattern_t* cobject = cairo_pattern_create_rgb(red, green, blue);
  return Pattern(cobject, true /* has reference */);
}

Pattern Pattern::create_rgba(double red, double green, double blue, double alpha)
{
  cairo_pattern_t* cobject  = cairo_pattern_create_rgba(red, green, blue, alpha);
  return Pattern(cobject, true /* has reference */);
}

Pattern Pattern::create_for_surface(cairo_surface_t *surface)
{
  cairo_pattern_t* cobject =  cairo_pattern_create_for_surface(surface);
  return Pattern(cobject, true /* has reference */);
}

Pattern Pattern::create_linear(double x0, double y0, double x1, double y1)
{
  cairo_pattern_t* cobject =  cairo_pattern_create_linear(x0, y0, x1, y1);
  return Pattern(cobject, true /* has reference */);
}

Pattern Pattern::create_radial(double cx0, double cy0, double radius0, double cx1, double cy1, double radius1)
{
  cairo_pattern_t* cobject =  cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1);
  return Pattern(cobject, true /* has reference */);
}

void Pattern::add_color_stop_rgb(double offset, double red, double green, double blue)
{
  cairo_pattern_add_color_stop_rgb(m_cobject, offset, red, green, blue);
  check_object_status_and_throw_exception(*this);
}

void Pattern::add_color_stop_rgba(double offset, double red, double green, double blue, double alpha)
{
  cairo_pattern_add_color_stop_rgba(m_cobject, offset, red, green, blue, alpha);
  check_object_status_and_throw_exception(*this);
}

void Pattern::set_matrix(const cairo_matrix_t &matrix)
{
  cairo_pattern_set_matrix(m_cobject, &matrix);
  check_object_status_and_throw_exception(*this);
}

void Pattern::get_matrix(cairo_matrix_t &matrix) const
{
  cairo_pattern_get_matrix(m_cobject, &matrix);
  check_object_status_and_throw_exception(*this);
}

void Pattern::set_extend(Extend extend)
{
  cairo_pattern_set_extend(m_cobject, (cairo_extend_t)extend);
  check_object_status_and_throw_exception(*this);
}

Extend Pattern::get_extend() const
{
  const Extend result = cairo_pattern_get_extend(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

void Pattern::set_filter(Filter filter)
{
  cairo_pattern_set_filter(m_cobject, (cairo_filter_t)filter);
  check_object_status_and_throw_exception(*this);
}

Filter Pattern::get_filter() const
{
  Filter result = cairo_pattern_get_filter(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

} //namespace Cairo
