#ifndef __CAIROMM_PATH_H
#define __CAIROMM_PATH_H

#include <cairomm/enums.h>
#include <string>
#include <cairo/cairo.h>


namespace Cairo
{

/** A data structure for holding a path.
 * Use Context::copy_path() or Context::copy_path_flat() to instantiate a new Path.
 */
class Path
{
public:
  //Path();
  explicit Path(cairo_path_t* cobject, bool take_ownership = false);
  //Path(const Path& src);

  virtual ~Path();

  //Path& operator=(const Path& src);

  //bool operator ==(const Path& src) const;
  //bool operator !=(const Path& src) const;

  typedef cairo_path_t cobject;
  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  //There is no *_status() function for this object:
  //inline Status get_status() const
  //{ return cairo_path_status(const_cast<cairo_path_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

protected:

  cobject* m_cobject;
};

} // namespace Cairo

#endif //__CAIROMM_PATH_H

