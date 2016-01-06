# http://lackof.org/taggart/hacking/make-example/

SHELL=/bin/bash
SUBDIRS=lib src
CLEANDIRS=$(SUBDIRS:%=clean-%)

subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean

