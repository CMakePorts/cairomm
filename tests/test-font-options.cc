#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <cairomm/fontoptions.h>

using namespace boost::unit_test;
using namespace Cairo;

void test_lcd_filter()
{
  FontOptions fo;
  fo.set_lcd_filter(LCD_FILTER_DEFAULT);
  BOOST_CHECK_EQUAL(fo.get_lcd_filter(), LCD_FILTER_DEFAULT);
  fo.set_lcd_filter(LCD_FILTER_NONE);
  BOOST_CHECK_EQUAL(fo.get_lcd_filter(), LCD_FILTER_NONE);
  fo.set_lcd_filter(LCD_FILTER_INTRA_PIXEL);
  BOOST_CHECK_EQUAL(fo.get_lcd_filter(), LCD_FILTER_INTRA_PIXEL);
  fo.set_lcd_filter(LCD_FILTER_FIR3);
  BOOST_CHECK_EQUAL(fo.get_lcd_filter(), LCD_FILTER_FIR3);
  fo.set_lcd_filter(LCD_FILTER_FIR5);
  BOOST_CHECK_EQUAL(fo.get_lcd_filter(), LCD_FILTER_FIR5);
}

test_suite*
init_unit_test_suite(int argc, char* argv[])
{
  // compile even with -Werror
  if (argc && argv) {}

  test_suite* test= BOOST_TEST_SUITE( "Cairo::Context Tests" );

  test->add (BOOST_TEST_CASE (&test_lcd_filter));

  return test;
}
