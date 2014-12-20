#ifndef __MODEL_H__
#define __MODEL_H__

#include "platform.h"

#define CF_STATECOUNT 6
#define CF_MAXPLAYERCOUNT 4
#define CF_MAXGRIDSIZE 12


typedef struct cf_coordinates_t
{
        uint8_t row;
        uint8_t col;
} cf_coordinates_t;


typedef int cf_cellState_t;


typedef struct cf_grid_t
{
        cf_coordinates_t dimensions;
        cf_cellState_t cell[CF_MAXGRIDSIZE][CF_MAXGRIDSIZE];
} cf_grid_t;


typedef uint8_t cf_player_i;


typedef struct cf_model_t
{
        uint8_t playerCount;
        cf_grid_t grid;
        cf_coordinates_t playerHomes[CF_MAXPLAYERCOUNT];
        cf_player_i nextPlayer;
} cf_model_t;

void cf_grid_init( cf_grid_t *this_grid );

/** Initialize fields first ! */
void cf_model_init( cf_model_t *this_model );

void play( cf_model_t *thisModel, cf_cellState_t chosenState );

#endif /* __MODEL_H__ */
