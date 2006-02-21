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

#include <cairomm/xlib_surface.h>
#include <cairomm/private.h>


namespace Cairo
{

#ifdef CAIRO_HAS_XLIB_SURFACE

XlibSurface::XlibSurface(cairo_surface_t* cobject, bool has_reference) :
    Surface(cobject, has_reference)
{}

XlibSurface::~XlibSurface()
{
  // surface is destroyed in base class
}

RefPtr<XlibSurface> XlibSurface::create(Display *dpy, Drawable drawable, Visual *visual, int width, int height)
{
  cairo_surface_t* cobject = cairo_xlib_surface_create(dpy, drawable, visual, width, height);
  check_status_and_throw_exception(cairo_surface_status(cobject));
  return RefPtr<XlibSurface>(new XlibSurface(cobject, true /* has reference */));
}

RefPtr<XlibSurface> XlibSurface::create(Display *dpy, Pixmap bitmap, Screen *screen, int width, int height)
{
  cairo_surface_t* cobject = cairo_xlib_surface_create_for_bitmap(dpy, bitmap, screen, width, height);
  check_status_and_throw_exception(cairo_surface_status(cobject));
  return RefPtr<XlibSurface>(new XlibSurface(cobject, true /* has reference */));
}

void XlibSurface::set_size(int width, int height)
{
  cairo_xlib_surface_set_size(m_cobject, width, height);
  check_object_status_and_throw_exception(*this);
}

void XlibSurface::set_drawable(Drawable drawable, int width, int height)
{
  cairo_xlib_surface_set_drawable(m_cobject, drawable, width, height);
  check_object_status_and_throw_exception(*this);
}

#endif // CAIRO_HAS_XLIB_SURFACE

} //namespace Cairo
