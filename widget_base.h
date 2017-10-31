#ifndef  __WIDGET_BASE_H__
#define __WIDGET_BASE_H__

#include "platform.h"

struct ui_element_t;

typedef void ui_draw_function_t( struct ui_element_t *element ); //, uiState_t *uiState, bool isActive );

typedef void ui_user_action_function_t( struct ui_element_t *element ); //, uiState_t *uiState );

typedef struct ui_class_t
{
        ui_draw_function_t *draw_func;
        ui_user_action_function_t *action_func;
} ui_class_t;

/*typedef struct ui_element_neighbourhood_t
{
        struct ui_element_t *up;
        struct ui_element_t *down;
        struct ui_element_t *left;
        struct ui_element_t *right;
        } ui_element_neighbourhood_t;*/

enum { neighbour_count = 4 };

enum neighbour_order
{
        neighbour_up = 0,
        neighbour_down = 1,
        neighbour_left = 2,
        neighbour_right = 3,
};

typedef struct ui_element_t
{
        const uint8_t y;
        const uint8_t x;
        const ui_class_t *const class;
        const char *const text;
        void *data;
        struct ui_element_t *neighbours[neighbour_count];
} ui_element_t;

#endif /* __WIDGET_BASE_H__ */
