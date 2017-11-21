#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "../model.h"

typedef struct key_to_action_t
{
        char character;
        uint8_t player; // Not yet used,
        cf_cellState_t color;
} key_to_action_t;

enum {key_to_action_count = CF_COLORCOUNT };

extern const key_to_action_t const key_to_action[key_to_action_count];

uint8_t cf_game_one_move( cf_model_t *const this_model );

#endif /* __CONTROLLER_H__ */
