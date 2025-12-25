#include "buttons.h"

void load_buttons_loop()
{
    if (digitalRead(button_pin) == LOW && last_button_state == HIGH)
    {
        on_main_button_pressed();
    }
    else if (digitalRead(button_pin) == HIGH && last_button_state == LOW)
    {
        on_main_button_released();
    }

    if (digitalRead(up_button_pin) == LOW && last_up_button_state == HIGH)
    {
        on_up_button_pressed();
    }
    else if (digitalRead(up_button_pin) == HIGH && last_up_button_state == LOW)
    {
        on_up_button_released();
    }

    if (digitalRead(down_button_pin) == LOW && last_down_button_state == HIGH)
    {
        on_down_button_pressed();
    }
    else if (digitalRead(down_button_pin) == HIGH && last_down_button_state == LOW)
    {
        on_down_button_released();
    }
    last_button_state = digitalRead(12);
    last_up_button_state = digitalRead(21);
    last_down_button_state = digitalRead(5);
}

void on_main_button_pressed()
{
    if (sys_mode == "unlinked")
    {
        sys_mode = "normal";
    }
    else if (sys_mode == "normal")
    {
        sys_mode = "menu";
    }
    else if (sys_mode == "menu")
    {
        if (main_menu_selection == 0)
            sys_mode = "normal";
        if (main_menu_selection == 1)
            sys_mode = "normal";
        if (main_menu_selection == 2)
            sys_mode = "normal";
        if (main_menu_selection == 3)
            scan_networks();
        if (main_menu_selection == 4)
            sys_mode = "deauth";
        if (main_menu_selection == 5)
            esp_restart();
    }
    else if (sys_mode == "deauth")
    {
        if (!is_deauth_running)
        {
            if (wifi_scan == 0)
            {
                scan_networks();
            }
            else if (deauth_target < 0)
            {
                sys_mode = "deauth_selection";
            }
            else
            {
                start_deauth(deauth_target, 0x01);
            }
        }
        else
        {
            stop_deauth();
        }
    }
    else if (sys_mode == "deauth_selection")
    {
        if (wifi_scan > 0)
        {
            sys_mode = "deauth";
        }
        else
        {
            scan_networks();
        }
    }
}

void on_up_button_pressed()
{
    if (sys_mode == "normal")
    {
    }
    else if (sys_mode == "menu")
    {
        main_menu_selection--;
        if (main_menu_selection < 0)
        {
            main_menu_selection = main_menu_count - 1;
            main_menu_scroll = main_menu_count - 4;
        }
        if (main_menu_selection < main_menu_scroll)
            main_menu_scroll = main_menu_selection;
    }
    else if (sys_mode == "deauth")
    {
        sys_mode = "deauth_selection";
    }
    else if (sys_mode == "deauth_selection")
    {
        deauth_target--;
        if (deauth_target < 0)
        {
            deauth_target = wifi_menu_count - 1;
            deauth_target_scroll = wifi_menu_count - 4;
        }
        if (deauth_target < deauth_target_scroll)
            deauth_target_scroll = deauth_target;
    }
}

void on_down_button_pressed()
{
    if (sys_mode == "normal")
    {
    }
    else if (sys_mode == "menu")
    {
        main_menu_selection++;
        if (main_menu_selection >= main_menu_count)
        {
            main_menu_selection = 0;
            main_menu_scroll = 0;
        }
        if (main_menu_selection >= main_menu_scroll + 4)
            main_menu_scroll = main_menu_selection - 3;
    }
    else if (sys_mode == "deauth")
    {
        sys_mode = "menu";
    }
    else if (sys_mode == "deauth_selection")
    {
        deauth_target++;
        if (deauth_target >= wifi_menu_count)
        {
            deauth_target = 0;
            deauth_target_scroll = 0;
        }
        if (deauth_target >= deauth_target_scroll + 4)
            deauth_target_scroll = deauth_target - 3;
    }
}

void on_main_button_released()
{
}

void on_up_button_released()
{
}

void on_down_button_released()
{
}