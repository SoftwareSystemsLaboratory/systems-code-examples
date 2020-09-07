# Makefile for the hello driver.
PROG=	time
SRCS=	time.c

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+=	-ldriver -lsys

MAN=

BINDIR?= /usr/sbin

CPPFLAGS+= -D_SYSTEM=1

.include <bsd.prog.mk>
