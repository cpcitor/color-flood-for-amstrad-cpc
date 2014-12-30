#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* PLATFORM NATIVE */

#include <stdio.h>

#define dbglog(msg) fprintf(stderr, "%s", msg)
#define dbglogf(...) fprintf(stderr, __VA_ARGS__)
#define dbgvar(VARNAME, FORMAT) dbglogf(#VARNAME "=" FORMAT " ", VARNAME);
#define dbgvar_d(VARNAME) dbgvar(VARNAME, "%d");
#define dbgvar_s(VARNAME) dbgvar(VARNAME, "%s");
#define dbglog_nl() dbglog(NL);

#define silmark() fprintf(stderr, NL "== in %s ==\t", __PRETTY_FUNCTION__)
#define silmark_end() fprintf(stderr, NL "== quitting %s ==\t", __PRETTY_FUNCTION__)
#define silmsg(...) fprintf(stderr, NL "%s: ", __PRETTY_FUNCTION__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, NL);
#define silvar(VARNAME, FORMAT) silmsg(#VARNAME "= " #FORMAT NL, VARNAME);
#define NL "\012"

typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned short uint16_t;

//#define assert(...)
#include <assert.h>

#define cf_platform_init(...) (void)0

#endif /* __PLATFORM_H__ */
