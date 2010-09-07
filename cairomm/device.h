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

#ifndef __CAIROMM_DEVICE_H
#define __CAIROMM_DEVICE_H

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
class Device
{
public:

  /** Create a C++ wrapper for the C instance. This C++ instance should then be given to a RefPtr.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit Device(cairo_device_t* cobject, bool has_reference = false);

  virtual ~Device();

  DeviceType get_type() const;

  //TODO: Documentation.
  void flush();

  //TODO: Documentation.
  void finish();

  typedef cairo_device_t cobject;

  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline ErrorStatus get_status() const
  { return cairo_device_status(const_cast<cairo_device_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

  void reference() const;
  void unreference() const;

protected:

  cobject* m_cobject;
};

} // namespace Cairo

#endif //__CAIROMM_DEVICE_H

// vim: ts=2 sw=2 et
