include $(top_srcdir)/examples/Makefile.am_fragment

# build the executable but don't install it
example_pdf_file_LDADD = $(top_srcdir)/cairomm/libcairomm-1.0.la
noinst_PROGRAMS = example_pdf_file
example_pdf_file_SOURCES = main.cc

CLEANFILES = image.pdf
