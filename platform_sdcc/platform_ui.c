#include <cfwi/cfwi.h>

void pause()
{
        cfwi_txt_str0_output( "(press-any-key..." );
        fw_km_wait_key();
        cfwi_txt_str0_output( "ok)" );
}
