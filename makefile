CC=gcc
CFLAGS=-lm -Werror -I.
CFILES=main.c GeneralPurposeBuffer.c GeneralPurposeBuffer.h

gpb: main.c GeneralPurposeBuffer.c GeneralPurposeBuffer.h
	$(CC) -o gpb $(CFILES) $(CFLAGS)
