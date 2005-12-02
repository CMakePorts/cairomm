#ifndef __CAIROMM_PATTERN_H
#define __CAIROMM_PATTERN_H

#include <cairomm/enums.h>
#include <cairo/cairo.h>


namespace Cairo
{

typedef cairo_extend_t Extend;
typedef cairo_filter_t Filter;

/**
 * This is a reference-counted object. The copy constructor creates a second reference to the object, instead 
 * of creating an independent copy of the object.
 */
class Pattern
{
public:
  Pattern();

  /** Create a C++ wrapper for the C instance.
   * @param cobject The C instance.
   * @param has_reference Whether we already have a reference. Otherwise, the constructor will take an extra reference.
   */
  explicit Pattern(cairo_pattern_t* cobject, bool has_reference = false);

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  Pattern(const Pattern& src);

  //TODO?: Pattern(cairo_pattern_t *target);
  virtual ~Pattern();

  /** Create a second reference to the Pattern.
  * Changing this instance will change the original instance.
  */
  Pattern& operator=(const Pattern& src);

  static Pattern create_rgb(double red, double green, double blue);
  static Pattern create_rgba(double red, double green, double blue, double alpha);

  static Pattern create_for_surface(cairo_surface_t *surface);
  static Pattern create_linear(double x0, double y0, double x1, double y1);
  static Pattern create_radial(double cx0, double cy0, double radius0, double cx1, double cy1, double radius1);

  void add_color_stop_rgb(double offset, double red, double green, double blue);
  void add_color_stop_rgba(double offset, double red, double green, double blue, double alpha);
  void set_matrix(const cairo_matrix_t &matrix);
  void get_matrix(cairo_matrix_t &matrix) const;
  void set_extend(Extend extend);
  Extend get_extend() const;
  void set_filter(Filter filter);
  Filter get_filter() const;

  typedef cairo_pattern_t cobject;
  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline Status get_status() const
  { return cairo_pattern_status(const_cast<cairo_pattern_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

protected:
  cobject* m_cobject;
};

} // namespace Cairo

#endif //__CAIROMM_PATTERN_H

