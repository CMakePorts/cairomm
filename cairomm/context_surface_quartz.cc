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

#include <cairommconfig.h>
#include <cairomm/context_private.h>
#include <cairomm/quartz_surface.h>

namespace Cairo
{

namespace Private
{

RefPtr<Surface> wrap_surface_quartz(cairo_surface_t* surface)
{
#if CAIRO_HAS_QUARTZ_SURFACE
    return make_refptr_for_instance<QuartzSurface>(new QuartzSurface(surface, false /* does not have reference */));
#else
    return make_refptr_for_instance<Surface>(new Surface(surface, false /* does not have reference */));
#endif
}

} // namespace Private

} // namespace Cairo

// vim: ts=2 sw=2 et
