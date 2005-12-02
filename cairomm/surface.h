#ifndef __CAIROMM_SURFACE_H
#define __CAIROMM_SURFACE_H

#include <cairomm/fontoptions.h>
#include <cairomm/enums.h>
#include <cairo/cairo.h>


namespace Cairo
{

typedef cairo_content_t Content;
typedef cairo_format_t Format;

/** A cairo surface represents an image, either as the destination of a drawing operation or as source when 
 * drawing onto another surface. There are different subtypes of cairo surface for different drawing
 * backends.
 *
 * This is a reference-counted object. The copy constructor creates a second reference to the object, instead of creating an independent copy of the object.
 */
class Surface
{
public:
  Surface();

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit Surface(cairo_surface_t* cobject, bool has_reference = false);

  /** Create a second reference to the surface.
  * Changing this instance will change the original instance.
  */
  Surface(const Surface& src);

  //TODO?: Surface(cairo_surface_t *target);
  virtual ~Surface();

  /** Create a second reference to the surface.
  * Changing this instance will change the original instance.
  */
  Surface& operator=(const Surface& src);

  //We use create_*() methods, instead of constructors, because
  //a) We want to make it clear that these are new instance, not just new references to the same instances.
  //b) Overloading on parameter types are not always enough to distinguish them.
  static Surface create(const Surface& other, Content content, int width, int height);
  static Surface create(Format format, int width, int height);
  static Surface create(unsigned char* data, Format format, int width, int height, int stride);

  //void write_to_png(const std::string& filename);
  //void write_to_png_stream(cairo_write_func_t write_func, void *closure); //TODO: Use a sigc::slot?
  void *get_user_data(const cairo_user_data_key_t *key);

  void set_user_data(const cairo_user_data_key_t *key, void *user_data, cairo_destroy_func_t destroy); //TODO: Use a sigc::slot?

  void get_font_options(FontOptions& options);

  void finish();
  void flush();

  void mark_dirty();
  void mark_dirty(int x, int y, int width, int height);

  void set_device_offset(double x_offset, double y_offset);

  int get_width() const;
  int get_height() const;

  void create_from_png(const char* filename);
  void create_from_png_stream(cairo_read_func_t read_func, void *closure);

  typedef cairo_surface_t cobject;
  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline Status get_status() const
  { return cairo_surface_status(const_cast<cairo_surface_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

protected:
  cobject* m_cobject;
};

} // namespace Cairo

#endif //__CAIROMM_SURFACE_H

