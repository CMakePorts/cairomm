/* Copyright (C) 2010 The cairomm Development Team
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

#ifndef __CAIROMM_REGION_H
#define __CAIROMM_REGION_H

#include <cairomm/types.h>
#include <cairomm/enums.h>
#include <cairomm/refptr.h>
#include <cairo.h>


namespace Cairo
{

//TODO: Documentation.

/**
 * This is a reference-counted object that should be used via Cairo::RefPtr.
 */
class Region
{
public:

  Region();

  explicit Region(const RectangleInt& rectangle);

  //TODO: wrapping cairo_region_create_rectangles()
  //Region(const RectangleInt *rects, int count);

  /** Create a C++ wrapper for the C instance. This C++ instance should then be given to a RefPtr.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit Region(cairo_region_t* cobject, bool has_reference = false);

//TODO:
//cairo_public cairo_region_t *
//cairo_region_copy (const cairo_region_t *original);

  virtual ~Region();

  RectangleInt get_extents() const;

  int get_num_rectangles() const;

  RectangleInt get_rectangle(int nth_rectangle) const;

  bool empty() const;

  RegionOverlap contains_rectangle(const RectangleInt& rectangle) const;

  bool contains_point(int x, int y) const;

  void translate(int dx, int dy);

  void subtract(const RefPtr<Region>& other);

  void subtract(const RectangleInt& rectangle);

  void intersect(const RefPtr<Region>& other);

  void intersect(const RectangleInt& rectangle);

  //We don't call this method union() because that is a C++ keyword.

  void do_union(const RefPtr<Region>& other);

  void do_union(const RectangleInt& rectangle);



  typedef cairo_region_t cobject;

  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline ErrorStatus get_status() const
  { return cairo_region_status(const_cast<cairo_region_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

  void reference() const;
  void unreference() const;

protected:

  cobject* m_cobject;
};

} // namespace Cairo

#endif //__CAIROMM_REGION_H

// vim: ts=2 sw=2 et
