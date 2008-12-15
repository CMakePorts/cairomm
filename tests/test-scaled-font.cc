#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>
using namespace boost::unit_test;
#include <cairomm/scaledfont.h>
#include <iostream>

using namespace Cairo;

void test_construction()
{
  RefPtr<ToyFontFace> face = ToyFontFace::create("sans", FONT_SLANT_NORMAL, FONT_WEIGHT_NORMAL);
  Matrix identity;
  cairo_matrix_init_identity(&identity);
  RefPtr<ScaledFont> font = ScaledFont::create(face, identity, identity, FontOptions());
  BOOST_REQUIRE(font);

  // now use the default argument for font_options
  font = ScaledFont::create(face, identity, identity);
  BOOST_REQUIRE(font);
}

void test_text_to_glyphs()
{
  RefPtr<ToyFontFace> face = ToyFontFace::create("sans", FONT_SLANT_NORMAL, FONT_WEIGHT_NORMAL);
  Matrix identity;
  cairo_matrix_init_identity(&identity);
  RefPtr<ScaledFont> font = ScaledFont::create(face, identity, identity, FontOptions());
  BOOST_REQUIRE(font);

  std::vector<Glyph> glyphs;
  std::vector<TextCluster> clusters;
  TextClusterFlags flags;
  font->text_to_glyphs(0, 0, "foo", glyphs, clusters, flags);

  BOOST_CHECK_EQUAL(3, glyphs.size());
  BOOST_CHECK_EQUAL(3, clusters.size());
}

void test_scale_matrix()
{
  RefPtr<ToyFontFace> face = ToyFontFace::create("sans", FONT_SLANT_NORMAL, FONT_WEIGHT_NORMAL);
  Matrix m;
  cairo_matrix_init_scale(&m, 2.0, 4.0);
  RefPtr<ScaledFont> font = ScaledFont::create(face, m, m, FontOptions());
  BOOST_REQUIRE(font);

  Matrix result;
  font->get_scale_matrix(result);
  // no real test, just excercising the functionality
}

void test_get_font_face()
{
  // this is to test for a bug where we were accidentally freeing the resulting
  // font face from a call to ScaledFont::get_font_face() when we didn't hold a
  // reference to it
  RefPtr<ToyFontFace> face = ToyFontFace::create("sans", FONT_SLANT_NORMAL, FONT_WEIGHT_NORMAL);
  Matrix identity;
  cairo_matrix_init_identity(&identity);
  RefPtr<ScaledFont> font = ScaledFont::create(face, identity, identity, FontOptions());
  BOOST_REQUIRE(font);
  const int refcount = cairo_font_face_get_reference_count(face->cobj());
  {
    RefPtr<FontFace> got_face = font->get_font_face();
  } // scope ensure that the font face is destroyed
  // after creating and destroying the FontFace in get_font_face, our reference
  // count should be the same
  BOOST_REQUIRE_EQUAL(cairo_font_face_get_reference_count(face->cobj()), refcount);
}


test_suite*
init_unit_test_suite(int argc, char* argv[])
{
  // compile even with -Werror
  if (argc && argv) {}

  test_suite* test= BOOST_TEST_SUITE( "Cairo::ScaledFont Tests" );

  test->add (BOOST_TEST_CASE (&test_construction));
  test->add (BOOST_TEST_CASE (&test_text_to_glyphs));
  test->add (BOOST_TEST_CASE (&test_scale_matrix));
  test->add (BOOST_TEST_CASE (&test_get_font_face));

  return test;
}
