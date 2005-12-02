#ifndef __CAIROMM_FONTFACE_H
#define __CAIROMM_FONTFACE_H

#include <cairomm/enums.h>
#include <cairo/cairo.h>


namespace Cairo
{

/**
 * This is a reference-counted object. The copy constructor creates a second reference to the object, instead 
 * of creating an independent copy of the object.
 */
class FontFace
{
public:
  FontFace();

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit FontFace(cairo_font_face_t* cobject, bool has_reference = false);

  /** Create a second reference to the FontFace.
  * Changing this instance will change the original instance.
  */
  FontFace(const FontFace& src);

  //TODO?: FontFace(cairo_font_face_t *target);
  virtual ~FontFace();

  /** Create a second reference to the FontFace.
  * Changing this instance will change the original instance.
  */
  FontFace& operator=(const FontFace& src);

  void *get_user_data(const cairo_user_data_key_t *key);

  void set_user_data(const cairo_user_data_key_t *key, void *user_data, cairo_destroy_func_t destroy); //TODO: Use a sigc::slot?


  typedef cairo_font_face_t cobject;
  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline Status get_status() const
  { return cairo_font_face_status(const_cast<cairo_font_face_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

protected:

  cobject* m_cobject;
};

} // namespace Cairo

#endif //__CAIROMM_FONTFACE_H

