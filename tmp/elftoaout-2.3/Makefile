CC = gcc
CFLAGS = -O2 -Wall

all: elftoaout

elftoaout: elftoaout.c
	$(CC) $(CFLAGS) -o elftoaout elftoaout.c

install: elftoaout
	install -m 0755 -s elftoaout /usr/bin/elftoaout
	install -m 0644 elftoaout.1 /usr/man/man1/elftoaout.1

clean:
	rm -f *~ *.[soa] core
