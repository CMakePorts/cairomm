/* Copyright (C) 2008 The cairomm Development Team
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
#ifndef __CAIROMM_TYPES_H
#define __CAIROMM_TYPES_H

#include <cairo.h>

namespace Cairo {
typedef cairo_matrix_t Matrix; //A simple struct. //TODO: Derive and add operator[] and operator. matrix multiplication?
typedef cairo_rectangle_t Rectangle;
typedef cairo_font_extents_t FontExtents; //A simple struct.
typedef cairo_text_extents_t TextExtents; //A simple struct.
typedef cairo_text_cluster_t TextCluster;
typedef cairo_glyph_t Glyph; //A simple struct.

}

#endif // __CAIROMM_TYPES_H
