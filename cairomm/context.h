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
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __CAIROMM_CONTEXT_H
#define __CAIROMM_CONTEXT_H

#include <cairomm/surface.h>
#include <cairomm/fontface.h>
#include <cairomm/pattern.h>
#include <cairomm/path.h>
#include <valarray>
#include <vector>
#include <cairo.h>


namespace Cairo
{

typedef cairo_operator_t Operator;
typedef cairo_fill_rule_t FillRule;
typedef cairo_line_cap_t LineCap;
typedef cairo_line_join_t LineJoin;
typedef cairo_font_slant_t FontSlant;
typedef cairo_font_weight_t FontWeight;

typedef cairo_glyph_t Glyph; //A simple struct.
typedef cairo_font_extents_t FontExtents; //A simple struct.
typedef cairo_text_extents_t TextExtents; //A simple struct.
typedef cairo_matrix_t Matrix; //A simple struct. //TODO: Derive and add operator[] and operator. matrix multiplication?

/** The context is the main object used when drawing with cairo. To draw with cairo, you create a context,  
 * set the target surface, and drawing options for the context, create shapes with methods like move_to() and 
 * line_to(), and then draw shapes with stroke() or fill().
 *
 * This is a reference-counted object. The copy constructor creates a second reference to the object, instead of creating an independent copy of the object.
 *
 * Contexts can be pushed to a stack via save(). They may then safely be changed, without losing the current
 * state. Use restore() to restore to the saved state.
 */
class Context
{
public:
  Context();
  explicit Context(Surface& src);

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit Context(cairo_t* cobject, bool has_reference = false);

  /** Create a second reference to the context.
   * Changing this instance will change the original instance.
   */
  Context(const Context& src);

  //TODO?: Context(cairo_surface_t *target);
  virtual ~Context();

  /** Create a second reference to the context.
   * Changing this instance will change the original instance.
   */
  Context& operator=(const Context& src);

  void save();
  void restore();
  void set_operator(Operator op);
  void set_source(const Pattern& source);
  void set_source_rgb(double red, double green, double blue);
  void set_source_rgba(double red, double green, double blue, double alpha);
  void set_source(Surface& surface, double x, double y);
  void set_tolerance(double tolerance);
  void set_antialias(Antialias antialias);
  void set_fill_rule(FillRule fill_rule);
  void set_line_width(double width);
  void set_line_cap(LineCap line_cap);
  void set_line_join(LineJoin line_join);
  void set_dash(std::valarray<double>& dashes, double offset);
  void set_dash();
  void set_miter_limit(double limit);
  void translate(double tx, double ty);
  void scale(double sx, double sy);
  void rotate(double angle);
  void rotate_deg(double angle);
  void transform(const Matrix& matrix);
  void set_matrix(const Matrix& matrix);
  void identity_matrix();
  void user_to_device(double& x, double& y);
  void user_to_device_distance(double& dx, double& dy);
  void device_to_user(double& x, double& y);
  void device_to_user_distance(double& dx, double& dy);
  void new_path();
  void move_to(double x, double y);
  void line_to(double x, double y);
  void curve_to(double x1, double y1, double x2, double y2, double x3, double y3);
  void arc(double xc, double yc, double radius, double angle1, double angle2);
  void arc_negative(double xc, double yc, double radius, double angle1, double angle2);
  void rel_move_to(double dx, double dy);
  void rel_line_to(double dx, double dy);
  void rel_curve_to(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3);
  void rectangle(double x, double y, double width, double height);
  void close_path();
  void paint();
  void paint_with_alpha(double alpha);
  void mask(Pattern& pattern); //Should the source be const?
  void mask(Surface& surface, double surface_x, double surface_y); //TODO: Should the source be const?
  void stroke();
  void stroke_preserve();
  void fill();
  void fill_preserve();
  void copy_page();
  void show_page();
  bool in_stroke(double x, double y) const;
  bool in_fill(double x, double y) const;
  void get_stroke_extents(double& x1, double& y1, double& x2, double& y2) const;
  void get_fill_extents(double& x1, double& y1, double& x2, double& y2) const;
  void reset_clip();
  void clip();
  void clip_preserve();
  void select_font_face (const std::string& family, FontSlant slant, FontWeight weight);
  void set_font_size(double size);
  void set_font_matrix(const Matrix& matrix);
  void get_font_matrix(Matrix& matrix) const;
  void set_font_options(const FontOptions& options);
  void show_text(const std::string& utf8);
  void show_glyphs(const std::vector<Glyph>& glyphs);
  FontFace get_font_face() const;
  void get_font_extents(FontExtents& extents) const;
  void set_font_face(const FontFace& font_face);
  void get_text_extents(const std::string& utf8, TextExtents& extents) const;
  void get_glyph_extents(const std::vector<Glyph>& glyphs, TextExtents& extents) const;
  void text_path(const std::string& utf8);
  void glyph_path(const std::vector<Glyph>& glyphs); //TODO: Is this an output parameter?
  Operator get_operator() const;
  Pattern get_source() const;
  double get_tolerance() const;
  Antialias get_antialias() const;
  void get_current_point (double& x, double& y) const;
  FillRule get_fill_rule() const;
  double get_line_width() const;
  LineCap get_line_cap() const;
  LineJoin get_line_join() const;

  double get_miter_limit() const;
  void get_matrix(Matrix& matrix);

  Surface get_target();
  const Surface get_target() const;
  
  Path* copy_path() const;
  Path* copy_path_flat() const;

  void append_path(const Path& path);

  typedef cairo_t cobject;
  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }
 
  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline Status get_status() const
  { return cairo_status(const_cast<cairo_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

protected:

 
  cobject* m_cobject;
};

} // namespace Cairo

#endif //__CAIROMM_CONTEXT_H

