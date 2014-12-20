localproject: astyle dsk native

SRCS := $(wildcard *.c) platform_*/*.c #HACK
HDRS := $(wildcard *.h)

astyle: $(SRCS) $(HDRS)
	astyle --mode=c --lineend=linux --indent=spaces=8 --style=ansi --add-brackets --indent-switches --indent-classes --indent-preprocessor --convert-tabs --break-blocks --pad-oper --pad-paren-in --pad-header --unpad-paren --align-pointer=name $^ platform_*/*.h #HACK

CC = gcc

native: $(SRCS)
	$(CC) -g -o $@ $^ -Iplatform_native

