#ifndef __LOG_H__
#define __LOG_H__

/* PLATFORM NATIVE */

#include <platform.h> // defines NL platform_print_formatted_string and platform_print_plain_string

#define dbglog(msg) platform_print_plain_string(msg)
#define dbglogf(...) platform_print_formatted_string(__VA_ARGS__)

#define dbgvar(VARNAME, FORMAT) dbglogf(#VARNAME "=" FORMAT " ", VARNAME);
#define dbgvar_d(VARNAME) dbgvar(VARNAME, "%d");
#define dbgvar_s(VARNAME) dbgvar(VARNAME, "%s");
#define dbglog_nl() dbglog(NL);

#ifdef __GNUC__

#define silmark() platform_print_formatted_string( NL "== in %s ==\t", __PRETTY_FUNCTION__)
#define silmark_end() platform_print_formatted_string( NL "== quitting %s ==\t", __PRETTY_FUNCTION__)
#define silmsg(...) platform_print_formatted_string( NL "%s: ", __PRETTY_FUNCTION__); platform_print_formatted_string( __VA_ARGS__); platform_print_formatted_string( NL);
#define silvar(VARNAME, FORMAT) silmsg(#VARNAME "= " #FORMAT NL, VARNAME);

#else /* __GNUC__ */

#define silmark()
#define silmark_end()
#define silmsg(...) silmark(); platform_print_formatted_string(__VA_ARGS__)
#define silvar(VARNAME, FORMAT) silmsg(#VARNAME "= " #FORMAT NL, VARNAME);

#endif /* __GNUC__ */

#endif /* __LOG_H__ */
