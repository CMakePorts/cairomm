#ifndef __CAIROMM_PRIVATE_H
#define __CAIROMM_PRIVATE_H

#include <cairomm/enums.h>
#include <cairomm/exception.h>
#include <string>


namespace Cairo
{

//We inline this because it is called so often.
inline void check_status_and_throw_exception(Status status)
{
  if(status != CAIRO_STATUS_SUCCESS)
    throw exception(status);
}

template<class T>
void check_object_status_and_throw_exception(const T& object)
{
  //get_status() is normally an inlined member method.
  check_status_and_throw_exception(object.get_status());
}

} // namespace Cairo

#endif //__CAIROMM_PRIVATE_H

