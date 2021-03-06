DOMAIN = $(PACKAGE_NAME)
COPYRIGHT_HOLDER = The Virt Viewer authors
MSGID_BUGS_ADDRESS = https://virt-manager.org/bugs/

MAINTAINERCLEANFILES = $(GMOFILES) $(POTFILE) $(POFILES)

LANGS := \
	af am anp ar as ast bal be bg \
	bn_IN bn bo br brx bs ca cs cy da \
	de_CH de el en_GB eo es et eu fa fi \
	fr gl gu he hi hr hu ia \
	id ilo is it ja ka kk km kn ko \
	kw_GB kw@kkcor kw kw@uccor ky lt lv mai mk ml \
	mn mr ms nb nds ne nl nn nso \
	or pa pl pt_BR pt ro ru si sk sl \
	sq sr@latin sr sv ta te tg th tr tw \
	uk ur vi wba yo zh_CN zh_HK zh_TW zu


POTFILE_DEPS := $(shell $(SED) 's,^,$(top_srcdir)/,' $(srcdir)/POTFILES)
POTFILE := $(srcdir)/$(DOMAIN).pot
POFILES := $(LANGS:%=$(srcdir)/%.po)
GMOFILES := $(LANGS:%=$(srcdir)/%.gmo)

EXTRA_DIST = \
	POTFILES \
	$(POTFILE) \
	$(POFILES) \
	$(GMOFILES)

if HAVE_GNU_GETTEXT_TOOLS

XGETTEXT_ARGS = \
	--default-domain=$(DOMAIN) \
	--from-code=utf-8 \
	--add-comments=TRANSLATORS: \
	 --keyword=_ --keyword=N_ \
	--copyright-holder='$(COPYRIGHT_HOLDER)' \
	--package-name="$(PACKAGE_NAME)" \
	--package-version="$(PACKAGE_VERSION)" \
	--msgid-bugs-address="$(MSGID_BUGS_ADDRESS)" \
	--directory=$(top_srcdir) \
	$(NULL)

SED_PO_FIXUP_ARGS = \
	-e "s|text/plain; charset=CHARSET|text/plain; charset=UTF-8|g" \
	-e "s|SOME DESCRIPTIVE TITLE|Virt Viewer package strings|g" \
	-e "s|Copyright (C) YEAR|Copyright (C) $$(date +'%Y')|" \
	$(NULL)

all: update-po

update-po: $(POFILES)

update-gmo: $(GMOFILES)

update-mini-po: $(POTFILE)
	for lang in $(LANGS); do \
	  echo "Minimizing $$lang content" && \
	  $(MSGMERGE) --no-location --no-fuzzy-matching --sort-output \
	    $(srcdir)/$$lang.po $(POTFILE) | \
	  $(SED) $(SED_PO_FIXUP_ARGS) | \
	  $(PERL) $(top_srcdir)/build-aux/minimize-po.pl > \
	    $(srcdir)/$$lang.mini.po ; \
	done

push-pot: $(POTFILE)
	zanata push --push-type=source

pull-po: $(POTFILE)
	zanata pull --create-skeletons
	$(MAKE) update-mini-po
	$(MAKE) update-gmo

$(POTFILE): POTFILES $(POTFILE_DEPS)
	$(XGETTEXT) -o $@-t $(XGETTEXT_ARGS) \
	  --files-from=$(abs_srcdir)/POTFILES
	$(SED) $(SED_PO_FIXUP_ARGS) < $@-t > $@
	rm -f $@-t

$(srcdir)/%.po: $(srcdir)/%.mini.po $(POTFILE)
	$(MSGMERGE) --no-fuzzy-matching $< $(POTFILE) | \
	  $(SED) $(SED_PO_FIXUP_ARGS) > $@

$(srcdir)/%.gmo: $(srcdir)/%.po
	rm -f $@ $@-t
	$(MSGFMT) -c -o $@-t $<
	mv $@-t $@

.PRECIOUS: $(POTFILE) $(POFILES)

endif HAVE_GNU_GETTEXT_TOOLS

if ENABLE_NLS

# Cannot use 'localedir' since this conflicts with autoconf.
langinstdir = $(datadir)/locale

install-data-hook: $(GMOFILES)
	mkdir -p $(DESTDIR)$(langinstdir)
	for lang in $(LANGS); do \
	  d=$(DESTDIR)$(langinstdir)/$$lang/LC_MESSAGES; \
	  mkdir -p $$d; \
	  install -m 0644 $(srcdir)/$$lang.gmo $$d/$(DOMAIN).mo; \
	done

uninstall-hook:
	for lang in $(LANGS); do \
	  d=$(DESTDIR)$(langinstdir)/$$lang/LC_MESSAGES; \
	  rm -f $$d/$(DOMAIN).mo; \
	done

endif ENABLE_NLS

-include $(top_srcdir)/git.mk
