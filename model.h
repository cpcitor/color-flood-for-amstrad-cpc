#ifndef __MODEL_H__
#define __MODEL_H__

#include "platform.h"

enum
{
        CF_MAXPLAYERCOUNT_EXPONENT = 2,
        CF_MAXPLAYERCOUNT = ( 1 << CF_MAXPLAYERCOUNT_EXPONENT )
};
enum { CF_MAXGRIDSIZE = 24 };

typedef struct cf_coordinates_t
{
        uint8_t row;
        uint8_t col;
} cf_coordinates_t;

typedef enum cf_cellState_t
{
        CF_COLORCOUNT = 9,
        to_process = CF_COLORCOUNT,
        processed,
        CF_STATECOUNT
} cf_cellState_t;

typedef struct cf_grid_t
{
        cf_coordinates_t dimensions;
        cf_cellState_t cell[CF_MAXGRIDSIZE][CF_MAXGRIDSIZE];
} cf_grid_t;

typedef uint8_t cf_player_i;

typedef uint16_t cf_onebitpercolor_t; /* WARNING: assumes CF_COLORCOUNT <= 16 */

typedef struct cf_model_t
{
        uint8_t playerEnableBits;
        cf_grid_t grid;
        cf_coordinates_t playerHomes[CF_MAXPLAYERCOUNT];
        cf_player_i nextPlayer;
        /* Information below tine line is redundant, computed from information above. */
        cf_onebitpercolor_t allowedNextColorBits;
        uint16_t domainAreas[CF_MAXPLAYERCOUNT];
} cf_model_t;

#define is_player_enabled(model, iplayer) (((model)->playerEnableBits & (1<<(iplayer))) !=0)
#define is_player_disabled(model, iplayer) (((model)->playerEnableBits & (1<<(iplayer))) ==0)

extern cf_model_t global_model;

void cf_grid_init( cf_grid_t *this_grid );

/** Initialize fields first ! */
void cf_model_init( cf_model_t *this_model );

uint8_t cf_model_play( cf_model_t *const thisModel, cf_cellState_t const newState );
bool cf_model_is_color_allowed_for_current_player( const cf_model_t *const model, const cf_cellState_t newState );

#define color_next(color) ( ((color)+1) % CF_COLORCOUNT )
#define color_previous(color) ( ((color+CF_COLORCOUNT)-1) % CF_COLORCOUNT )

cf_cellState_t cf_model_get_player_cellstate( const cf_model_t *const this_model, cf_player_i const iplayer );

void cf_model_update_allowed_color_table( cf_model_t *const this_model );

#endif /* __MODEL_H__ */
