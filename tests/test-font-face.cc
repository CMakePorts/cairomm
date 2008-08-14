// vim: ts=2 sw=2 et
/*
 * These tests are of limited usefulness.  In fact, you might even say that
 * they're not really tests at all.  But I felt that it would be useful to have
 * some basic usage of most functions just to verify that things compile and
 * work generally
 */

#include <cfloat>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>
using namespace boost::unit_test;
#include <cairomm/fontface.h>

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


test_suite*
init_unit_test_suite(int argc, char* argv[])
{
  // compile even with -Werror
  if (argc && argv) {}

  test_suite* test= BOOST_TEST_SUITE( "Cairo::FontFace Tests" );

  test->add (BOOST_TEST_CASE (&test_create_toy));
  test->add (BOOST_TEST_CASE (&test_toy_getters));

  return test;
}
