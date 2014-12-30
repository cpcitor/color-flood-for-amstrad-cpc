localproject: astyle cf2.dsk native

SRCS := $(wildcard *.c)
SRCS_NATIVE := $(wildcard platform_native/*.c)
HDRS := $(wildcard *.h)
HDRS_NATIVE := $(wildcard platform_native/*.h)

astyle: $(wildcard *.c */*.c *.h */*.h)
	astyle --mode=c --lineend=linux --indent=spaces=8 --style=ansi --add-brackets --indent-switches --indent-classes --indent-preprocessor --convert-tabs --break-blocks --pad-oper --pad-paren-in --pad-header --unpad-paren --align-pointer=name $^ platform_*/*.c platform_*/*.h #HACK

CC = gcc -W -Wall

native: $(SRCS) $(SRCS_NATIVE)
	$(CC) $(CFLAGS) -g -o $@ $^ -Iplatform_native


cf2.dsk: platform_sdcc/cf.bas dsk $(CDTC_ENV_FOR_CPCXFS)
	( source $(CDTC_ENV_FOR_CPCXFS) ; \
	set -eu ; \
	cp cf.dsk $@.tmp ; \
	cpcxfs $@.tmp -f -t -p $< ; \
	mv -vf $@.tmp $@ ; \
	)

clean-native:
	-rm -f native

clean2:
	-rm -f */*.lk */*.noi */*.rel */*.asm */*.ihx */*.lst */*.map */*.sym */*.rst */*.bin.log */*.lib $(TARGETS)
	-rm -f */src/*.lk */src/*.noi */src/*.rel */src/*.asm */src/*.ihx */src/*.lst */src/*.map */src/*.sym */src/*.rst */src/*.bin.log
	-rm -f *.orig */*.orig

clean-full: clean clean2 clean-native 

test-sdcc: clean-full dsk2	
	arnold -drivea cf.dsk 

test-native: clean-full native
	./native

