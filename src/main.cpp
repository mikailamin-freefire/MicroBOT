#include "deauth.h"
#include "display.h"
#include "variables.h"
#include "serial.h"
#include "buttons.h"

void setup()
{
    Serial.begin(115200);
    Wire.begin(17, 16);
    pinMode(led_pin, OUTPUT);
    pinMode(extra_led_pin, OUTPUT);
    pinMode(vibrate_pin, OUTPUT);
    pinMode(button_pin, INPUT_PULLUP);
    pinMode(up_button_pin, INPUT_PULLUP);
    pinMode(down_button_pin, INPUT_PULLUP);
    digitalWrite(led_pin, LOW);
    digitalWrite(extra_led_pin, LOW);
    digitalWrite(vibrate_pin, LOW);
    last_button_state = digitalRead(12);
    last_up_button_state = digitalRead(21);
    last_down_button_state = digitalRead(5);
    WiFi.mode(WIFI_MODE_STA);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
    wifi_scan = 0;

    configTime(6 * 3600, 0, nullptr);

    sys_mode = "unlinked";
}

void loop()
{
    screen_timeout++;
    if (screen_timeout >= 2000)
    {
        display_status = false;
    }
    else
    {
        display_status = true;
    }
    serial_loop();
    if (display_status) {
        display.ssd1306_command(SSD1306_DISPLAYON);
    }
    else {
        display.clearDisplay();
        display.display();
        display.ssd1306_command(SSD1306_DISPLAYOFF);
    }
    if (sys_mode == "unlinked")
    {
        if (display_status)
            display_sub_screen("Welcome To MicroBOT", "MicroBOT",true);
    }
    else if (sys_mode == "normal")
    {
        if (display_status)
            show_normal();
    }
    else if (sys_mode == "menu")
    {
        if (display_status)
            show_main_menu();
    }
    else if (sys_mode == "about") {
        if (display_status) 
            show_about_menu();
    }
    else if (sys_mode == "deauth")
    {
        if (display_status)
            show_deauth();
    }
    else if (sys_mode == "deauth_selection")
    {
        if (deauth_target < 0)
            deauth_target = 0;
        if (display_status)
            show_deauth_selection();
    }
    else if (sys_mode == "sleep_con") {
        if (display_status) 
            display_sub_screen("Press " + String(up_button_pin) + " to confirm", "SLEEP", true);
    }
    else
    {
        if (display_status)
            display_sub_screen("Somthing was wrong", "ERROR", true);
    }

    load_buttons_loop();
}