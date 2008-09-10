// vim: ts=2 sw=2 et
/*
 * These tests are of limited usefulness.  In fact, you might even say that
 * they're not really tests at all.  But I felt that it would be useful to have
 * some basic usage of most functions just to verify that things compile and
 * work generally
 */

#include <cfloat>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>
using namespace boost::unit_test;
#include <cairomm/fontface.h>
#include <cairomm/scaledfont.h>
#include <cairomm/surface.h>
#include <cairomm/context.h>

#include <cairo-features.h>
#ifdef CAIRO_HAS_WIN32_FONT
#include <windows.h>
#include <cairomm/win32_font.h>
#endif // CAIRO_HAS_WIN32_FONT

static Cairo::Matrix identity_matrix;

void
test_create_toy ()
{
  Cairo::RefPtr<Cairo::ToyFontFace> toy =
    Cairo::ToyFontFace::create("sans",
                               Cairo::FONT_SLANT_ITALIC,
                               Cairo::FONT_WEIGHT_NORMAL);
  BOOST_CHECK (toy);
  BOOST_CHECK_EQUAL (CAIRO_STATUS_SUCCESS, toy->get_status());
}

void test_toy_getters ()
{
  Cairo::RefPtr<Cairo::ToyFontFace> toy =
    Cairo::ToyFontFace::create("sans",
                               Cairo::FONT_SLANT_ITALIC,
                               Cairo::FONT_WEIGHT_NORMAL);
  BOOST_CHECK_EQUAL ("sans", toy->get_family());
  BOOST_CHECK_EQUAL (Cairo::FONT_SLANT_ITALIC, toy->get_slant());
  BOOST_CHECK_EQUAL (Cairo::FONT_WEIGHT_NORMAL, toy->get_weight());
  BOOST_CHECK_EQUAL (Cairo::FONT_TYPE_TOY, toy->get_type());
}

void test_user_font_create()
{
  Cairo::RefPtr<Cairo::UserFontFace> font = Cairo::UserFontFace::create();
  BOOST_CHECK_EQUAL (Cairo::FONT_TYPE_USER, font->get_type());
}

// create some dummy callbacks
static unsigned int init_call_count = 0;
Cairo::ErrorStatus my_init(const Cairo::RefPtr<Cairo::ScaledFont>&, const Cairo::RefPtr<Cairo::Context>&, Cairo::FontExtents&)
{
  init_call_count++;
  return CAIRO_STATUS_SUCCESS;
}

static unsigned int unicode_to_glyph_call_count = 0;
Cairo::ErrorStatus my_unicode_to_glyph(const Cairo::RefPtr<Cairo::ScaledFont>&, unsigned long, unsigned long&)
{
  unicode_to_glyph_call_count++;
  return CAIRO_STATUS_SUCCESS;
}

static unsigned int render_glyph_call_count = 0;
Cairo::ErrorStatus my_render_glyph(const Cairo::RefPtr<Cairo::ScaledFont>&, unsigned long, const Cairo::RefPtr<Cairo::Context>&, Cairo::TextExtents&)
{
  render_glyph_call_count++;
  return CAIRO_STATUS_SUCCESS;
}

static unsigned int text_to_glyphs_call_count = 0;
Cairo::ErrorStatus my_text_to_glyphs(const Cairo::RefPtr<Cairo::ScaledFont>&, const std::string& utf8, std::vector<Cairo::Glyph>& glyphs, std::vector<Cairo::TextCluster>& /*clusters*/, bool& /*backward*/)
{
  text_to_glyphs_call_count++;
  if (glyphs.size())
    glyphs.clear();
  // just fill in some bogus glyph indexes
  std::string::const_iterator str_iter = utf8.begin();
  for (; str_iter != utf8.end(); ++str_iter)
  {
    Cairo::Glyph g;
    g.index = (unsigned long) *str_iter;
    glyphs.push_back(g);
  }
  return CAIRO_STATUS_SUCCESS;
}

void test_user_font_callbacks_ptr()
{
  render_glyph_call_count = 0;
  unicode_to_glyph_call_count = 0;
  init_call_count = 0;
  Cairo::RefPtr<Cairo::UserFontFace> font = Cairo::UserFontFace::create();
  BOOST_CHECK(font);
  font->set_init_func(sigc::ptr_fun(my_init));
  font->set_unicode_to_glyph_func(sigc::ptr_fun(my_unicode_to_glyph));
  font->set_render_glyph_func(sigc::ptr_fun(my_render_glyph));
  Cairo::RefPtr<Cairo::ScaledFont> scaled_font =
    Cairo::ScaledFont::create(font, identity_matrix, identity_matrix,
                              Cairo::FontOptions());
  BOOST_CHECK (init_call_count > 0);
  Cairo::RefPtr<Cairo::ImageSurface> surface =
    Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 100, 100);
  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
  cr->set_font_face(font);
  cr->show_text("Hello, world");
  BOOST_CHECK (unicode_to_glyph_call_count > 0);
  BOOST_CHECK (render_glyph_call_count > 0);
}

// since unicode_to_glyph_func and text_to_glyphs_func are mutually exclusive,
// we must test them separately.  This test tests the text_to_glyphs_func
void test_user_font_callbacks_ptr_text()
{
  render_glyph_call_count = 0;
  text_to_glyphs_call_count = 0;
  init_call_count = 0;
  Cairo::RefPtr<Cairo::UserFontFace> font = Cairo::UserFontFace::create();
  BOOST_CHECK(font);
  font->set_init_func(sigc::ptr_fun(my_init));
  font->set_render_glyph_func(sigc::ptr_fun(my_render_glyph));
  font->set_text_to_glyphs_func(sigc::ptr_fun(my_text_to_glyphs));
  Cairo::RefPtr<Cairo::ScaledFont> scaled_font =
    Cairo::ScaledFont::create(font, identity_matrix, identity_matrix,
                              Cairo::FontOptions());
  BOOST_CHECK (init_call_count > 0);
  Cairo::RefPtr<Cairo::ImageSurface> surface =
    Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 100, 100);
  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
  cr->set_font_face(font);
  cr->show_text("Hello, world");
  BOOST_CHECK (render_glyph_call_count > 0);
  BOOST_CHECK (text_to_glyphs_call_count > 0);
}

struct UserFontCallbacks
{
Cairo::ErrorStatus init(const Cairo::RefPtr<Cairo::ScaledFont>&, const Cairo::RefPtr<Cairo::Context>&, Cairo::FontExtents&)
{
  init_call_count++;
  return CAIRO_STATUS_SUCCESS;
}

Cairo::ErrorStatus unicode_to_glyph(const Cairo::RefPtr<Cairo::ScaledFont>&, unsigned long, unsigned long&)
{
  unicode_to_glyph_call_count++;
  return CAIRO_STATUS_SUCCESS;
}

Cairo::ErrorStatus render_glyph(const Cairo::RefPtr<Cairo::ScaledFont>&, unsigned long, const Cairo::RefPtr<Cairo::Context>&, Cairo::TextExtents&)
{
  render_glyph_call_count++;
  return CAIRO_STATUS_SUCCESS;
}

static unsigned int init_call_count;
static unsigned int unicode_to_glyph_call_count;
static unsigned int render_glyph_call_count;
};

unsigned int UserFontCallbacks::init_call_count = 0;
unsigned int UserFontCallbacks::unicode_to_glyph_call_count = 0;
unsigned int UserFontCallbacks::render_glyph_call_count = 0;

void test_user_font_callbacks_mem()
{
  Cairo::RefPtr<Cairo::UserFontFace> font = Cairo::UserFontFace::create();
  BOOST_CHECK(font);
  UserFontCallbacks callbacks;
  font->set_init_func(sigc::mem_fun(&callbacks, &UserFontCallbacks::init));
  font->set_unicode_to_glyph_func(sigc::mem_fun(&callbacks,
                                                &UserFontCallbacks::unicode_to_glyph));
  font->set_render_glyph_func(sigc::mem_fun(&callbacks,
                                            &UserFontCallbacks::render_glyph));
  Cairo::RefPtr<Cairo::ScaledFont> scaled_font =
    Cairo::ScaledFont::create(font, identity_matrix, identity_matrix,
                              Cairo::FontOptions());
  BOOST_CHECK (UserFontCallbacks::init_call_count > 0);
  Cairo::RefPtr<Cairo::ImageSurface> surface =
    Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 100, 100);
  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
  cr->set_font_face(font);
  cr->show_text("Hello, world");
  BOOST_CHECK (UserFontCallbacks::unicode_to_glyph_call_count > 0);
  BOOST_CHECK (UserFontCallbacks::render_glyph_call_count > 0);
}

static unsigned int init_exception_call_count = 0;
Cairo::ErrorStatus my_init_exception(const Cairo::RefPtr<Cairo::ScaledFont>&, const Cairo::RefPtr<Cairo::Context>&, Cairo::FontExtents&)
{
  init_exception_call_count++;
  throw std::logic_error("init exception");
}

static unsigned int unicode_to_glyph_exception_call_count = 0;
Cairo::ErrorStatus my_unicode_to_glyph_exception(const Cairo::RefPtr<Cairo::ScaledFont>&, unsigned long, unsigned long&)
{
  unicode_to_glyph_exception_call_count++;
  throw std::logic_error("unicode-to-glyph exception");
}

static unsigned int render_glyph_exception_call_count = 0;
Cairo::ErrorStatus my_render_glyph_exception(const Cairo::RefPtr<Cairo::ScaledFont>&, unsigned long, const Cairo::RefPtr<Cairo::Context>&, Cairo::TextExtents&)
{
  render_glyph_exception_call_count++;
  throw std::logic_error("render-glyph exception");
}


void test_user_font_callbacks_exception()
{
  Cairo::RefPtr<Cairo::UserFontFace> font = Cairo::UserFontFace::create();
  BOOST_CHECK(font);
  font->set_init_func(sigc::ptr_fun(my_init_exception));

  // the init() callback will throw an exception, if this isn't handled in the
  // callback wrapper, the program will abort since an exception can't unwind
  // through C code.  However, due to the exception being thrown, the create()
  // function will fail and throw a new exception.  So if the executable doesn't
  // abort, we should get an exception here.
  Cairo::RefPtr<Cairo::ScaledFont> scaled_font;
  BOOST_CHECK_THROW (scaled_font = Cairo::ScaledFont::create(font,
                                                             identity_matrix,
                                                             identity_matrix,
                                                             Cairo::FontOptions()),
                     Cairo::logic_error);
  BOOST_CHECK (init_exception_call_count > 0);

  // now initialize a scaled font properly so we can test the other callbacks
  font = Cairo::UserFontFace::create();
  font->set_init_func(sigc::ptr_fun(my_init));
  font->set_render_glyph_func(sigc::ptr_fun(my_render_glyph_exception));
  font->set_unicode_to_glyph_func(sigc::ptr_fun(my_unicode_to_glyph_exception));
  BOOST_CHECK_NO_THROW (scaled_font = Cairo::ScaledFont::create(font,
                                                                identity_matrix,
                                                                identity_matrix,
                                                                Cairo::FontOptions()))
  Cairo::RefPtr<Cairo::ImageSurface> surface =
    Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 100, 100);
  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
  cr->set_font_face(font);
  // this call should throw an exception since the callback wrapper will return
  // an error status (that will be translated into an exception) but the test
  // shouldn't abort sindce the callback exceptions are handled by the callback
  // wrapper
  BOOST_REQUIRE_EQUAL (CAIRO_STATUS_SUCCESS, font->get_status());
  BOOST_CHECK_THROW(cr->show_text("Hello, world"), Cairo::logic_error);
  BOOST_CHECK (UserFontCallbacks::unicode_to_glyph_call_count > 0);
  BOOST_CHECK (UserFontCallbacks::render_glyph_call_count > 0);
}

// create some dummy callbacks
static unsigned int init2_call_count = 0;
Cairo::ErrorStatus my_init2(const Cairo::RefPtr<Cairo::ScaledFont>&, const Cairo::RefPtr<Cairo::Context>&, Cairo::FontExtents&)
{
  init2_call_count++;
  return CAIRO_STATUS_SUCCESS;
}

void test_user_font_replace_callback()
{
  // reset
  init_call_count = 0;
  Cairo::RefPtr<Cairo::UserFontFace> font = Cairo::UserFontFace::create();
  font->set_init_func(sigc::ptr_fun(my_init));
  // now replace the init function with my_init2 and make sure that the 2nd
  // function is called, not the first
  font->set_init_func(sigc::ptr_fun(my_init2));
  Cairo::RefPtr<Cairo::ScaledFont> scaled_font;
  BOOST_CHECK_NO_THROW (scaled_font = Cairo::ScaledFont::create(font,
                                                                identity_matrix,
                                                                identity_matrix,
                                                                Cairo::FontOptions()))
  BOOST_CHECK (init2_call_count > 0);
  BOOST_CHECK_EQUAL (init_call_count, 0);
}

#ifdef CAIRO_HAS_FT_FONT
void test_ft_font_face()
{
  FcPattern* invalid = FcPatternCreate();
  Cairo::RefPtr<Cairo::FtFontFace> invalid_face;
  BOOST_CHECK_THROW(invalid_face = Cairo::FtFontFace::create(invalid), std::bad_alloc);

  // basically taken from the cairo test case -- we don't care what font we're
  // using so just create an empty pattern and do the minimal substitution to
  // get a valid pattern
  FcPattern* pattern = FcPatternCreate();
  FcConfigSubstitute (NULL, pattern, FcMatchPattern);
  FcDefaultSubstitute (pattern);
  FcResult result;
  FcPattern* resolved = FcFontMatch (NULL, pattern, &result);
  Cairo::RefPtr<Cairo::FtFontFace> face = Cairo::FtFontFace::create(resolved);
  BOOST_CHECK(face);

  // FIXME: test creating from a FT_Face
}
#endif // CAIRO_HAS_FT_FONT

#ifdef CAIRO_HAS_WIN32_FONT
void test_win32_font_face()
{
  LOGFONTW lf;
  lf.lfHeight = 10;
  lf.lfWidth = 0;
  lf.lfEscapement = 0;
  lf.lfOrientation = 0;
  lf.lfWeight = FW_NORMAL;
  lf.lfItalic = FALSE;
  lf.lfUnderline = FALSE;
  lf.lfStrikeOut = FALSE;
  lf.lfCharSet = ANSI_CHARSET;
  lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
  lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  lf.lfQuality = DEFAULT_QUALITY;
  lf.lfPitchAndFamily = DEFAULT_PITCH;
  wcscpy(lf.lfFaceName, L"Courier New");

  Cairo::RefPtr<Cairo::Win32FontFace> fc(Cairo::Win32FontFace::create(&lf));
  BOOST_CHECK(fc);
  Cairo::RefPtr<Cairo::ImageSurface> sfc(Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, 100, 100));
  Cairo::RefPtr<Cairo::Context> cr(Cairo::Context::create(sfc));
  cr->translate(0.0, 50.0);
  cr->set_source_rgb(1.0, 1.0, 1.0);
  BOOST_CHECK_NO_THROW(cr->set_font_face(fc));
  BOOST_CHECK_NO_THROW(cr->show_text("Hello, World!"));
}
#endif // CAIRO_HAS_WIN32_FONT


test_suite*
init_unit_test_suite(int argc, char* argv[])
{
  // compile even with -Werror
  if (argc && argv) {}

  // setup
  cairo_matrix_init_identity(&identity_matrix);

  test_suite* test= BOOST_TEST_SUITE( "Cairo::FontFace Tests" );

  test->add (BOOST_TEST_CASE (&test_create_toy));
  test->add (BOOST_TEST_CASE (&test_toy_getters));
  test->add (BOOST_TEST_CASE (&test_user_font_create));
  test->add (BOOST_TEST_CASE (&test_user_font_callbacks_ptr));
  test->add (BOOST_TEST_CASE (&test_user_font_callbacks_ptr_text));
  test->add (BOOST_TEST_CASE (&test_user_font_callbacks_mem));
  test->add (BOOST_TEST_CASE (&test_user_font_callbacks_exception));
  test->add (BOOST_TEST_CASE (&test_user_font_replace_callback));
#ifdef CAIRO_HAS_FT_FONT
  test->add (BOOST_TEST_CASE (&test_ft_font_face));
#endif // CAIRO_HAS_FT_FONT
#ifdef CAIRO_HAS_WIN32_FONT
  test->add (BOOST_TEST_CASE (&test_win32_font_face));
#endif // CAIRO_HAS_WIN32_FONT

  return test;
}
