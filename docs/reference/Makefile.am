DOXYGEN_CONFIGFILE = Doxyfile
DOXYGEN_CONFIGFILE_SOURCE = Doxyfile.in
WEB_SERVER = cairographics.org
WEB_SERVER_PATH = /srv/cairo.freedesktop.org/www/documentation/cairomm/reference
HTML_TEMPLATE_FILES = cairomm.css cairomm-header.html

EXTRA_DIST = $(DOXYGEN_CONFIGFILE_SOURCE) \
			 $(HTML_TEMPLATE_FILES) cairomm_doxygen_tags

cairomm_doxygen_tags : $(index_html)

index_html = html/index.html

$(index_html): $(DOXYGEN_CONFIGFILE) $(wildcard $(top_srcdir)/cairomm/*.h) $(HTML_TEMPLATE_FILES)
	-rm -rf html
	doxygen $(DOXYGEN_CONFIGFILE) \
	2> doxygen-warnings.txt | tee doxygen-output.txt && cat doxygen-warnings.txt

html: $(index_html)

cairomm-reference-html.tar.gz: $(index_html)
	tar cf - html | gzip -c --best >$@

referencedir = $(datadir)/doc/libcairomm-1.0/reference/html

publish:	html
	rsync -avz --rsh ssh --cvs-exclude html/ $(WEB_SERVER):$(WEB_SERVER_PATH)

install-reference: $(index_html)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(referencedir)
	@dir='$(<D)'; for p in `ls $$dir/*.html $$dir/*.css $$dir/*.png $$dir/*.jpg $$dir/*.map $$dir/*.md5 $$dir/*.dot` ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(referencedir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(referencedir)/$$f; \
	done

uninstall-reference: $(index_html)
	@$(NORMAL_UNINSTALL)
	@dir='$(<D)'; for p in $$dir/*.html $$dir/*.css $$dir/*.png $$dir/*.jpg $$dir/*.map $$dir/*.md5 $$dir/*.dot ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(referencedir)/$$f"; \
	  rm -f $(DESTDIR)$(referencedir)/$$f; \
	done

DOXYGEN_REPORTS = doxygen-output.txt doxygen-warnings.txt undocumented.txt

doc-clean:
	-rm -rf html
	-rm -f cairomm_doxygen_tags
	-rm -f $(DOXYGEN_REPORTS)

install-data-local: install-reference

uninstall-local: uninstall-reference

all-local: $(index_html)

maintainer-clean-local: doc-clean
distclean-local: doc-clean

dist-hook: $(index_html)
	cp -R html $(distdir)

DISTCLEANFILES = $(DOXYGEN_CONFIGFILE) $(DOXYGEN_REPORTS)

.PHONY: doc-clean install-reference uninstall-reference

