if AUTOTESTS

# build automated 'tests'
TESTS=test-context test-font-face test-surface test-scaled-font
noinst_PROGRAMS = $(TESTS)
test_context_SOURCES=test-context.cc
test_font_face_SOURCES=test-font-face.cc
test_surface_SOURCES=test-surface.cc
test_scaled_font_SOURCES=test-scaled-font.cc

else

#don't build anything
TESTS=

endif

#Where to find the header files needed by the source files:
INCLUDES =  -I$(top_srcdir) @CAIROMM_CFLAGS@

#The libraries that the executable needs to link against:
LIBS = $(top_builddir)/cairomm/libcairomm-1.0.la @LIBS@ @CAIROMM_LIBS@ @BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB@
