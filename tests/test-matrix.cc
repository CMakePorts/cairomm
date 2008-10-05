#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>
using namespace boost::unit_test;

#include <cairomm/matrix.h>

// this is necessary for BOOST_CHECK_EQUAL, but there's no equivalent in the C
// API, so I'm reluctant to include it in cairomm right now
bool operator==(const Cairo::Matrix& A, const Cairo::Matrix& B)
{
  return
    A.xx == B.xx &&
    A.yx == B.yx &&
    A.xy == B.xy &&
    A.yy == B.yy &&
    A.x0 == B.x0 &&
    A.y0 == B.y0;
}

// this is necessary for BOOST_CHECK_EQUAL to work but doesn't seem useful
// enough to put in the actual implementation
std::ostream& operator<<(std::ostream& out, const Cairo::Matrix& matrix)
{
  return out << "[ "
    << matrix.xx << ", "
    << matrix.yx << ", "
    << matrix.xy << ", "
    << matrix.yy << ", "
    << matrix.x0 << ", "
    << matrix.y0 << " ]";
}

void test_constructors()
{
  cairo_matrix_t c_identity;
  cairo_matrix_init_identity(&c_identity);
  BOOST_CHECK_EQUAL(c_identity, Cairo::identity_matrix());

  // nonsense values, just for testing
  const double xx=1, yx=2, xy=3, yy=5, x0=6, y0=7;
  cairo_matrix_t c_matrix;
  cairo_matrix_init(&c_matrix, xx, yx, xy, yy, x0, y0);
  Cairo::Matrix cpp_matrix(xx, yx, xy, yy, x0, y0);

  BOOST_CHECK_EQUAL(c_matrix, cpp_matrix);
}

void test_invert()
{
  // test a valid matrix
  BOOST_CHECK_NO_THROW(Cairo::identity_matrix().invert());
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
  Cairo::Matrix matrix = Cairo::identity_matrix();
  cairo_matrix_t casted = (cairo_matrix_t) Cairo::identity_matrix();
  // check that it's equal to the identity matrix
  cairo_matrix_t identity;
  cairo_matrix_init_identity(&identity);

  BOOST_CHECK_EQUAL(casted, identity);

  // pass C++ type as an argument to C
  foo(&matrix);
  BOOST_CHECK_EQUAL(matrix, *test_matrix);
}

void test_multiply()
{
  Cairo::Matrix A = Cairo::scaled_matrix(2, 4);
  Cairo::Matrix B = Cairo::translation_matrix(5.3, 1.2);
  Cairo::Matrix C = A * B;
  Cairo::Matrix D;
  D.multiply(A, B);
  BOOST_CHECK_EQUAL(C, D);
}

test_suite*
init_unit_test_suite(int /*argc*/, char** /*argv*/)
{
  test_suite* test= BOOST_TEST_SUITE( "Cairo::Matrix Tests" );

  test->add (BOOST_TEST_CASE (&test_constructors));
  test->add (BOOST_TEST_CASE (&test_invert));
  test->add (BOOST_TEST_CASE (&test_cast));
  test->add (BOOST_TEST_CASE (&test_multiply));

  return test;
}
