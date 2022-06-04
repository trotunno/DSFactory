CC=gcc
CFLAGS=-lm -I.
CFILES= main.c common/gpbcommon.h generalpurposebuffer.c generalpurposebuffer.h queue/queue.c queue/queue.h ringbuffer/ringbuffer.c ringbuffer/ringbuffer.h stack/stack.h stack/stack.c

executable: $(CFILES)
	$(CC) -o executable $(CFILES) $(CFLAGS)
