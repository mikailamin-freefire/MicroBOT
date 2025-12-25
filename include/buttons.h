#ifndef BUTTONS_H
#define BUTTONS_H

#include "variables.h"
#include "deauth.h"
#include "display.h"
#include "functions.h"

void load_buttons_loop();

void on_main_button_pressed();
void on_up_button_pressed();
void on_down_button_pressed();

void on_main_button_released();
void on_up_button_released();
void on_down_button_released();

#endif