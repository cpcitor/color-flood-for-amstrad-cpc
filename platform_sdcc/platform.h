#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* PLATFORM SDCC */

#include <stdio.h>

#include <cfwi/cfwi.h>

#define dbglog(msg) cfwi_txt_str0_output(msg)
#define dbglogf(...) printf(__VA_ARGS__)
#define dbgvar(VARNAME, FORMAT) dbglogf(#VARNAME "=" FORMAT NL, VARNAME);
#define dbgvar_d(VARNAME) dbgvar(VARNAME, "%d");
#define dbgvar_s(VARNAME) dbgvar(VARNAME, "%s");
#define dbglog_nl() dbglog(NL);

#define silmark()
#define silmark_end()
#define silmsg(...) silmark(); printf(__VA_ARGS__)
#define silvar(VARNAME, FORMAT) silmsg(#VARNAME "= " #FORMAT NL, VARNAME);
#define NL "\015\012"

/* SDCC types */
typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned short uint16_t;
typedef signed short sint16_t;

//#define assert(...)
#include "sg_assert.h"

#include "screen.h"

void cf_platform_init();

// for memcpy
#include <string.h>
#define ASSIGN(dst, src) memcpy( (&(dst)), (&(src)), sizeof(src) )

#endif /* __PLATFORM_H__ */
