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

#include <cairomm/exception.h>

namespace Cairo
{

exception::exception(Status status)
: m_status(status)
{
}

exception::~exception() throw()
{}

const char* exception::what() const throw()
{
  //Hopefully this is a const char* to a static string.
  return cairo_status_to_string((cairo_status_t)m_status);
}

} //namespace xmlpp

