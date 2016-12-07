// -*- c++ -*-
#ifndef _cairo_REFPTR_H
#define _cairo_REFPTR_H

#include <memory>

/* $Id: refptr.h,v 1.6 2006-09-27 18:38:57 murrayc Exp $ */

/* Copyright 2005 The cairomm Development Team
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

#include <utility>

namespace Cairo
{

template <class T_CppObject>
void RefPtrDeleter(T_CppObject* object)
{
  if (!object)
    return;

  object->unreference();
}

/** RefPtr<> is a reference-counting shared smartpointer.
 *
 * Reference counting means that a shared reference count is incremented each
 * time a RefPtr is copied, and decremented each time a RefPtr is destroyed,
 * for instance when it leaves its scope. When the reference count reaches
 * zero, the contained object is deleted
 *
 * cairomm uses RefPtr so that you don't need to remember
 * to delete the object explicitly, or know when a method expects you to delete 
 * the object that it returns, and to prevent any need to manually  reference 
 * and unreference() cairo objects.
 */
template <class T_CppObject>
using RefPtr = std::shared_ptr<T_CppObject>;

template <class T_CppObject>
RefPtr<T_CppObject>
make_refptr_for_instance(T_CppObject* object)
{
  return RefPtr<T_CppObject>(object, &RefPtrDeleter<T_CppObject>);
}

} // namespace Cairo

#endif /* _cairo_REFPTR_H */

// vim: ts=2 sw=2 et
