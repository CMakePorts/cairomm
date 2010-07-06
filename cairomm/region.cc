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

#include <cairomm/region.h>
#include <cairomm/private.h>

namespace Cairo
{

Region::Region()
: m_cobject(cairo_region_create())
{
}

Region::Region(const RectangleInt& rectangle)
: m_cobject(cairo_region_create_rectangle(&rectangle))
{
}

Region::Region(cairo_region_t* cobject, bool has_reference)
: m_cobject(0)
{
  if(has_reference)
    m_cobject = cobject;
  else
    m_cobject = cairo_region_reference(cobject);
}

Region::~Region()
{
  if(m_cobject)
    cairo_region_destroy(m_cobject);
}

void Region::reference() const
{
 cairo_region_reference(m_cobject);
}

void Region::unreference() const
{
  cairo_region_destroy(m_cobject);
}

RectangleInt Region::get_extents() const
{
  RectangleInt result;
  cairo_region_get_extents(m_cobject, &result);
  return result;
}

int Region::get_num_rectangles() const
{
  return cairo_region_num_rectangles(m_cobject);
}

RectangleInt Region::get_rectangle(int nth_rectangle) const
{
  RectangleInt result;
  cairo_region_get_rectangle(m_cobject, nth_rectangle, &result);
  return result;
}

bool Region::empty() const
{
  return cairo_region_is_empty(m_cobject);
}

RegionOverlap Region::contains_rectangle(const RectangleInt& rectangle) const
{
  return (RegionOverlap)cairo_region_contains_rectangle(m_cobject, &rectangle);
}

bool Region::contains_point(int x, int y) const
{
  return cairo_region_contains_point(m_cobject, x, y);
}

void Region::translate(int dx, int dy)
{
  cairo_region_translate(m_cobject, dx, dy);
}

ErrorStatus Region::subtract(const RefPtr<Region>& other)
{
  return cairo_region_subtract(m_cobject, (other ? other->cobj() : 0));
}

ErrorStatus Region::subtract(const RectangleInt& rectangle)
{
  return cairo_region_subtract_rectangle(m_cobject, &rectangle);
}

ErrorStatus Region::intersect(const RefPtr<Region>& other)
{
  return cairo_region_intersect(m_cobject, (other ? other->cobj() : 0));
}

ErrorStatus Region::intersect(const RectangleInt& rectangle)
{
  return cairo_region_intersect_rectangle(m_cobject, &rectangle);
}

ErrorStatus Region::do_union(const RefPtr<Region>& other)
{
  return cairo_region_union(m_cobject, (other ? other->cobj() : 0));
}

ErrorStatus Region::do_union(const RectangleInt& rectangle)
{
  return cairo_region_union_rectangle(m_cobject, &rectangle);
}


} //namespace Cairo

// vim: ts=2 sw=2 et
