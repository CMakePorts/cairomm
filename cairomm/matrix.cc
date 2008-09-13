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
#include <cairomm/matrix.h>
#include <cairomm/private.h>

namespace Cairo
{

Matrix::Matrix()
{
  init_identity();
}

Matrix::Matrix(double xx, double yx, double xy, double yy, double x0, double y0)
{
  cairo_matrix_init(this, xx, yx, xy, yy, x0, y0);
}

void Matrix::init_identity()
{
  cairo_matrix_init_identity(this);
}

void Matrix::init_translate(double tx, double ty)
{
  cairo_matrix_init_translate(this, tx, ty);
}

void Matrix::init_scale(double sx, double sy)
{
  cairo_matrix_init_scale(this, sx, sy);
}

void Matrix::init_rotate(double radians)
{
  cairo_matrix_init_rotate(this, radians);
}

void Matrix::translate(double tx, double ty)
{
  cairo_matrix_translate(this, tx, ty);
}

void Matrix::scale(double sx, double sy)
{
  cairo_matrix_scale(this, sx, sy);
}

void Matrix::rotate(double radians)
{
  cairo_matrix_rotate(this, radians);
}

void Matrix::invert()
{
  cairo_status_t status = cairo_matrix_invert(this);
  check_status_and_throw_exception(status);
}

// throws exception
void Matrix::muiltiply(Matrix& a, Matrix& b)
{
  cairo_matrix_multiply(this, &a, &b);
}

void Matrix::transform_distance(double& dx, double& dy) const
{
  cairo_matrix_transform_distance(this, &dx, &dy);
}

void Matrix::transform_point(double& x, double& y) const
{
  cairo_matrix_transform_point(this, &x, &y);
}

} // namespace Cairo
