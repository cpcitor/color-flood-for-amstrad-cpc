#define ASSERT_CONTINUES 1

#include "platform.h"
#include "screen.h"

void test()
{

        assert( 0 == 1 );

        {
                uint8_t *offscreen = ( uint8_t * )0x0fff;
                screen_write( offscreen, 0xff );
        }
}
