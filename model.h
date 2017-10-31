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
        red = 0,
        yellow = 1,
        green = 2,
        cyan = 3,
        blue = 4,
        magenta = 5,
        CF_COLORCOUNT,
        orange = 6,
        grey = 7,
        dark_red = 8,
        dark_yellow = 9,
        dark_green = 10,
        dark_cyan = 11,
        dark_blue = 12,
        dark_magenta = 13,
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

typedef struct cf_model_t
{
        uint8_t playerEnableBits;
        cf_grid_t grid;
        cf_coordinates_t playerHomes[CF_MAXPLAYERCOUNT];
        cf_player_i nextPlayer;
        uint16_t domainAreas[CF_MAXPLAYERCOUNT];
} cf_model_t;

#define is_player_enabled(model, iplayer) ((model->playerEnableBits & (1<<iplayer)) !=0)
#define is_player_disabled(model, iplayer) ((model->playerEnableBits & (1<<iplayer)) ==0)

extern cf_model_t global_model;

void cf_grid_init( cf_grid_t *this_grid );

/** Initialize fields first ! */
void cf_model_init( cf_model_t *this_model );

uint8_t cf_model_play( cf_model_t *const thisModel, cf_cellState_t const newState );

cf_cellState_t cf_model_get_current_player_state( const cf_model_t *const this_model, uint8_t const iplayer );

#endif /* __MODEL_H__ */
