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

typedef struct ui_element_t
{
        const uint8_t y;
        const uint8_t x;
        const ui_class_t *const class;
        const char *const text;
        void *data;
        struct ui_element_t *neighbour_up;
        struct ui_element_t *neighbour_down;
        struct ui_element_t *neighbour_left;
        struct ui_element_t *neighbour_right;
} ui_element_t;

#endif /* __WIDGET_BASE_H__ */
