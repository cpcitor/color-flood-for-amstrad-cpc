#ifndef __WIDGET_CLASSES_H__
#define __WIDGET_CLASSES_H__

#include "widget_base.h"

void draw_window( char *title, uint8_t top, uint8_t height, uint8_t left, uint8_t width );

void radioButtonDraw( const ui_element_t *const element );
void checkBoxDraw( const ui_element_t *const element );
//void textInputDraw( const ui_element_t * const element );
void buttonDraw( const ui_element_t *const element );

void radioButtonAction( const ui_element_t *const source );
void checkBoxAction( const ui_element_t *const source );
void buttonAction( const ui_element_t *const source );

extern const ui_class_t radioButtonClass;
extern const ui_class_t checkBoxClass;
//extern ui_class_t textInputClass;
extern const ui_class_t buttonClass;

void config_gui_mark_selected_element( const ui_element_t *const element, char c );

#define ui_element_draw(ui_element) do { const ui_element_t *const ui_e_t = (ui_element); (((ui_e_t)->class->draw_func)(ui_e_t)); } while (0)

#endif /* __WIDGET_CLASSES_H__ */
