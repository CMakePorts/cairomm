#include <cairomm/context.h>
#include <cairomm/private.h>

namespace Cairo
{

Context::Context(Surface& target)
: m_cobject(0)
{
  m_cobject = cairo_create(target.cobj());
}

Context::Context(cairo_t* cobject, bool has_reference)
: m_cobject(0)
{
  if(has_reference)
    m_cobject = cobject;
  else
    m_cobject = cairo_reference(cobject);
}

Context::Context(const Context& src)
{
  //Reference-counting, instead of copying by value:
  if(!src.m_cobject)
    m_cobject = 0;
  else
    m_cobject = cairo_reference(src.m_cobject);
}

Context::~Context()
{
  if(m_cobject)
    cairo_destroy(m_cobject);
}


Context& Context::operator=(const Context& src)
{
  //Reference-counting, instead of copying by value:

  if(this == &src)
    return *this;

  if(m_cobject == src.m_cobject)
    return *this;

  if(m_cobject)
  {
    cairo_destroy(m_cobject);
    m_cobject = 0;
  }

  if(!src.m_cobject)
    return *this;

  m_cobject = cairo_reference(src.m_cobject);

  return *this;
}


void Context::save()
{
  cairo_save(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::restore()
{
  cairo_restore(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::set_operator(Operator op)
{
  cairo_set_operator(m_cobject, (cairo_operator_t)op);
  check_object_status_and_throw_exception(*this);
}

void Context::set_source(const Pattern& source)
{
  cairo_set_source(m_cobject, const_cast<cairo_pattern_t*>(source.cobj()));
  check_object_status_and_throw_exception(*this);
}

void Context::set_source_rgb(double red, double green, double blue)
{
  cairo_set_source_rgb(m_cobject, red, green, blue);
  check_object_status_and_throw_exception(*this);
}

void Context::set_source_rgba(double red, double green, double blue,
double alpha)
{
  cairo_set_source_rgba(m_cobject, red, green, blue, alpha);
  check_object_status_and_throw_exception(*this);
}

void Context::set_source_surface(Surface& surface, double x, double y)
{
  cairo_set_source_surface(m_cobject, surface.cobj(), x, y);
  check_object_status_and_throw_exception(*this);
}

void Context::set_tolerance(double tolerance)
{
  cairo_set_tolerance(m_cobject, tolerance);
  check_object_status_and_throw_exception(*this);
}

void Context::set_antialias(Antialias antialias)
{
  cairo_set_antialias(m_cobject, (cairo_antialias_t)antialias);
  check_object_status_and_throw_exception(*this);
}

void Context::set_fill_rule(FillRule fill_rule)
{
  cairo_set_fill_rule(m_cobject, (cairo_fill_rule_t)fill_rule);
  check_object_status_and_throw_exception(*this);
}

void Context::set_line_width(double width)
{
  cairo_set_line_width(m_cobject, width);
  check_object_status_and_throw_exception(*this);
}

void Context::set_line_cap(LineCap line_cap)
{
  cairo_set_line_cap(m_cobject, (cairo_line_cap_t)line_cap);
  check_object_status_and_throw_exception(*this);
}

void Context::set_line_join(LineJoin line_join)
{
  cairo_set_line_join(m_cobject, (cairo_line_join_t)line_join);
  check_object_status_and_throw_exception(*this);
}

void Context::set_dash(std::valarray<double>& dashes, double offset)
{
  cairo_set_dash(m_cobject, &dashes[0], dashes.size(), offset);
  check_object_status_and_throw_exception(*this);
}

void Context::set_dash()
{
  cairo_set_dash(m_cobject, 0, 0, 0);
  check_object_status_and_throw_exception(*this);
}

void Context::set_miter_limit(double limit)
{
  cairo_set_miter_limit(m_cobject, limit);
  check_object_status_and_throw_exception(*this);
}

void Context::translate(double tx, double ty)
{
  cairo_translate(m_cobject, tx, ty);
  check_object_status_and_throw_exception(*this);
}

void Context::scale(double sx, double sy)
{
  cairo_scale(m_cobject, sx, sy);
  check_object_status_and_throw_exception(*this);
}

void Context::rotate(double angle)
{
  cairo_rotate(m_cobject, angle);
  check_object_status_and_throw_exception(*this);
}

void Context::rotate_deg(double angle)
{
  cairo_rotate(m_cobject, angle*M_PI/180.0);
  check_object_status_and_throw_exception(*this);
}

void Context::transform(const cairo_matrix_t& matrix)
{
  cairo_transform(m_cobject, &matrix);
  check_object_status_and_throw_exception(*this);
}

void Context::set_matrix(const cairo_matrix_t& matrix)
{
  cairo_set_matrix(m_cobject, &matrix);
  check_object_status_and_throw_exception(*this);
}

void Context::identity_matrix()
{
  cairo_identity_matrix(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::user_to_device(double& x, double& y)
{
  cairo_user_to_device(m_cobject, &x, &y);
  check_object_status_and_throw_exception(*this);
}

void Context::user_to_device_distance(double& dx, double& dy)
{
  cairo_user_to_device_distance(m_cobject, &dx, &dy);
  check_object_status_and_throw_exception(*this);
}

void Context::device_to_user(double& x, double& y)
{
  cairo_device_to_user(m_cobject, &x, &y);
  check_object_status_and_throw_exception(*this);
}

void Context::device_to_user_distance(double& dx, double& dy)
{
  cairo_device_to_user_distance(m_cobject, &dx, &dy);
  check_object_status_and_throw_exception(*this);
}

void Context::new_path()
{
  cairo_new_path(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::move_to(double x, double y)
{
  cairo_move_to(m_cobject, x, y);
  check_object_status_and_throw_exception(*this);
}

void Context::line_to(double x, double y)
{
  cairo_line_to(m_cobject, x, y);
  check_object_status_and_throw_exception(*this);
}

void Context::curve_to(double x1, double y1, double x2, double y2, double x3, double y3)
{
  cairo_curve_to(m_cobject, x1, y1, x2, y2, x3, y3);
  check_object_status_and_throw_exception(*this);
}

void Context::arc(double xc, double yc, double radius, double angle1, double angle2)
{
  cairo_arc(m_cobject, xc, yc, radius, angle1, angle2);
  check_object_status_and_throw_exception(*this);
}

void Context::arc_negative(double xc, double yc, double radius, double angle1, double angle2)
{
  cairo_arc_negative(m_cobject, xc, yc, radius, angle1, angle2);
  check_object_status_and_throw_exception(*this);
}

void Context::rel_move_to(double dx, double dy)
{
  cairo_rel_move_to(m_cobject, dx, dy);
  check_object_status_and_throw_exception(*this);
}

void Context::rel_line_to(double dx, double dy)
{
  cairo_rel_line_to(m_cobject, dx, dy);
  check_object_status_and_throw_exception(*this);
}

void Context::rel_curve_to(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3)
{
  cairo_rel_curve_to(m_cobject, dx1, dy1, dx2, dy2, dx3, dy3);
  check_object_status_and_throw_exception(*this);
}

void Context::rectangle(double x, double y, double width, double height)
{
  cairo_rectangle(m_cobject, x, y, width, height);
  check_object_status_and_throw_exception(*this);
}

void Context::close_path()
{
  cairo_close_path(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::paint()
{
  cairo_paint(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::paint_with_alpha(double alpha)
{
  cairo_paint_with_alpha(m_cobject, alpha);
  check_object_status_and_throw_exception(*this);
}

void Context::mask(Pattern& pattern)
{
  cairo_mask(m_cobject, pattern.cobj());
  check_object_status_and_throw_exception(*this);
}

void Context::mask_surface(Surface& surface, double surface_x, double surface_y)
{
  cairo_mask_surface(m_cobject, surface.cobj(), surface_x, surface_y);
  check_object_status_and_throw_exception(*this);
}

void Context::stroke()
{
  cairo_stroke(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::stroke_preserve()
{
  cairo_stroke_preserve(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::fill()
{
  cairo_fill(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::fill_preserve()
{
  cairo_fill_preserve(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::copy_page()
{
  cairo_copy_page(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::show_page()
{
  cairo_show_page(m_cobject);
  check_object_status_and_throw_exception(*this);
}

bool Context::in_stroke(double x, double y) const
{
  const bool result = cairo_in_stroke(m_cobject, x, y);
  check_object_status_and_throw_exception(*this);
  return result;
}

bool Context::in_fill(double x, double y) const
{
  const bool result = cairo_in_fill(m_cobject, x, y);
  check_object_status_and_throw_exception(*this);
  return result;
}

void Context::stroke_extents(double& x1, double& y1, double& x2, double& y2) const
{
  cairo_stroke_extents(m_cobject, &x1, &y1, &x2, &y2);
  check_object_status_and_throw_exception(*this);
}

void Context::fill_extents(double& x1, double& y1, double& x2, double& y2) const
{
  cairo_fill_extents(m_cobject, &x1, &y1, &x2, &y2);
  check_object_status_and_throw_exception(*this);
}

void Context::reset_clip()
{
  cairo_reset_clip(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::clip()
{
  cairo_clip(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::clip_preserve()
{
  cairo_clip_preserve(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Context::select_font_face (const std::string& family, FontSlant slant, FontWeight weight)
{
  cairo_select_font_face (m_cobject, family.c_str(), (cairo_font_slant_t)slant, (cairo_font_weight_t)weight);
  check_object_status_and_throw_exception(*this);
}

void Context::set_font_size(double size)
{
  cairo_set_font_size(m_cobject, size);
  check_object_status_and_throw_exception(*this);
}

void Context::set_font_matrix(const cairo_matrix_t &matrix)
{
  cairo_set_font_matrix(m_cobject, &matrix);
  check_object_status_and_throw_exception(*this);
}

void Context::get_font_matrix(cairo_matrix_t &matrix) const
{
  cairo_get_font_matrix(m_cobject, &matrix);
  check_object_status_and_throw_exception(*this);
}

void Context::set_font_options(const FontOptions& options)
{
  cairo_set_font_options(m_cobject, options.cobj());
  check_object_status_and_throw_exception(*this);
}

void Context::show_text(const std::string& utf8)
{
  cairo_show_text(m_cobject, utf8.c_str());
  check_object_status_and_throw_exception(*this);
}

void Context::show_glyphs(const std::vector<Glyph>& glyphs)
{
  cairo_show_glyphs(m_cobject, const_cast<cairo_glyph_t*>(&glyphs[0]), glyphs.size());
  check_object_status_and_throw_exception(*this);
}

FontFace Context::get_font_face() const
{
  cairo_font_face_t* cfontface = cairo_get_font_face(m_cobject);
  check_object_status_and_throw_exception(*this);
  return FontFace(cfontface, false /* does not have reference */);
}

void Context::font_extents(FontExtents& extents)
{
  cairo_font_extents(m_cobject, &extents);
  check_object_status_and_throw_exception(*this);
}

void Context::set_font_face(const FontFace& font_face)
{
  cairo_set_font_face(m_cobject, const_cast<cairo_font_face_t*>(font_face.cobj()));
  check_object_status_and_throw_exception(*this);
}

void Context::text_extents(const std::string& utf8, TextExtents& extents)
{
  cairo_text_extents(m_cobject, utf8.c_str(), &extents);
  check_object_status_and_throw_exception(*this);
}

void Context::glyph_extents(const std::vector<Glyph>& glyphs, TextExtents& extents) const
{
  cairo_glyph_extents(m_cobject, const_cast<cairo_glyph_t*>(&glyphs[0]), glyphs.size(), &extents);
  check_object_status_and_throw_exception(*this);
}

void Context::text_path(const std::string& utf8)
{
  cairo_text_path(m_cobject, utf8.c_str());
  check_object_status_and_throw_exception(*this);
}

void Context::glyph_path(const std::vector<Glyph>& glyphs)
{
  cairo_glyph_path(m_cobject, const_cast<cairo_glyph_t*>(&glyphs[0]), glyphs.size());
  check_object_status_and_throw_exception(*this);
}

Operator Context::get_operator() const
{
  const Operator result = cairo_get_operator(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

Pattern Context::get_source() const
{
  cairo_pattern_t* pattern = cairo_get_source(m_cobject);
  check_object_status_and_throw_exception(*this);
  return Pattern(pattern, false /* does not have reference */);
}

double Context::get_tolerance() const
{
  const double result = cairo_get_tolerance(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

Antialias Context::get_antialias() const
{
  const Antialias result = cairo_get_antialias(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

void Context::get_current_point(double& x, double& y) const
{
  cairo_get_current_point(m_cobject, &x, &y);
  check_object_status_and_throw_exception(*this);
}

FillRule Context::get_fill_rule() const
{
  const FillRule result = cairo_get_fill_rule(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

double Context::get_line_width() const
{
  const double result = cairo_get_line_width(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

LineCap Context::get_line_cap() const
{
  const LineCap result = cairo_get_line_cap(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

LineJoin Context::get_line_join() const
{
  const LineJoin result = cairo_get_line_join(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

double Context::get_miter_limit() const
{
  const double result = cairo_get_miter_limit(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

void Context::get_matrix(cairo_matrix_t &matrix)
{
  cairo_get_matrix(m_cobject, &matrix);
  check_object_status_and_throw_exception(*this);
}

Surface Context::get_target()
{
  cairo_surface_t* surface = cairo_get_target(m_cobject);
  check_object_status_and_throw_exception(*this);
  return Surface(surface, false /* does not have reference */);
}

const Surface Context::get_target() const
{
  cairo_surface_t* surface = cairo_get_target(const_cast<cairo_t*>(m_cobject));
  check_object_status_and_throw_exception(*this);
  return Surface(surface, false /* does not have reference */);
}

Path* Context::copy_path() const
{
  cairo_path_t* cresult = cairo_copy_path(const_cast<cairo_t*>(m_cobject));
  check_object_status_and_throw_exception(*this);
  return new Path(cresult, true /* take ownership */); //The caller must delete it.
}

Path* Context::copy_path_flat() const
{
  cairo_path_t* cresult = cairo_copy_path_flat(const_cast<cairo_t*>(m_cobject));
  check_object_status_and_throw_exception(*this);
  return new Path(cresult, true /* take ownership */); //The caller must delete it.
}

//TODO: Should this be const? Does cairo_append_path() take ownership?
void Context::append_path(const Path& path)
{
  cairo_append_path(m_cobject, const_cast<cairo_path_t*>(path.cobj()));
  check_object_status_and_throw_exception(*this);
}

} //namespace Cairo
