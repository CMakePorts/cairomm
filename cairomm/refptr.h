// -*- c++ -*-
#ifndef _cairo_REFPTR_H
#define _cairo_REFPTR_H

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

//TODO: Use std::shared_ptr<> instead when we can break ABI.
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
class RefPtr
{
public:
  // Let the cast constructors and assignement operators access private data.
  template <typename T_CastFrom>
  friend class RefPtr;

  /** Default constructor
   *
   * Afterwards it will be null and use of -> will cause a segmentation fault.
   */
  inline RefPtr() noexcept;
  
  /// Destructor - decrements reference count.
  inline ~RefPtr() noexcept;

  /** For use only in the internal implementation of cairomm, gtkmm, etc.
   *
   * This takes ownership of @a pCppObject, so it will be deleted when the 
   * last RefPtr is deleted, for instance when it goes out of scope.
   *
   * This assumes that @a pCppObject already has a starting reference for its underlying cairo object,
   * so that destruction of @a @pCppObject will cause a corresponding unreference of its underlying 
   * cairo object. For instance, a cairo_*_create() function usually provides a starting reference, 
   * but a cairo_*_get_*() function requires the caller to manually reference the returned object.
   * In this case, you should call reference() on @a pCppObject before passing it to this constructor.
   */
  explicit inline RefPtr(T_CppObject* pCppObject) noexcept;

  ///  For use only in the internal implementation of sharedptr.
  explicit inline RefPtr(T_CppObject* pCppObject, int* refcount) noexcept;

  /** Move constructor
   */
  inline RefPtr(RefPtr&& src) noexcept;

  /** Move constructor (from different, but castable type).
   */
  template <class T_CastFrom>
  inline RefPtr(RefPtr<T_CastFrom>&& src) noexcept;

  /** Copy constructor
   *
   * This increments the shared reference count.
   */
  inline RefPtr(const RefPtr<T_CppObject>& src) noexcept;

  /** Copy constructor (from different, but castable type).
   *
   * Increments the reference count.
   */
  template <class T_CastFrom>
  inline RefPtr(const RefPtr<T_CastFrom>& src) noexcept;

  /** Swap the contents of two RefPtr<>.
   * This method swaps the internal pointers to T_CppObject.  This can be
   * done safely without involving a reference/unreference cycle and is
   * therefore highly efficient.
   */
  inline void swap(RefPtr<T_CppObject>& other) noexcept;

  /// Copy from another RefPtr:
  inline RefPtr<T_CppObject>& operator=(const RefPtr<T_CppObject>& src) noexcept;

  /** Copy from different, but castable type).
   *
   * Increments the reference count.
   */
  template <class T_CastFrom>
  inline RefPtr<T_CppObject>& operator=(const RefPtr<T_CastFrom>& src) noexcept;

  /// Move assignment operator:
  inline RefPtr& operator=(RefPtr&& src) noexcept;

  /// Move assignment operator (from different, but castable type):
  template <class T_CastFrom>
  inline RefPtr& operator=(RefPtr<T_CastFrom>&& src) noexcept;

  /// Tests whether the RefPtr<> point to the same underlying instance.
  inline bool operator==(const RefPtr<T_CppObject>& src) const noexcept;
  
  /// See operator==().
  inline bool operator!=(const RefPtr<T_CppObject>& src) const noexcept;

  /** Dereferencing.
   *
   * Use the methods of the underlying instance like so:
   * <code>refptr->memberfun()</code>.
   */
  inline T_CppObject* operator->() const noexcept;

  /** Test whether the RefPtr<> points to any underlying instance.
   *
   * Mimics usage of ordinary pointers:
   * @code
   *   if (ptr)
   *     do_something();
   * @endcode
   */
  inline explicit operator bool() const noexcept;

  /// Set underlying instance to 0, decrementing reference count of existing instance appropriately.
  inline void clear() noexcept;


  /** Dynamic cast to derived class.
   *
   * The RefPtr can't be cast with the usual notation so instead you can use
   * @code
   *   ptr_derived = RefPtr<Derived>::cast_dynamic(ptr_base);
   * @endcode
   */
  template <class T_CastFrom>
  static inline RefPtr<T_CppObject> cast_dynamic(const RefPtr<T_CastFrom>& src) noexcept;

  /** Static cast to derived class.
   *
   * Like the dynamic cast; the notation is 
   * @code
   *   ptr_derived = RefPtr<Derived>::cast_static(ptr_base);
   * @endcode
   */
  template <class T_CastFrom>
  static inline RefPtr<T_CppObject> cast_static(const RefPtr<T_CastFrom>& src) noexcept;

  /** Cast to non-const.
   *
   * The RefPtr can't be cast with the usual notation so instead you can use
   * @code
   *   ptr_unconst = RefPtr<UnConstType>::cast_const(ptr_const);
   * @endcode
   */
  template <class T_CastFrom>
  static inline RefPtr<T_CppObject> cast_const(const RefPtr<T_CastFrom>& src) noexcept;


#ifndef DOXYGEN_IGNORE_THIS

  // Warning: This is for internal use only.  Do not manually modify the
  // reference count with this pointer.
  inline int* refcount_() const noexcept { return pCppRefcount_; }

#endif // DOXYGEN_IGNORE_THIS

private:
  void unref() noexcept;

  T_CppObject* pCppObject_;
  mutable int* pCppRefcount_;
};


#ifndef DOXYGEN_IGNORE_THIS

// RefPtr<>::operator->() comes first here since it's used by other methods.
// If it would come after them it wouldn't be inlined.

template <class T_CppObject> inline
T_CppObject* RefPtr<T_CppObject>::operator->() const noexcept
{
  return pCppObject_;
}

template <class T_CppObject> inline
RefPtr<T_CppObject>::RefPtr() noexcept
:
  pCppObject_(nullptr),
  pCppRefcount_(nullptr)
{}

template <class T_CppObject> inline
RefPtr<T_CppObject>::~RefPtr() noexcept
{
  unref();
}

template <class T_CppObject> inline
void RefPtr<T_CppObject>::unref() noexcept
{
  if(pCppRefcount_)
  {
    --(*pCppRefcount_);

    if(*pCppRefcount_ == 0)
    {
      if(pCppObject_)
      {
        delete pCppObject_;
        pCppObject_ = nullptr;
      }

      delete pCppRefcount_;
      pCppRefcount_ = nullptr;
    }
  }
}


template <class T_CppObject> inline
RefPtr<T_CppObject>::RefPtr(T_CppObject* pCppObject) noexcept
:
  pCppObject_(pCppObject),
  pCppRefcount_(nullptr)
{
  if(pCppObject)
  {
    pCppRefcount_ = new int;
    *pCppRefcount_ = 1; //This will be decremented in the destructor.
  }
}

//Used by cast_*() implementations:
template <class T_CppObject> inline
RefPtr<T_CppObject>::RefPtr(T_CppObject* pCppObject, int* refcount) noexcept
:
  pCppObject_(pCppObject),
  pCppRefcount_(refcount)
{
  if(pCppObject_ && pCppRefcount_)
    ++(*pCppRefcount_);
}

template <class T_CppObject> inline
RefPtr<T_CppObject>::RefPtr(const RefPtr<T_CppObject>& src) noexcept
:
  pCppObject_ (src.pCppObject_),
  pCppRefcount_(src.pCppRefcount_)
{
  if(pCppObject_ && pCppRefcount_)
    ++(*pCppRefcount_);
}

template <class T_CppObject> inline
RefPtr<T_CppObject>::RefPtr(RefPtr&& src) noexcept
:
  pCppObject_ (src.pCppObject_),
  pCppRefcount_ (src.pCppRefcount_)
{
  src.pCppObject_ = nullptr;
  src.pCppRefcount_ = nullptr;
}

template <class T_CppObject>
  template <class T_CastFrom>
inline
RefPtr<T_CppObject>::RefPtr(RefPtr<T_CastFrom>&& src) noexcept
:
  pCppObject_ (src.pCppObject_),
  pCppRefcount_ (src.pCppRefcount_)
{
  src.pCppObject_ = nullptr;
  src.pCppRefcount_ = nullptr;
}

// The templated ctor allows copy construction from any object that's
// castable.  Thus, it does downcasts:
//   base_ref = derived_ref
template <class T_CppObject>
  template <class T_CastFrom>
inline
RefPtr<T_CppObject>::RefPtr(const RefPtr<T_CastFrom>& src) noexcept
:
  // Without the friend delaration,
  // a different RefPtr<> will not allow us access to pCppObject_.  We need
  // to add a get_underlying() for this, but that would encourage incorrect
  // use, so we use the less well-known operator->() accessor:
  pCppObject_ (src.operator->()),
  pCppRefcount_(src.refcount_())
{
  if(pCppObject_ && pCppRefcount_)
    ++(*pCppRefcount_);
}

template <class T_CppObject> inline
void RefPtr<T_CppObject>::swap(RefPtr<T_CppObject>& other) noexcept
{
  T_CppObject *const temp = pCppObject_;
  int* temp_count = pCppRefcount_; 

  pCppObject_ = other.pCppObject_;
  pCppRefcount_ = other.pCppRefcount_;

  other.pCppObject_ = temp;
  other.pCppRefcount_ = temp_count;
}

template <class T_CppObject> inline
RefPtr<T_CppObject>& RefPtr<T_CppObject>::operator=(const RefPtr<T_CppObject>& src) noexcept
{
  // In case you haven't seen the swap() technique to implement copy
  // assignment before, here's what it does:
  //
  // 1) Create a temporary RefPtr<> instance via the copy ctor, thereby
  //    increasing the reference count of the source object.
  //
  // 2) Swap the internal object pointers of *this and the temporary
  //    RefPtr<>.  After this step, *this already contains the new pointer,
  //    and the old pointer is now managed by temp.
  //
  // 3) The destructor of temp is executed, thereby unreferencing the
  //    old object pointer.
  //
  // This technique is described in Herb Sutter's "Exceptional C++", and
  // has a number of advantages over conventional approaches:
  //
  // - Code reuse by calling the copy ctor.
  // - Strong exception safety for free.
  // - Self assignment is handled implicitely.
  // - Simplicity.
  // - It just works and is hard to get wrong; i.e. you can use it without
  //   even thinking about it to implement copy assignment whereever the
  //   object data is managed indirectly via a pointer, which is very common.

  RefPtr<T_CppObject> temp (src);
  this->swap(temp);
  return *this;
}

template <class T_CppObject> inline
RefPtr<T_CppObject>& RefPtr<T_CppObject>::operator=(RefPtr&& src) noexcept
{
  RefPtr<T_CppObject> temp (std::move(src));
  this->swap(temp);
  src.pCppObject_ = nullptr;
  src.pCppRefcount_ = nullptr;

  return *this;
}

template <class T_CppObject>
  template <class T_CastFrom>
inline
RefPtr<T_CppObject>& RefPtr<T_CppObject>::operator=(RefPtr<T_CastFrom>&& src) noexcept
{
  RefPtr<T_CppObject> temp (std::move(src));
  this->swap(temp);
  src.pCppObject_ = nullptr;
  src.pCppRefcount_ = nullptr;

  return *this;
}

template <class T_CppObject>
  template <class T_CastFrom>
inline
RefPtr<T_CppObject>& RefPtr<T_CppObject>::operator=(const RefPtr<T_CastFrom>& src) noexcept
{
  RefPtr<T_CppObject> temp (src);
  this->swap(temp);
  return *this;
}

template <class T_CppObject> inline
bool RefPtr<T_CppObject>::operator==(const RefPtr<T_CppObject>& src) const noexcept
{
  return (pCppObject_ == src.pCppObject_);
}

template <class T_CppObject> inline
bool RefPtr<T_CppObject>::operator!=(const RefPtr<T_CppObject>& src) const noexcept
{
  return (pCppObject_ != src.pCppObject_);
}

template <class T_CppObject> inline
RefPtr<T_CppObject>::operator bool() const noexcept
{
  return (pCppObject_ != nullptr);
}

template <class T_CppObject> inline
void RefPtr<T_CppObject>::clear() noexcept
{
  RefPtr<T_CppObject> temp; // swap with an empty RefPtr<> to clear *this
  this->swap(temp);
}

template <class T_CppObject>
  template <class T_CastFrom>
inline
RefPtr<T_CppObject> RefPtr<T_CppObject>::cast_dynamic(const RefPtr<T_CastFrom>& src) noexcept
{
  T_CppObject *const pCppObject = dynamic_cast<T_CppObject*>(src.operator->());

  if(pCppObject) //Check whether dynamic_cast<> succeeded so we don't pass a null object with a used refcount:
    return RefPtr<T_CppObject>(pCppObject, src.refcount_());
  else
    return RefPtr<T_CppObject>();
}

template <class T_CppObject>
  template <class T_CastFrom>
inline
RefPtr<T_CppObject> RefPtr<T_CppObject>::cast_static(const RefPtr<T_CastFrom>& src) noexcept
{
  T_CppObject *const pCppObject = static_cast<T_CppObject*>(src.operator->());

  return RefPtr<T_CppObject>(pCppObject, src.refcount_());
}

template <class T_CppObject>
  template <class T_CastFrom>
inline
RefPtr<T_CppObject> RefPtr<T_CppObject>::cast_const(const RefPtr<T_CastFrom>& src) noexcept
{
  T_CppObject *const pCppObject = const_cast<T_CppObject*>(src.operator->());

  return RefPtr<T_CppObject>(pCppObject, src.refcount_());
}

#endif /* DOXYGEN_IGNORE_THIS */

/** @relates Glib::RefPtr */
template <class T_CppObject> inline
void swap(RefPtr<T_CppObject>& lhs, RefPtr<T_CppObject>& rhs) noexcept
{
  lhs.swap(rhs);
}

} // namespace Cairo


#endif /* _cairo_REFPTR_H */

// vim: ts=2 sw=2 et
