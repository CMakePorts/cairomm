include $(top_srcdir)/examples/Makefile.am_fragment

# build the executable but don't install it
noinst_PROGRAMS = pdf-surface \
									ps-surface \
									svg-surface \
									image-surface

pdf_surface_SOURCES = pdf-surface.cc
ps_surface_SOURCES = ps-surface.cc
svg_surface_SOURCES = svg-surface.cc
image_surface_SOURCES = image-surface.cc

CLEANFILES = image.pdf image.ps image.svg example_png_file.png
