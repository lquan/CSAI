#
# Copyright (c) 2010 Tias Guns <tias.guns@cs.kuleuven.be>
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
GECODE_VERSION=gecode-3.4.2
GECODE_DIR=$(GECODE_VERSION)/

all-local: gecode

gecode:
	if test ! -d $(GECODE_DIR); then \
		wget http://www.gecode.org/download/$(GECODE_VERSION).tar.gz && \
		tar -xzvf $(GECODE_VERSION).tar.gz && \
		rm $(GECODE_VERSION).tar.gz; \
	fi
if BUILD_GECODE
#	cd $(GECODE_DIR) && ./configure --disable-shared --enable-static
if GECODE_WITH_GIST
GECODE_CONFIG_GIST = --enable-qt --enable-gist
else
GECODE_CONFIG_GIST = --disable-qt --disable-gist
endif
	cd $(GECODE_DIR) && ./configure\
			--disable-doc-dot --disable-doc-search --disable-doc-tagfile --disable-doc-chm\
			--disable-set-vars --disable-graph --disable-flatzinc\
			--disable-scheduling --disable-examples --disable-minimodel \
			$(GECODE_CONFIG_GIST) $(GECODE_CONFIG_FLAGS)
	cd $(GECODE_DIR) && $(MAKE) $(AM_MAKEFLAGS)
else
	echo "Not building gecode, as requested"
endif


clean-local:
	if test -d $(GECODE_DIR); then cd $(GECODE_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean; fi

distclean-local:
	if test -d $(GECODE_DIR); then cd $(GECODE_DIR) && $(MAKE) $(AM_MAKEFLAGS) distclean; fi
