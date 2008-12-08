#include <cairomm/cairomm.h>
#include <iostream>

const double HEIGHT = 200.0;
const double WIDTH = 400.0;
const double FONT_SIZE = 64.0;
const double TEXT_ORIGIN_Y = (HEIGHT / 2.0) + (FONT_SIZE / 2.0);
const double TEXT_ORIGIN_X = 50.0;  // arbitrary

// A *very* simple font that just draws a box for every glyph
class BoxFontFace : public Cairo::UserFontFace
{
public:
  static Cairo::RefPtr<BoxFontFace> create()
  {
    return Cairo::RefPtr<BoxFontFace>(new BoxFontFace());
  }

  virtual Cairo::ErrorStatus
    render_glyph(const Cairo::RefPtr<Cairo::ScaledFont>& /*scaled_font*/,
                 unsigned long glyph,
                 const Cairo::RefPtr<Cairo::Context>& cr,
                 Cairo::TextExtents& /*metrics*/)
  {
    std::cout << "Rendering glyph " << glyph << std::endl;
    cr->set_line_width(0.05);
    // FIXME: is the negative Y value correct?
    cr->rectangle(0.0, 0.0, 1.0, -1.0);
    cr->stroke();
    return CAIRO_STATUS_SUCCESS;
  }

protected:
  BoxFontFace() : UserFontFace() { }
};

int main(int, char**)
{
  Cairo::RefPtr<Cairo::ImageSurface> surface =
    Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, WIDTH, HEIGHT);
  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
  // fill background in white
  cr->set_source_rgb(1.0, 1.0, 1.0);
  cr->paint();

  // draw a little dot at the point where text will be drawn
  cr->arc(TEXT_ORIGIN_X, TEXT_ORIGIN_Y, FONT_SIZE / 4.0, 0, 2*M_PI);
  cr->set_source_rgba(0.0, 1.0, 0.0, 0.5);
  cr->fill();

  // draw the text
  cr->move_to(TEXT_ORIGIN_X, TEXT_ORIGIN_Y);
  cr->set_source_rgb(0.8, 0.2, 0.2);

  // this scope block is simply to test that the user font can still be
  // drawn even after the UserFont wrapper object has been de-referenced
  {
    Cairo::RefPtr<BoxFontFace> font = BoxFontFace::create();
    cr->set_font_face(font);
  }

  cr->set_font_size(FONT_SIZE);
  cr->show_text("cairomm!");
  surface->write_to_png("user-font.png");
  return 0;
}
