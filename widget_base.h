#ifndef  __WIDGET_BASE_H__
#define __WIDGET_BASE_H__

#include "platform.h"

struct ui_element_t;

typedef void ui_draw_function_t( const struct ui_element_t *const element ); //, uiState_t *uiState, bool isActive );

typedef void ui_user_action_function_t( const struct ui_element_t *const element ); //, uiState_t *uiState );

typedef struct ui_class_t
{
        ui_draw_function_t *draw_func;
        ui_user_action_function_t *action_func;
} ui_class_t;

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
        const uint8_t data;
        const struct ui_element_t *const neighbours[neighbour_count];  // declare neighbours as array neighbour_count of pointer to const ui_element_t
} ui_element_t;

#endif /* __WIDGET_BASE_H__ */
