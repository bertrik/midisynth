CFLAGS = -W -Wall -O2 -std=c99
LDFLAGS = -lm

all: notestable.c

notestable.c: gennotes
	./gennotes >$@

gennotes: gennotes.c

clean:
	rm -f gennotes
	rm -f notestable.c

