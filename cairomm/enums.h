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

#ifndef __CAIROMM_ENUMS_H
#define __CAIROMM_ENUMS_H

#include <cairo.h>

namespace Cairo
{

#ifndef DOXYGEN_IGNORE_THIS
//This is only used internally, but it must be in a public header because we inline some methods.
typedef cairo_status_t ErrorStatus;
#endif //DOXYGEN_IGNORE_THIS

} // namespace Cairo

#endif //__CAIROMM_ENUMS_H

