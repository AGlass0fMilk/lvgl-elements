CPPSRCS += ConsoleView.cpp

DEPPATH += --dep-path lvgl-elements
VPATH += :lvgl-elements

CFLAGS += "-I$(LVGL_DIR)/lvgl-elements"