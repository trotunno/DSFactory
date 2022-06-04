CC=gcc
CFLAGS=-lm -I.
CFILES= main.c common/gpbcommon.h generalpurposebuffer/generalpurposebuffer.c generalpurposebuffer/generalpurposebuffer.h queue/queue.c queue/queue.h ringbuffer/ringbuffer.c ringbuffer/ringbuffer.h stack/stack.h stack/stack.c dsfactory/dsfactory.c dsfactory/dsfactory.h

dsfact: $(CFILES)
	$(CC) -o dsfact $(CFILES) $(CFLAGS)
