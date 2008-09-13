#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>
using namespace boost::unit_test;

#include <cairomm/matrix.h>

void test_constructors()
{
  cairo_matrix_t c_identity;
  cairo_matrix_init_identity(&c_identity);
  Cairo::Matrix cpp_identity;

  BOOST_CHECK_EQUAL(c_identity.xx,  cpp_identity.xx);
  BOOST_CHECK_EQUAL(c_identity.yx,  cpp_identity.yx);
  BOOST_CHECK_EQUAL(c_identity.xy,  cpp_identity.xy);
  BOOST_CHECK_EQUAL(c_identity.yy,  cpp_identity.yy);
  BOOST_CHECK_EQUAL(c_identity.x0,  cpp_identity.x0);
  BOOST_CHECK_EQUAL(c_identity.y0,  cpp_identity.y0);

  // nonsense values, just for testing
  const double xx=1, yx=2, xy=3, yy=5, x0=6, y0=7;
  cairo_matrix_t c_matrix;
  cairo_matrix_init(&c_matrix, xx, yx, xy, yy, x0, y0);
  Cairo::Matrix cpp_matrix(xx, yx, xy, yy, x0, y0);

  BOOST_CHECK_EQUAL(c_matrix.xx, cpp_matrix.xx);
  BOOST_CHECK_EQUAL(c_matrix.yx, cpp_matrix.yx);
  BOOST_CHECK_EQUAL(c_matrix.xy, cpp_matrix.xy);
  BOOST_CHECK_EQUAL(c_matrix.yy, cpp_matrix.yy);
  BOOST_CHECK_EQUAL(c_matrix.x0, cpp_matrix.x0);
  BOOST_CHECK_EQUAL(c_matrix.y0, cpp_matrix.y0);
}

void test_invert()
{
  // test a valid matrix
  Cairo::Matrix identity;
  BOOST_CHECK_NO_THROW(identity.invert());
  // check a degenerate matrix
  Cairo::Matrix degenerate(0,0,0,0,0,0);
  BOOST_CHECK_THROW(degenerate.invert(), std::logic_error);
}

cairo_matrix_t* test_matrix = 0;
static void foo(cairo_matrix_t* matrix)
{
  test_matrix = matrix;
}

void test_cast()
{
  // make sure that we can cast between C++ and C types without ill effect
  Cairo::Matrix matrix;
  cairo_matrix_t casted = (cairo_matrix_t) matrix;
  // check that it's equal to the identity matrix
  cairo_matrix_t identity;
  cairo_matrix_init_identity(&identity);

  BOOST_CHECK_EQUAL(casted.xx, identity.xx);
  BOOST_CHECK_EQUAL(casted.yx, identity.yx);
  BOOST_CHECK_EQUAL(casted.xy, identity.xy);
  BOOST_CHECK_EQUAL(casted.yy, identity.yy);
  BOOST_CHECK_EQUAL(casted.x0, identity.x0);
  BOOST_CHECK_EQUAL(casted.y0, identity.y0);

  // pass C++ type as an argument to C
  foo(&matrix);
  BOOST_CHECK_EQUAL(matrix.xx, test_matrix->xx);
  BOOST_CHECK_EQUAL(matrix.yx, test_matrix->yx);
  BOOST_CHECK_EQUAL(matrix.xy, test_matrix->xy);
  BOOST_CHECK_EQUAL(matrix.yy, test_matrix->yy);
  BOOST_CHECK_EQUAL(matrix.x0, test_matrix->x0);
  BOOST_CHECK_EQUAL(matrix.y0, test_matrix->y0);
}

test_suite*
init_unit_test_suite(int /*argc*/, char** /*argv*/)
{
  test_suite* test= BOOST_TEST_SUITE( "Cairo::Matrix Tests" );

  test->add (BOOST_TEST_CASE (&test_constructors));
  test->add (BOOST_TEST_CASE (&test_invert));
  test->add (BOOST_TEST_CASE (&test_cast));

  return test;
}
