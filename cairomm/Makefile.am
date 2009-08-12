lib_LTLIBRARIES = libcairomm-1.0.la

include $(srcdir)/filelist.am
include $(top_srcdir)/build/compile-binding.am

AM_CPPFLAGS = $(binding_includes) $(binding_cppflags) -I. $(CAIROMM_CFLAGS)
AM_CXXFLAGS = $(CAIROMM_WXXFLAGS)

libcairomm_1_0_la_SOURCES = $(binding_sources)
libcairomm_1_0_la_LDFLAGS = -no-undefined -version-info $(CAIROMM_SO_VERSION)
libcairomm_1_0_la_LIBADD = $(CAIROMM_LIBS)
