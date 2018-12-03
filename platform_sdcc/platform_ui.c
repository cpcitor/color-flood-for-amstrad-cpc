#include <cfwi/cfwi.h>

#include "platform.h"

#ifndef NDEBUG

void cf_pause()
{
        cfwi_txt_str0_output( "?" );
        fw_km_wait_key();
}

void cf_pause_message( char *msg )
{
        cfwi_txt_str0_output( msg );
        cf_pause();
}

#endif /* NDEBUG */
