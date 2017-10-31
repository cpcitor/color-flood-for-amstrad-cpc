#ifndef __MODEL_PODIUM_H__
#define __MODEL_PODIUM_H__

#include "platform.h"
#include "model.h"

#define CF_PODIUM_ROW_COUNT CF_MAXPLAYERCOUNT
#define CF_PODIUM_SEATS_PER_ROW CF_MAXPLAYERCOUNT
#define CF_PODIUM_EMPTY_SEATS_VALUE CF_MAXPLAYERCOUNT

/**

An empty podium seat holds value CF_MAXPLAYERCOUNT.

*/
typedef struct
{
        uint16_t area;
        cf_player_i seat[CF_PODIUM_SEATS_PER_ROW];
} cf_podium_row_t;


/** At game end, we compute podium rows, to account for all possible
* draw-game cases.

* Although technically, only the first row of the podium may hold all
* players, the second may hold at most all-minus-one players, the
* third all-minus-two players and so on, we take a simple model with a
* podium where each row has enough room for all players.
*/
typedef struct
{
        cf_podium_row_t row[CF_PODIUM_ROW_COUNT];
} cf_podium_t;

void cf_model_podium_init( cf_podium_t *this_podium );
void cf_model_podium_compute( cf_podium_t *const this_podium, const cf_model_t *const this_model );
void cf_view_print_podium( const cf_podium_t *const this_podium );

#endif /* __MODEL_PODIUM_H__ */
