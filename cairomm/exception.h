#ifndef __CAIRO_EXCEPTION_H
#define __CAIRO_EXCEPTION_H

#include <cairomm/enums.h>
#include <exception>

namespace Cairo
{

typedef cairo_status_t Status;

/** Base class for all cairo exceptions.
 */
class exception: public std::exception
{
public:
  explicit exception(Status status);
  virtual ~exception() throw();

  virtual const char* what() const throw();

private:
  Status m_status;
};

} // namespace xmlpp

#endif // __CAIRO_EXCEPTION_H
