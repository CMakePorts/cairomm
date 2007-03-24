// vim: ts=2 sw=2 et
/*
 * These tests are of limited usefulness.  In fact, you might even say that
 * they're not really tests at all.  But I felt that it would be useful to have
 * some basic usage of most functions just to verify that things compile and
 * work generally
 */

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
using namespace boost::unit_test;
#include <cairomm/context.h>

#define CREATE_CONTEXT(varname) \
  Cairo::RefPtr<Cairo::Surface> surf = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 10, 10); \
  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surf);

void
test_dashes ()
{
  CREATE_CONTEXT(cr);
  std::valarray<double> dash_array(4);
  dash_array[0] = 0.1;
  dash_array[1] = 0.2;
  dash_array[2] = 0.04;
  dash_array[3] = 0.31;
  cr->set_dash(dash_array, 0.54);

  std::vector<double> get_array;
  double get_offset;
  cr->get_dash (get_array, get_offset);
  BOOST_CHECK (get_array[0] == dash_array[0]);
  BOOST_CHECK (get_array[1] == dash_array[1]);
  BOOST_CHECK (get_array[2] == dash_array[2]);
  BOOST_CHECK (get_array[3] == dash_array[3]);
  BOOST_CHECK (get_offset == 0.54);

  cr->unset_dash ();
  cr->get_dash (get_array, get_offset);
  BOOST_CHECK (get_array.empty ());
}

void
test_save_restore ()
{
  CREATE_CONTEXT(cr);
  cr->set_line_width (1.0);
  cr->save ();
  cr->set_line_width (4.0);
  BOOST_CHECK (cr->get_line_width () == 4.0);
  cr->restore ();
  BOOST_CHECK (cr->get_line_width () == 1.0);
}

void
test_operator ()
{
  CREATE_CONTEXT(cr);
  cr->set_operator (Cairo::OPERATOR_ATOP);
  BOOST_CHECK (cr->get_operator () == Cairo::OPERATOR_ATOP);
  cr->set_operator (Cairo::OPERATOR_CLEAR);
  BOOST_CHECK (cr->get_operator () == Cairo::OPERATOR_CLEAR);
}

void
test_source ()
{
  CREATE_CONTEXT(cr);
  Cairo::RefPtr<Cairo::Pattern> solid_pattern =
    Cairo::SolidPattern::create_rgb (1.0, 0.5, 0.25);
  Cairo::RefPtr<Cairo::Pattern> gradient_pattern =
    Cairo::LinearGradient::create (0.0, 0.0, 1.0, 1.0);

  // there doesn't seem to be any way to compare the retrieved pattern to the
  // one that was set...  for now, just excercise the function calls.
  cr->set_source (solid_pattern);
  //BOOST_CHECK (cr->get_source () == solid_pattern);

  cr->set_source (gradient_pattern);
  //BOOST_CHECK (cr->get_source () == gradient_pattern);

  cr->set_source_rgb (1.0, 0.5, 0.25);
  Cairo::RefPtr<Cairo::SolidPattern> solid =
    Cairo::RefPtr<Cairo::SolidPattern>::cast_dynamic(cr->get_source ());
  BOOST_REQUIRE (solid);
  double rx, gx, bx, ax;
  solid->get_rgba (rx, gx, bx, ax);
  BOOST_CHECK (rx == 1.0);
  BOOST_CHECK (gx == 0.5);
  BOOST_CHECK (bx == 0.25);
  cr->set_source_rgba (0.1, 0.3, 0.5, 0.7);
  solid =
    Cairo::RefPtr<Cairo::SolidPattern>::cast_dynamic(cr->get_source ());
  BOOST_REQUIRE (solid);
  solid->get_rgba (rx, gx, bx, ax);
  BOOST_CHECK (rx == 0.1);
  BOOST_CHECK (gx == 0.3);
  BOOST_CHECK (bx == 0.5);
  BOOST_CHECK (ax == 0.7);
}

void
test_tolerance ()
{
  CREATE_CONTEXT(cr);
  cr->set_tolerance (3.0);
  BOOST_CHECK (cr->get_tolerance () == 3.0);
}

void
test_antialias ()
{
  CREATE_CONTEXT(cr);
  cr->set_antialias (Cairo::ANTIALIAS_GRAY);
  BOOST_CHECK (cr->get_antialias () == Cairo::ANTIALIAS_GRAY);

  cr->set_antialias (Cairo::ANTIALIAS_SUBPIXEL);
  BOOST_CHECK (cr->get_antialias () == Cairo::ANTIALIAS_SUBPIXEL);
}

void
test_fill_rule ()
{
  CREATE_CONTEXT(cr);
  cr->set_fill_rule (Cairo::FILL_RULE_EVEN_ODD);
  BOOST_CHECK (cr->get_fill_rule () == Cairo::FILL_RULE_EVEN_ODD);
  cr->set_fill_rule (Cairo::FILL_RULE_WINDING);
  BOOST_CHECK (cr->get_fill_rule () == Cairo::FILL_RULE_WINDING);
}

void
test_line_width ()
{
  CREATE_CONTEXT(cr);
  cr->set_line_width (1.0);
  BOOST_CHECK (cr->get_line_width () == 1.0);
  cr->set_line_width (4.0);
  BOOST_CHECK (cr->get_line_width () == 4.0);
}

void
test_line_cap ()
{
  CREATE_CONTEXT(cr);
  cr->set_line_cap (Cairo::LINE_CAP_BUTT);
  BOOST_CHECK (cr->get_line_cap () == Cairo::LINE_CAP_BUTT);
  cr->set_line_cap (Cairo::LINE_CAP_ROUND);
  BOOST_CHECK (cr->get_line_cap () == Cairo::LINE_CAP_ROUND);
}

void
test_line_join ()
{
  CREATE_CONTEXT(cr);
  cr->set_line_join (Cairo::LINE_JOIN_BEVEL);
  BOOST_CHECK (cr->get_line_join () == Cairo::LINE_JOIN_BEVEL);
  cr->set_line_join (Cairo::LINE_JOIN_MITER);
  BOOST_CHECK (cr->get_line_join () == Cairo::LINE_JOIN_MITER);
}

void
test_miter_limit ()
{
  CREATE_CONTEXT (cr);
  cr->set_miter_limit (1.3);
  BOOST_CHECK (cr->get_miter_limit () == 1.3);
  cr->set_miter_limit (4.12);
  BOOST_CHECK (cr->get_miter_limit () == 4.12);
}

void
test_matrix ()
{
  CREATE_CONTEXT (cr);
  //cr->transform();
  //cr->set_matrix();
  //cr->set_identity_matrix ();
}

void
test_user_device ()
{
  // scale / transform a context, and then verify that user-to-device and
  // device-to-user things work.
}

void
test_draw ()
{
  CREATE_CONTEXT (cr);
  // just call a bunch of drawing functions to excercise them a bit.  There's no
  // rhyme or reason to this, don't expect it to draw anything interesting.
  cr->begin_new_path ();
  cr->move_to (1.0, 1.0);
  cr->line_to (2.0, 2.0);
  cr->curve_to (0.5, 0.5, 0.5, 0.5, 1.0, 1.0);
  cr->arc (1.5, 0.5, 0.5, 0, 2 * M_PI);
  cr->stroke ();
  cr->arc_negative (1.5, 0.5, 0.5, 0, 2 * M_PI);
  cr->rel_move_to (0.1, 0.1);
  cr->rel_line_to (0.5, -0.5);
  cr->rel_curve_to (0.5, 0.5, 0.5, 0.5, 1.0, 1.0);
  cr->rectangle (0.0, 0.0, 1.0, 1.0);
  cr->close_path ();
  cr->paint ();
}

void
test_clip ()
{
  CREATE_CONTEXT (cr);
  cr->rectangle (0.0, 0.0, 1.0, 1.0);
  cr->clip ();
  double x1, y1, x2, y2;
  cr->get_clip_extents (x1, y1, x2, y2);
  BOOST_CHECK (x1 == 0.0);
  BOOST_CHECK (y1 == 0.0);
  BOOST_CHECK (x2 == 1.0);
  BOOST_CHECK (y2 == 1.0);
}

void
test_current_point ()
{
  CREATE_CONTEXT (cr);
  cr->move_to (2.0, 3.0);
  double x, y;
  cr->get_current_point (x, y);
  BOOST_CHECK (x == 2.0);
  BOOST_CHECK (y == 3.0);
}

test_suite*
init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test= BOOST_TEST_SUITE( "Cairo::Context Tests" );

    test->add (BOOST_TEST_CASE (&test_dashes));
    test->add (BOOST_TEST_CASE (&test_save_restore));
    test->add (BOOST_TEST_CASE (&test_operator));
    test->add (BOOST_TEST_CASE (&test_source));
    test->add (BOOST_TEST_CASE (&test_tolerance));
    test->add (BOOST_TEST_CASE (&test_antialias));
    test->add (BOOST_TEST_CASE (&test_fill_rule));
    test->add (BOOST_TEST_CASE (&test_line_width));
    test->add (BOOST_TEST_CASE (&test_line_cap));
    test->add (BOOST_TEST_CASE (&test_line_join));
    test->add (BOOST_TEST_CASE (&test_miter_limit));
    //test->add (BOOST_TEST_CASE (&test_matrix));
    //test->add (BOOST_TEST_CASE (&test_user_device));
    test->add (BOOST_TEST_CASE (&test_draw));
    test->add (BOOST_TEST_CASE (&test_clip));
    test->add (BOOST_TEST_CASE (&test_current_point));

    return test;
}
