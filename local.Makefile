localproject: astyle dsk2 native

SRCS := $(wildcard *.c)
SRCS_NATIVE := $(wildcard platform_native/*.c)
HDRS := $(wildcard *.h)
HDRS_NATIVE := $(wildcard platform_native/*.h)

astyle: $(wildcard *.c */*.c *.h */*.h)
	astyle --mode=c --lineend=linux --indent=spaces=8 --style=ansi --add-brackets --indent-switches --indent-classes --indent-preprocessor --convert-tabs --break-blocks --pad-oper --pad-paren-in --pad-header --unpad-paren --align-pointer=name $^ platform_*/*.h #HACK

CC = gcc

native: $(SRCS) $(SRCS_NATIVE)
	$(CC) -g -o $@ $^ -Iplatform_native


dsk2: platform_sdcc/cf.bas dsk $(CDTC_ENV_FOR_IDSK)
	( source $(CDTC_ENV_FOR_IDSK) ; \
	iDSK cf.dsk -f -i $< -t 0 ; \
	)

clean-native:
	-rm -f native

clean2:
	-rm -f */*.lk */*.noi */*.rel */*.asm */*.ihx */*.lst */*.map */*.sym */*.rst */*.bin.log */*.lib $(TARGETS)
	-rm -f */src/*.lk */src/*.noi */src/*.rel */src/*.asm */src/*.ihx */src/*.lst */src/*.map */src/*.sym */src/*.rst */src/*.bin.log

