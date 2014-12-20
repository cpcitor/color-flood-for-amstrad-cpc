localproject: astyle dsk 

SRCS := $(wildcard *.c)
HDRS := $(wildcard *.h)

astyle: $(SRCS) $(HDRS)
	astyle --mode=c --lineend=linux --indent=spaces=8 --style=ansi --add-brackets --indent-switches --indent-classes --indent-preprocessor --convert-tabs --break-blocks --pad-oper --pad-paren-in --pad-header --unpad-paren --align-pointer=name $^
