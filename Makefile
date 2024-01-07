# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c pool.c
SRCH= drw.h       util.h pool.h
CONF= config.def.h keybinds.def.h
OBJ = ${SRC:.c=.o}
EXE = dwm
REBUILD = rm -f *.o
all: options default

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"
	@echo "rebuild  = ${REBUILD}"
.c.o:
	${CC} -c ${CFLAGS} $<

default: ${OBJ}
	${CC} -o ${EXE} ${OBJ} ${LDFLAGS}
	${REBUILD}

release:
	rm -rf -f -- dwm-${VERSION}
	rm -f -- dwm-${VERSION}
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README.md ${CONF} config.mk\
		${SRCH} ${SRC} transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf -f -- dwm-${VERSION}
	rm -f *.o *~ 

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
#	mkdir -p ${DESTDIR}${MANPREFIX}/man1
#	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
#	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all options release dist install uninstall
