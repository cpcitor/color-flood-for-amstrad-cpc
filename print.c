#include "platform.h"

// https://stackoverflow.com/questions/11975780/can-putchar-print-an-integer

void pr_uint( unsigned int n )
{
        if ( n / 10 != 0 )
        {
                pr_uint( n / 10 );
        }

        platform_print_char_safe( ( n % 10 ) + '0' );
}

/* void pr_int( int n ) */
/* { */
/*         if ( n < 0 ) */
/*         { */
/*                 platform_print_char_safe( '-' ); */
/*                 n = -n; */
/*         } */

/*         pr_uint( ( unsigned int ) n ); */
/* } */

/*

        {
                int i;

                for ( i = 0; i <= 255; i++ )
                {
                        pr_uint( i );

                        if ( ( i & 0x0f ) == 0 )
                        {
                                cf_pause();
                        }
                }
        }
*/
