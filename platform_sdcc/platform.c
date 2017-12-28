#include "platform.h"
#include "screen.h"
#include "../log.h"
#include "stdlib.h"

#include <cfwi/cfwi.h>

#include "platform_view.h"

static const ink_vector16 game_palette =
{
        {
                hardware_color_r0_g0_b0_black,
                hardware_color_r0_g0_b0_black,
                hardware_color_r2_g2_b2_bright_white,
                hardware_color_r2_g0_b0_bright_red,
                hardware_color_r2_g1_b0_orange,
                //rgb_to_cpc_color( 2, 2, 0 ), yellow is too close to green
                hardware_color_r0_g2_b0_bright_green, // not 0,2,1 too bright
                hardware_color_r0_g2_b2_bright_cyan,
                hardware_color_r0_g0_b2_bright_blue, // not 0,1,2 which would be too similar to 1,0,2
                //rgb_to_cpc_color( 1, 0, 2 ), too similar to 0,0,2 on a real CPC

                // rgb_to_cpc_color( 2, 0, 1 ), too aggressive
                //rgb_to_cpc_color( 1, 2, 0 ), too similar to 0,2,1

                hardware_color_r2_g0_b2_bright_magenta,

//      hardware_color_r1, 0, 1 ), too similar to 1,0,2
                hardware_color_r0_g1_b1_cyan,
                hardware_color_r1_g1_b0_yellow,
                hardware_color_r1_g0_b1_magenta
                /* #if CF_PASTEL_COLORS */
                /*         16, 25, 22, 23, 14, 17, */
                /* #else /\* CF_PASTEL_COLORS *\/ */
                /*         6, 24, 18, 20, 2, 8, */
                /* #endif /\* CF_PASTEL_COLORS *\/ */
                /*        15, 13,
                          3, 12, 9, 10, 1, 4*/
        }
};

void cf_platform_init()
{
        fw_scr_initialise();
        fw_gra_initialise();
        fw_scr_set_mode( 1 );

        {
                long unsigned int cpctime = fw_kl_time_please();
                dbgvar_lu( 0, cpctime );
                srand( cpctime );
        }
}

enum
{
        lowest_redefined_character = 128
};

void cf_platform_prepare_for_game_board()
{
        fw_scr_set_mode( 0 );
        fw_txt_initialise();
        cf_screen_line_to_ptr_init();

        fw_mc_set_inks( &game_palette );

        {
                //enum { char_matrix_definition_char_size }
                static const unsigned char const chardef[] =
                {
                        /*25,
                        0x80,
                        0b01001100,
                        0b10010010,
                        0b10010110,
                        0b10011010,
                        0b11010010,
                        0b10010010,
                        0b10001100,
                        0b00000000,*/
                        25,
                        0x81,
                        0b01000100,
                        0b10001100,
                        0b10010100,
                        0b10000100,
                        0b11000100,
                        0b10000100,
                        0b10011110,
                        0b00000000,
                        25,
                        0x82,
                        0b01011100,
                        0b10000010,
                        0b10000010,
                        0b10001100,
                        0b11010000,
                        0b10010000,
                        0b10011110,
                        0b00000000,
                        25,
                        0x83,
                        0b01011100,
                        0b10000010,
                        0b10000010,
                        0b10001100,
                        0b11000010,
                        0b10000010,
                        0b10011100,
                        0b00000000,
                        25,
                        0x87,
                        0b01011110,
                        0b10000010,
                        0b10000100,
                        0b10001000,
                        0b11001000,
                        0b10010000,
                        0b10010000,
                        0b00000000,
                        25,
                        0x88,
                        0b01001100,
                        0b10010010,
                        0b10010010,
                        0b10001100,
                        0b11010010,
                        0b10010010,
                        0b10001100,
                        0b00000000,
                        25,
                        0x89,
                        0b01001100,
                        0b10010010,
                        0b10010010,
                        0b10001110,
                        0b11000010,
                        0b10000010,
                        0b10011100,
                        0b00000000,
                };

                int chartogo = sizeof( chardef ) / sizeof( char );
                const char *p_c = chardef;

                extern void aftercode;
                const fw_txt_character_matrix_t *chartable = ( fw_txt_character_matrix_t * )( &aftercode );

                fw_txt_set_m_table( chartable, false, lowest_redefined_character );


                while ( chartogo > 0 )
                {
                        fw_txt_output( *p_c );
                        p_c++;
                        chartogo--;
                }
        }
}
