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

