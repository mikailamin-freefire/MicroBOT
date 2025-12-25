#ifndef DISPLAY_H
#define DISPLAY_H

#include "variables.h"
#include "deauth.h"

void display_top_outline();
void display_body_outline();
void display_sub_screen(String title, bool center = false);
void show_normal();
void show_deauth();
void show_main_menu();
void show_deauth_selection();

#endif