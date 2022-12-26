localproject: cf2.dsk stdio

full: clean clean-stdio localproject

SRCS := $(wildcard *.c)
SRCS_STDIO := $(wildcard platform_stdio/*.c)
HDRS := $(wildcard *.h)
HDRS_STDIO := $(wildcard platform_stdio/*.h)

astyle_local: $(wildcard *.c */*.c *.h */*.h)
	astyle --mode=c --lineend=linux --indent=spaces=8 --style=ansi --add-brackets --indent-switches --indent-classes --indent-preprocessor --convert-tabs --break-blocks --pad-oper --pad-paren-in --pad-header --unpad-paren --align-pointer=name $^ platform_*/*.c platform_*/*.h #HACK

CC = gcc -W -Wall -DCF_DEBUGLEVEL=$(CF_DEBUGLEVEL)

CFLAGS += "-DCF_DEBUGLEVEL=$(CF_DEBUGLEVEL)"

stdio: $(SRCS) $(SRCS_STDIO)
	$(CC) $(CFLAGS) -Wno-missing-field-initializers -g -o $@ $^ -Iplatform_stdio


cf2.dsk: platform_sdcc/cf.bas dsk $(CDTC_ENV_FOR_CPCXFS)
	( source $(CDTC_ENV_FOR_CPCXFS) ; \
	set -eu ; \
	cp cf.dsk $@.tmp ; \
	cpcxfs $@.tmp -f -t -p $< ; \
	mv -vf $@.tmp $@ ; \
	)

clean-stdio:
	-rm -f stdio

clean2:
	-rm -f */*.lk */*.noi */*.rel */*.asm */*.ihx */*.lst */*.map */*.sym */*.rst */*.bin.log */*.lib $(TARGETS)
	-rm -f */src/*.lk */src/*.noi */src/*.rel */src/*.asm */src/*.ihx */src/*.lst */src/*.map */src/*.sym */src/*.rst */src/*.bin.log
	-rm -f *.orig */*.orig

clean-full: clean clean2 clean-stdio

test-sdcc: clean-full cf.dsk
	-( arnold -at 'run"cf\n' -a cf.dsk & true ; )

test-stdio: clean-full stdio
	./stdio

doc: config_gui_dump.png

config_gui_dump.png: config_gui_dump.dot
	dot -Kfdp -n -Tpng -o "$@".tmp "$<" && mv -vf "$@".tmp "$@"

config_gui_dump.dot: stdio local.Makefile
	{ echo "digraph gui {" ; ./$< </dev/urandom 2>&1 | sed -n 's/^DOT: \(.*\)/\1/p' | fgrep -v '(nil)' ; echo "}"  ;} > "$@".tmp && mv -vf "$@".tmp "$@"
