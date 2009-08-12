include $(top_srcdir)/cairomm/filelist.am

book_name = $(CAIROMM_MODULE_NAME)
doc_input = $(addprefix $(top_srcdir)/cairomm/,$(files_extra_h))

htmlrefpub = http://www.cairographics.org/documentation/$(book_name)/reference/

include $(top_srcdir)/build/doc-reference.am

dist_noinst_DATA += reference/cairomm-header.html
