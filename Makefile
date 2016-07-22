CFLAGS = -W -Wall -O2 -std=c99
LDFLAGS = -lm

all: notestable.c

notestable.c: gennotes Makefile
	./gennotes 32000 >$@

gennotes: gennotes.c

clean:
	rm -f gennotes
	rm -f notestable.c

test:
	$(CC) $(CFLAGS) $(LDFLAGS) testmsg.c midisynth/midiproc.c -o testmsg
	./testmsg


