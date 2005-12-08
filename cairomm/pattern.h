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

#ifndef __CAIROMM_PATTERN_H
#define __CAIROMM_PATTERN_H

#include <cairomm/surface.h>
#include <cairomm/enums.h>
#include <cairo/cairo.h>


namespace Cairo
{

typedef cairo_extend_t Extend;
typedef cairo_filter_t Filter;

/**
 * This is a reference-counted object. The copy constructor creates a second reference to the object, instead 
 * of creating an independent copy of the object.
 */
class Pattern
{
public:
  //Use derived constructors.

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit Pattern(cairo_pattern_t* cobject, bool has_reference = false);

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  Pattern(const Pattern& src);

  //TODO?: Pattern(cairo_pattern_t *target);
  virtual ~Pattern();

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  Pattern& operator=(const Pattern& src);

  void set_matrix(const cairo_matrix_t &matrix);
  void get_matrix(cairo_matrix_t &matrix) const;

  typedef cairo_pattern_t cobject;
  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline Status get_status() const
  { return cairo_pattern_status(const_cast<cairo_pattern_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

protected:
  //Used by derived types only.
  Pattern();

  cobject* m_cobject;
};

class SolidPattern : public Pattern
{
public:

  static SolidPattern create_rgb(double red, double green, double blue);
  static SolidPattern create_rgba(double red, double green, double blue, double alpha);

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit SolidPattern(cairo_pattern_t* cobject, bool has_reference = false);

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  SolidPattern(const SolidPattern& src);

  //TODO?: SolidPattern(cairo_pattern_t *target);
  virtual ~SolidPattern();

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  SolidPattern& operator=(const SolidPattern& src);
};

class SurfacePattern : public Pattern
{
public:

  explicit SurfacePattern(Surface& surface);

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit SurfacePattern(cairo_pattern_t* cobject, bool has_reference = false);

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  SurfacePattern(const SurfacePattern& src);

  //TODO?: SurfacePattern(cairo_pattern_t *target);
  virtual ~SurfacePattern();

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  SurfacePattern& operator=(const SurfacePattern& src);

  void set_extend(Extend extend);
  Extend get_extend() const;
  void set_filter(Filter filter);
  Filter get_filter() const;
};

class Gradient : public Pattern
{
public:
  //Use derived constructors.

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit Gradient(cairo_pattern_t* cobject, bool has_reference = false);

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  Gradient(const Gradient& src);

  //TODO?: Gradient(cairo_pattern_t *target);
  virtual ~Gradient();

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  Gradient& operator=(const Gradient& src);

  void add_color_stop_rgb(double offset, double red, double green, double blue);
  void add_color_stop_rgba(double offset, double red, double green, double blue, double alpha);

protected:
  Gradient();
};

class LinearGradient : public Gradient
{
public:

  LinearGradient(double x0, double y0, double x1, double y1);

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit LinearGradient(cairo_pattern_t* cobject, bool has_reference = false);

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  LinearGradient(const LinearGradient& src);

  //TODO?: LinearGradient(cairo_pattern_t *target);
  virtual ~LinearGradient();

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  LinearGradient& operator=(const LinearGradient& src);
};

class RadialGradient : public Gradient
{
public:

  RadialGradient(double cx0, double cy0, double radius0, double cx1, double cy1, double radius1);

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit RadialGradient(cairo_pattern_t* cobject, bool has_reference = false);

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  RadialGradient(const RadialGradient& src);

  //TODO?: RadialGradient(cairo_pattern_t *target);
  virtual ~RadialGradient();

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  RadialGradient& operator=(const RadialGradient& src);
};

} // namespace Cairo

#endif //__CAIROMM_PATTERN_H

