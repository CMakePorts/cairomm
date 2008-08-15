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

void test_user_font_callbacks_ptr()
{
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
  test->add (BOOST_TEST_CASE (&test_user_font_callbacks_mem));
  test->add (BOOST_TEST_CASE (&test_user_font_callbacks_exception));
  test->add (BOOST_TEST_CASE (&test_user_font_replace_callback));

  return test;
}
