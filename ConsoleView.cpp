/*
 * ConsoleView.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: gdbeckstein
 */

#include "ConsoleView.h"

#if MBED_CONF_LVGL_ELEMENTS_USE_CONSOLE_VIEW

#define CONSOLE_COLOR_INFO LV_COLOR_SILVER//LV_COLOR_MAKE()
#define CONSOLE_COLOR_WARNING LV_COLOR_MAKE(251, 134, 17);
#define CONSOLE_COLOR_ERROR LV_COLOR_RED//LV_COLOR_MAKE()

ConsoleView::ConsoleView(lv_obj_t* parent, int16_t number_of_lines) : num_lines(number_of_lines)
{
	// Create the styles
	lv_style_copy(&console_style, &lv_style_plain);
	console_style.body.main_color = LV_COLOR_BLACK;
	console_style.body.grad_color = LV_COLOR_BLACK;
	console_style.body.border.color = LV_COLOR_BLACK;
	console_style.body.border.width = 0;
	console_style.body.padding.hor = 0;
	console_style.body.padding.inner = 0;
	console_style.body.padding.ver = 0;
	console_style.text.font = &MBED_CONF_LVGL_ELEMENTS_CONSOLE_VIEW_DEFAULT_FONT;
	console_style.text.color = LV_COLOR_WHITE;

	lv_style_copy(&info_style, &console_style);
	info_style.text.color = CONSOLE_COLOR_INFO;

	lv_style_copy(&warning_style, &console_style);
	warning_style.text.color = CONSOLE_COLOR_WARNING;

	lv_style_copy(&error_style, &console_style);
	error_style.text.color = CONSOLE_COLOR_ERROR;

	// Create the main container
	container = lv_cont_create(parent, NULL);
	lv_obj_set_style(container, &console_style);
	lv_cont_set_layout(container, LV_LAYOUT_COL_L);
	lv_cont_set_fit(container, false, true);

	// Create all the children objects
	lines = new lv_obj_t*[number_of_lines]();
	for(int i = 0; i < number_of_lines; i++)
	{
		lines[i] = lv_label_create(container, NULL);
		lv_obj_set_style(lines[i], &console_style);
		lv_obj_set_width(lines[i], lv_obj_get_width(container));
		lv_label_set_long_mode(lines[i], LV_LABEL_LONG_DOT);
		lv_label_set_text(lines[i], "");
	}

}

ConsoleView::~ConsoleView() {

	// Delete the main container (will delete all of its children)
	lv_obj_del(container);
	container = NULL;

	// Delete the lines list
	delete[] lines;
	lines = NULL;

}

void ConsoleView::print(const char* str) {
	add_text(str, &console_style);
}

void ConsoleView::info(const char* str) {
	add_text(str, &info_style);
}

void ConsoleView::warning(const char* str) {
	add_text(str, &warning_style);
}

void ConsoleView::error(const char* str) {
	add_text(str, &error_style);
}

void ConsoleView::show(void) {
	lv_obj_set_hidden(container, false);
}

void ConsoleView::hide(void) {
	lv_obj_set_hidden(container, true);
}

void ConsoleView::set_position(int16_t x, int16_t y) {
	lv_obj_set_pos(container, x, y);
}

void ConsoleView::set_width(int16_t w) {
	lv_obj_set_width(container, w);
	for(int i = 0; i < num_lines; i++)
	{
		lv_obj_set_width(lines[i], lv_obj_get_width(container));
	}
}

void ConsoleView::set_font(lv_font_t* font) {
	console_style.text.font = font;
	info_style.text.font = font;
	warning_style.text.font = font;
	error_style.text.font = font;
}

void ConsoleView::add_text(const char* str, lv_style_t* style) {

	// Shift all the text up one label and apply styles
	for(int i = 0; i < num_lines-1; i++)
	{
		lv_label_set_text(lines[i], lv_label_get_text(lines[i+1]));
		lv_obj_set_style(lines[i], lv_obj_get_style(lines[i+1]));
	}

	// Add new line of text and its style
	lv_label_set_text(lines[num_lines-1], str);
	lv_obj_set_style(lines[num_lines-1], style);
}

lv_obj_t* ConsoleView::get_obj(void) {
	return container;
}

#endif
