#! /usr/bin/make -f
SHELL=/bin/bash
BUILD_DIR = obj
default: login-server char-server map-server ladmin eathena-monitor
.DELETE_ON_ERROR:
include make.defs

.PHONY: all clean common most
# With no prerequisites, no target should ever be implicitly deleted.
# With any prerequisites, those targets won't be (no patterns).
.SECONDARY:
# This does the same, but only for its prerequisites.
# Unlike .SECONDARY, these may be patterns as well as normal prerequisites.
# .PRECIOUS: %/.

%/.:
	+mkdir -p $@

# The default recipe is suboptimal
%.cpp: %.lpp
	$(LEX) -o $@ $<
%.cpp %.h: %.ypp
	$(BISON) -d -o $*.cpp $<


# All this duplication is required because make handles pattern rules specially
${BUILD_DIR}/char/%.o: src/char/%.cpp | ${BUILD_DIR}/char/.
	$(COMPILE.cpp) -o $@ $<
${BUILD_DIR}/common/%.o: src/common/%.cpp | ${BUILD_DIR}/common/.
	$(COMPILE.cpp) -o $@ $<
${BUILD_DIR}/ladmin/%.o: src/ladmin/%.cpp | ${BUILD_DIR}/ladmin/.
	$(COMPILE.cpp) -o $@ $<
${BUILD_DIR}/login/%.o: src/login/%.cpp | ${BUILD_DIR}/login/.
	$(COMPILE.cpp) -o $@ $<
${BUILD_DIR}/map/%.o: src/map/%.cpp | ${BUILD_DIR}/map/.
	$(COMPILE.cpp) -o $@ $<
${BUILD_DIR}/tool/%.o: src/tool/%.cpp | ${BUILD_DIR}/tool/.
	$(COMPILE.cpp) -o $@ $<

MOSTPROGS = login-server char-server ladmin eathena-monitor
PROGS = ${MOSTPROGS} map-server
# Things to actually make
all: ${PROGS}
most: ${MOSTPROGS}
clean:
	rm -rf ${PROGS} ${BUILD_DIR}/
common: ${BUILD_DIR}/common/core.o ${BUILD_DIR}/common/db.o ${BUILD_DIR}/common/lock.o ${BUILD_DIR}/common/md5calc.o ${BUILD_DIR}/common/random.o ${BUILD_DIR}/common/nullpo.o ${BUILD_DIR}/common/socket.o ${BUILD_DIR}/common/timer.o ${BUILD_DIR}/common/utils.o ${BUILD_DIR}/common/cxxstdio.o ${BUILD_DIR}/common/extract.o

# Top level programs
login-server: ${BUILD_DIR}/login/login
	cp -f $< $@
char-server: ${BUILD_DIR}/char/char
	cp -f $< $@
map-server: ${BUILD_DIR}/map/map
	cp -f $< $@
ladmin: ${BUILD_DIR}/ladmin/ladmin
	cp -f $< $@
eathena-monitor: ${BUILD_DIR}/tool/eathena-monitor
	cp -f $< $@

# Executable dependencies - generated by hand
${BUILD_DIR}/char/char: ${BUILD_DIR}/char/char.o ${BUILD_DIR}/char/inter.o ${BUILD_DIR}/char/int_party.o ${BUILD_DIR}/char/int_storage.o ${BUILD_DIR}/common/core.o ${BUILD_DIR}/common/socket.o ${BUILD_DIR}/common/timer.o ${BUILD_DIR}/common/db.o ${BUILD_DIR}/common/lock.o ${BUILD_DIR}/common/random.o ${BUILD_DIR}/common/utils.o ${BUILD_DIR}/common/cxxstdio.o ${BUILD_DIR}/common/extract.o
${BUILD_DIR}/ladmin/ladmin: ${BUILD_DIR}/ladmin/ladmin.o ${BUILD_DIR}/common/md5calc.o ${BUILD_DIR}/common/core.o ${BUILD_DIR}/common/socket.o ${BUILD_DIR}/common/timer.o ${BUILD_DIR}/common/db.o ${BUILD_DIR}/common/random.o ${BUILD_DIR}/common/utils.o ${BUILD_DIR}/common/cxxstdio.o
${BUILD_DIR}/login/login: ${BUILD_DIR}/login/login.o ${BUILD_DIR}/common/core.o ${BUILD_DIR}/common/socket.o ${BUILD_DIR}/common/timer.o ${BUILD_DIR}/common/db.o ${BUILD_DIR}/common/lock.o ${BUILD_DIR}/common/random.o ${BUILD_DIR}/common/md5calc.o ${BUILD_DIR}/common/utils.o ${BUILD_DIR}/common/cxxstdio.o ${BUILD_DIR}/common/extract.o
${BUILD_DIR}/map/map: ${BUILD_DIR}/map/map.o ${BUILD_DIR}/map/tmw.o ${BUILD_DIR}/map/magic-interpreter-lexer.o ${BUILD_DIR}/map/magic-interpreter-parser.o ${BUILD_DIR}/map/magic-interpreter-base.o ${BUILD_DIR}/map/magic-expr.o ${BUILD_DIR}/map/magic-stmt.o ${BUILD_DIR}/map/magic.o ${BUILD_DIR}/map/map.o ${BUILD_DIR}/map/chrif.o ${BUILD_DIR}/map/clif.o ${BUILD_DIR}/map/pc.o ${BUILD_DIR}/map/npc.o ${BUILD_DIR}/map/chat.o ${BUILD_DIR}/map/path.o ${BUILD_DIR}/map/itemdb.o ${BUILD_DIR}/map/mob.o ${BUILD_DIR}/map/script.o ${BUILD_DIR}/map/storage.o ${BUILD_DIR}/map/skill.o ${BUILD_DIR}/map/skill-pools.o ${BUILD_DIR}/map/atcommand.o ${BUILD_DIR}/map/battle.o ${BUILD_DIR}/map/intif.o ${BUILD_DIR}/map/trade.o ${BUILD_DIR}/map/party.o ${BUILD_DIR}/common/core.o ${BUILD_DIR}/common/socket.o ${BUILD_DIR}/common/timer.o ${BUILD_DIR}/map/grfio.o ${BUILD_DIR}/common/db.o ${BUILD_DIR}/common/lock.o ${BUILD_DIR}/common/nullpo.o ${BUILD_DIR}/common/random.o ${BUILD_DIR}/common/md5calc.o ${BUILD_DIR}/common/utils.o ${BUILD_DIR}/common/cxxstdio.o ${BUILD_DIR}/common/extract.o
${BUILD_DIR}/tool/eathena-monitor: ${BUILD_DIR}/tool/eathena-monitor.o

# silence build warnings for code beyond my control
${BUILD_DIR}/map/magic-interpreter-lexer.o ${BUILD_DIR}/map/magic-interpreter-parser.o : override WARNINGS=

# deps.make is *NOT* automatically rebuilt normally
# but the generated source files do need to be done first
deps.make: src/map/magic-interpreter-parser.cpp src/map/magic-interpreter-lexer.cpp
	for F in `find src/ -name '*.cpp'`; do \
	    ${CXX} ${CPPFLAGS} -MM "$$F" -MT "$$(sed 's/src/$${BUILD_DIR}/;s/\.cpp/.o/' <<< "$$F")"; \
	done > deps.make
	echo '# vim: filetype=make' >> deps.make

include deps.make

prefix=/usr/local
install:
	install -d ${prefix}/bin/
	install --backup=numbered -t ${prefix}/bin/ $(wildcard ${PROGS})
