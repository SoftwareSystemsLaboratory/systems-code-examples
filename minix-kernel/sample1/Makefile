DRIVER = sample1
u = /usr
i = $u/include
s = $i/sys
m = $i/minix
b = $i/ibm
d = ..
CC = exec cc
CFLAGS = -I$i $(CPROFILE)
LDFLAGS = -i -L../libdriver
LIBS = -ldriver -lsys
OBJ = sample1.o

all build: $(DRIVER)

$(DRIVER): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ) $(LIBS)
	install -S 128k $(DRIVER)

install: /usr/sbin/$(DRIVER)
/usr/sbin/$(DRIVER): $(DRIVER)
	install -o root -cs $? $@

clean:
	rm -f *.o $(DRIVER)

depend:
	mkdep "$(CC) -E $(CPPFLAGS)" *.c > .depend

include .depend

