#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_wifi_types.h>
#include <ArduinoJson.h>
#include "time.h"
#include <esp_sleep.h>

#define screen_width 128
#define screen_height 64
#define oled_reset -1

#define led_pin 2
#define extra_led_pin 25
#define button_pin 12
#define up_button_pin 21
#define down_button_pin 5
#define vibrate_pin 15

bool is_linked = false;
int link_id = 0000;

int last_button_state = HIGH;
int last_up_button_state = HIGH;
int last_down_button_state = HIGH;

int screen_timeout = 0;

Adafruit_SSD1306 display(screen_width, screen_height, &Wire, oled_reset);

String sys_mode = "normal";
bool display_status = true;

String main_menu[] = {
    "<- HOME ->",
    "# WiFi",
    "# BlueTooth",
    "# Scan WiFi",
    "# Deauth",
    "# Restart",
    "# Sleep",
    "# About"
};
int main_menu_count = 8;
int main_menu_selection = 0;
int main_menu_scroll = 0;

String about_menu[] = {
    "Name: MicroBOT",
    "Author: MIKAILAMIN",
    "screen_timeout"
};
int about_menu_count = 3;
int about_menu_selection = 0;
int about_menu_scroll = 0;

String wifi_menu[100];
int wifi_menu_count = 0;

int deauth_target = -1;
int deauth_target_scroll = 0;

int wifi_scan = 0;

#endif