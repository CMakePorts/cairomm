/* Copyright (C) 2008 Jonathon Jongsma
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
#ifndef __CAIROMM_MATRIX_H
#define __CAIROMM_MATRIX_H

#include <cairo.h>

namespace Cairo
{
class Matrix : public cairo_matrix_t
{
public:
  Matrix();
  Matrix(double xx, double yx, double xy, double yy, double x0, double y0);

  void init_identity();
  void init_translate(double tx, double ty);
  void init_scale(double sx, double sy);
  void init_rotate(double radians);
  void translate(double tx, double ty);
  void scale(double sx, double sy);
  void rotate(double radians);

  void invert(); // throws exception
  void muiltiply(Matrix& a, Matrix& b); // FIXME: operator*?

  void transform_distance(double& dx, double& dy) const;
  void transform_point(double& x, double& y) const;
};

} // namespace Cairo

#endif // __CAIROMM_MATRIX_H
