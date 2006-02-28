DOXYGEN_CONFIGFILE = Doxyfile
DOXYGEN_CONFIGFILE_SOURCE = Doxyfile.in
WEB_SERVER = cairographics.org
WEB_SERVER_PATH = /srv/cairo.freedesktop.org/www/documentation/cairomm/reference

EXTRA_DIST = $(DOXYGEN_CONFIGFILE_SOURCE) introduction.h html

index_html = html/index.html

$(index_html): $(DOXYGEN_CONFIGFILE)
	-rm -rf html
	doxygen $(doxygen_configfile) \
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
	@dir='$(<D)'; for p in $$dir/*.html $$dir/*.css $$dir/*.png $$dir/*.jpg $$dir/*.map $$dir/*.md5 $$dir/*.dot ; do \
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

install-data-local: install-reference

uninstall-local: uninstall-reference

all-local: $(index_html)

clean-local:
	-rm -rf html

CLEANFILES = cairomm_doxygen_tags \
						 doxygen-output.txt \
						 doxygen-warnings.txt \
						 undocumented.txt

DISTCLEANFILES = $(DOXYGEN_CONFIGFILE)
