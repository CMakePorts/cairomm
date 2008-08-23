#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>
using namespace boost::unit_test;
#include <cairomm/scaledfont.h>

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
  bool backwards = false;
  font->text_to_glyphs(0, 0, "foo", glyphs, clusters, backwards);

  BOOST_CHECK_EQUAL(3, glyphs.size());
  BOOST_CHECK_EQUAL(3, clusters.size());
}

test_suite*
init_unit_test_suite(int argc, char* argv[])
{
  // compile even with -Werror
  if (argc && argv) {}

  test_suite* test= BOOST_TEST_SUITE( "Cairo::ScaledFont Tests" );

  test->add (BOOST_TEST_CASE (&test_construction));
  test->add (BOOST_TEST_CASE (&test_text_to_glyphs));

  return test;
}
