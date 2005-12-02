#include <cairomm/path.h>
#include <cairomm/private.h>
#include <iostream>

namespace Cairo
{

/*
Path::Path()
: m_cobject(0)
{
  m_cobject = cairo_path_create();
}
*/

Path::Path(cairo_path_t* cobject, bool take_ownership)
: m_cobject(0)
{
  if(take_ownership)
    m_cobject = cobject;
  else
  {
    std::cerr << "cairomm: Path::Path(): copying of the underlying cairo_path_t* is not yet implemented." << std::endl;
    //m_cobject = cairo_path_copy(cobject);
  }
}

/*
Path::Path(const Path& src)
{
  //Reference-counting, instead of copying by value:
  if(!src.m_cobject)
    m_cobject = 0;
  else
    m_cobject = cairo_path_copy(src.m_cobject);
}
*/

Path::~Path()
{
  if(m_cobject)
    cairo_path_destroy(m_cobject);
}

/*
Path& Path::operator=(const Path& src)
{
  //Reference-counting, instead of copying by value:

  if(this == &src)
    return *this;

  if(m_cobject == src.m_cobject)
    return *this;

  if(m_cobject)
  {
    cairo_path_destroy(m_cobject);
    m_cobject = 0;
  }

  if(!src.m_cobject)
    return *this;

  m_cobject = cairo_path_copy(src.m_cobject);

  return *this;
}
*/

/*
bool Path::operator==(const Path& src) const
{
  return cairo_path_equal(m_cobject, src.cobj());
}
*/

} //namespace Cairo
