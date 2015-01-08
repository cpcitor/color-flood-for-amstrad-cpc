#define ASSERT_CONTINUES 1

#include "platform.h"
#include "screen.h"

// FIXME should be put in a separate module to allow compile to prune it out when unneeded.

void test()
{

        assert( 0 == 1 );

        {
                uint8_t *offscreen = ( uint8_t * )0x0fff;
                screen_write( offscreen, 0xff );
        }
}
