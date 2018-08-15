/*
 * ConsoleView.h
 *
 *  Created on: Aug 15, 2018
 *      Author: gdbeckstein
 */

#ifndef LVGL_ELEMENTS_CONSOLEVIEW_H_
#define LVGL_ELEMENTS_CONSOLEVIEW_H_

#include "lvgl.h"
#include "string.h"

#if MBED_CONF_LVGL_ELEMENTS_USE_CONSOLE_VIEW

// A simple console view for displaying debug information
class ConsoleView
{

public:

	/**
	 * Construct a console view
	 * @param[in] parent The parent object to attach this view to
	 * @param[in] number_of_lines Maximum number of text lines to show
	 */
	ConsoleView(lv_obj_t* parent, int16_t number_of_lines);
	virtual ~ConsoleView();

	void print(std::string str);
	void info(std::string str);
	void warning(std::string str);
	void error(std::string str);

	void show(void);
	void hide(void);

	void set_position(int16_t x, int16_t y);

	void set_font(lv_font_t* font);

protected:

	void add_text(std::string str, lv_style_t* style);

protected:

	lv_style_t console_style;
	lv_style_t info_style;
	lv_style_t warning_style;
	lv_style_t error_style;

	lv_obj_t* container;
	lv_obj_t** lines;
	uint16_t num_lines;

};

#endif

#endif /* LVGL_ELEMENTS_CONSOLEVIEW_H_ */
