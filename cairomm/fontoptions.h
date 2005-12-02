#ifndef __CAIROMM_FONTOPTIONS_H
#define __CAIROMM_FONTOPTIONS_H

#include <cairomm/enums.h>
#include <string>
#include <cairo/cairo.h>


namespace Cairo
{

typedef cairo_antialias_t Antialias;
typedef cairo_subpixel_order_t SubpixelOrder;
typedef cairo_hint_style_t HintStyle;
typedef cairo_hint_metrics_t HintMetrics;

/** How a font should be rendered.
 */
class FontOptions
{
public:
  FontOptions();
  explicit FontOptions(cairo_font_options_t* cobject, bool take_ownership = false);
  FontOptions(const FontOptions& src);

  virtual ~FontOptions();

  FontOptions& operator=(const FontOptions& src);

  bool operator ==(const FontOptions& src) const;
  //bool operator !=(const FontOptions& src) const;

  void merge(const FontOptions& other);

  unsigned long hash() const;

  void set_antialias(Antialias antialias);
  Antialias get_antialias() const;

  void set_subpixel_order(SubpixelOrder subpixel_order);
  SubpixelOrder get_subpixel_order() const;

  void set_hint_style(HintStyle hint_style);
  HintStyle get_hint_style() const;

  void set_hint_metrics(HintMetrics hint_metrics);
  HintMetrics get_hint_metrics() const;

  typedef cairo_font_options_t cobject;
  inline cobject* cobj() { return m_cobject; }
  inline const cobject* cobj() const { return m_cobject; }

  #ifndef DOXYGEN_IGNORE_THIS
  ///For use only by the cairomm implementation.
  inline Status get_status() const
  { return cairo_font_options_status(const_cast<cairo_font_options_t*>(cobj())); }
  #endif //DOXYGEN_IGNORE_THIS

protected:

  cobject* m_cobject;
};

} // namespace Cairo

#endif //__CAIROMM_FONTOPTIONS_H

