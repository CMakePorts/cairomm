## Process this file with automake to produce Makefile.in

# This is a list of all of the possible pkg-config files that can be generated.
# Specific ones to be installed are determined in configure.in
ALL_PC_IN = cairomm-1.0.pc.in \
		cairomm-ft-1.0.pc.in \
		cairomm-pdf-1.0.pc.in \
		cairomm-png-1.0.pc.in \
		cairomm-ps-1.0.pc.in \
		cairomm-quartz-1.0.pc.in \
		cairomm-quartz-font-1.0.pc.in \
		cairomm-quartz-image-1.0.pc.in \
		cairomm-svg-1.0.pc.in \
		cairomm-win32-1.0.pc.in \
		cairomm-win32-font-1.0.pc.in \
		cairomm-xlib-1.0.pc.in \
		cairomm-xlib-xrender-1.0.pc.in

EXTRA_DIST = $(ALL_PC_IN)

# Install the pkg-config files:
pkgconfigdir = $(libdir)/pkgconfig
# $INSTALLED_PC is computed in configure.in
pkgconfig_DATA = $(INSTALLED_PC)

DISTCLEANFILES=$(INSTALLED_PC)
