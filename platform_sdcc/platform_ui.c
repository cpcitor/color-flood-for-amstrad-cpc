#include <cfwi/cfwi.h>

#include "platform.h"

void pause()
{
        cfwi_txt_str0_output( "(key?" );
        fw_km_wait_key();
        cfwi_txt_str0_output( "ok)" NL );
}
