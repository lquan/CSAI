#
# Copyright (c) 2010 Tias Guns <tias.guns@cs.kuleuven.be>
# Copyright (c) 2011 Siegfried Nijssen <siegfried.nijssen@cs.kuleuven.be>
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

AM_CPPFLAGS = -I../${GECODE_INCLUDES}
LDADD = -L../${GECODE_LIBRARIES} \
		-lgecodekernel -lgecodedriver \
		-lgecodesearch -lgecodeint \
		-lgecodesupport
if GECODE_WITH_GIST
LDADD += -lgecodegist
endif

COMMON = common/floatoption.cpp common/stringuintoption.cpp common/textoption.cpp
FIMCP = $(COMMON) common/options_fimcp.cpp common/fimcp_basic.cpp
RIMCP = $(FIMCP) common/constraint_regression.cpp common/regression.cpp rimcp.cpp


bin_PROGRAMS = \
	rimcp
AM_DEFAULT_SOURCE_EXT = .cpp

rimcp_SOURCES = $(RIMCP) my_regression.cpp

EXTRA_DIST = README RELEASE
