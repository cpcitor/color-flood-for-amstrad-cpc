#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "../model.h"

typedef struct player_key_to_action_t
{
        // unsigned char player_id; /* ~0 means all players */
        unsigned char previous_color;
        unsigned char confirm;
        unsigned char next_color;
} player_key_to_action_t;

extern const player_key_to_action_t player_key_to_action_array[CF_MAXPLAYERCOUNT];

typedef struct key_to_action_t
{
        char character;
        uint8_t player; // Not yet used,
        cf_cellState_t color;
} key_to_action_t;

void cf_game_next_player( cf_model_t *const this_model );
uint8_t cf_game_one_move( cf_model_t *const this_model );

#endif /* __CONTROLLER_H__ */
