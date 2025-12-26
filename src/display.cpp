#include "display.h"

int get_center_x(String text)
{
    int16_t xh, yh;
    uint16_t wh, hh;
    display.getTextBounds(text, 0, 0, &xh, &yh, &wh, &hh);

    return (screen_width - wh) / 2;
}

void display_top_outline()
{
    display.drawLine(0, 0, 127, 0, WHITE);
    display.drawLine(0, 0, 0, 15, WHITE);
    display.drawLine(127, 0, 127, 15, WHITE);
    display.drawLine(0, 15, 127, 15, WHITE);
}

void display_body_outline()
{
    display.drawLine(0, 16, 127, 16, WHITE);
    display.drawLine(0, 16, 0, 63, WHITE);
    display.drawLine(127, 16, 127, 63, WHITE);
    display.drawLine(0, 63, 127, 63, WHITE);
}

void display_sub_screen(String title, bool center)
{
    display.clearDisplay();
    display_top_outline();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    int16_t xh, yh;
    uint16_t wh, hh;
    display.getTextBounds(title, 0, 0, &xh, &yh, &wh, &hh);
    int16_t cx_header = center ? ((128 - wh) / 2) - 1 : 3;
    display.setCursor(cx_header, 4);
    display.println(title);
    display.setTextSize(2);
    int16_t x, y;
    uint16_t w, h;
    const char *logo = "MicroBOT";
    display.getTextBounds(logo, 0, 0, &x, &y, &w, &h);
    int16_t cx = (128 - w) / 2;
    int16_t cy = (64 - 16 - h) / 2 + 16;
    display.setCursor(cx - 1, cy - 1);
    display_body_outline();
    display.println(logo);
    display.display();
}

void show_normal()
{
    display.clearDisplay();

    display_top_outline();
    display_body_outline();

    display.setTextColor(WHITE);
    display.setTextSize(1);

    const char *title = "MicroBOT";

    int16_t xt, yt;
    uint16_t wt, ht;
    display.getTextBounds(title, 0, 0, &xt, &yt, &wt, &ht);

    int16_t cx_title = (screen_width - wt) / 2;
    display.setCursor(cx_title, 4);
    display.println(title);

    int hour, minute, second;
    struct tm timeinfo;
    time_t now;
    time(&now);
    localtime_r(&now, &timeinfo);

    hour = timeinfo.tm_hour;
    minute = timeinfo.tm_min;
    second = timeinfo.tm_sec;

    String apm = "AM";
    if (hour >= 12)
    {
        apm = "PM";
        if (hour > 12)
            hour -= 12;
    }
    if (hour == 0)
        hour = 12;

    char hm[9];
    snprintf(hm, sizeof(hm), "%02d:%02d:%02d", hour, minute, second);

    display.setTextSize(2);

    int16_t xh, yh;
    uint16_t wh, hh;
    display.getTextBounds(hm, 0, 0, &xh, &yh, &wh, &hh);

    int16_t cx = (screen_width - wh) / 2;
    int16_t cy = ((screen_height - 16) - hh) / 2 + 16;

    display.setCursor(cx, cy);
    display.println(hm);

    display.setTextSize(1);

    int16_t xs, ys;
    uint16_t ws, hs;
    display.getTextBounds(apm, 0, 0, &xs, &ys, &ws, &hs);

    display.setCursor(screen_width - ws - 2, screen_height - hs - 2);
    display.println(apm);

    display.display();
}

void show_deauth()
{
    display.clearDisplay();

    display_top_outline();
    display_body_outline();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    String mac = "Scan required!";
    if (wifi_scan == 0)
    {
        mac = "Scan required!";
    }
    else if (deauth_target < 0)
    {
        mac = "Select a target (UP)";
    }

    if (wifi_scan > 0 && deauth_target >= 0 && deauth_target < wifi_scan)
        mac = WiFi.BSSIDstr(deauth_target);

    int16_t xh, yh;
    uint16_t wh, hh;
    display.getTextBounds(mac, 0, 0, &xh, &yh, &wh, &hh);

    int16_t cx_header = (screen_width - wh) / 2;
    display.setCursor(cx_header, 4);
    display.println(mac);

    display.setTextColor(WHITE);
    display.setTextSize(2);

    const char *title = "Deauth";

    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(title, 0, 0, &x1, &y1, &w, &h);

    int16_t cx = (screen_width - w) / 2;
    int16_t cy = ((screen_height - 16) - h) / 2 + 16;

    display.setCursor(cx - 1, cy - 1);
    display.println(title);

    display.setTextSize(1);
    const char *status_text = is_deauth_running ? "Activated" : "Deactivated";

    int16_t x2, y2;
    uint16_t w2, h2;
    display.getTextBounds(status_text, 0, 0, &x2, &y2, &w2, &h2);

    display.setCursor(screen_width - w2 - 2, screen_height - h2 - 2);
    display.println(status_text);

    display.display();
}

void show_main_menu()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextWrap(false);
    display_top_outline();

    display.setTextColor(WHITE);
    display.setCursor(get_center_x("Main Menu"), 4);
    display.print("Main Menu");

    for (int i = 0; i < 4; i++)
    {
        int item_index = main_menu_scroll + i;
        if (item_index >= main_menu_count)
            break;

        int y = 16 + (i * 12);

        if (item_index == main_menu_selection)
        {
            display.drawRect(0, y, 128, 12, WHITE);
        }
        display.setCursor(2, y + 2);
        if (item_index == 0)
            display.setCursor(get_center_x(main_menu[item_index]), y + 2);
        display.print(main_menu[item_index]);
    }

    display.display();
}

void show_about_menu()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextWrap(false);
    display_top_outline();

    display.setTextColor(WHITE);
    display.setCursor(get_center_x("About Me"), 4);
    display.print("About Me");

    for (int i = 0; i < 4; i++)
    {
        int item_index = about_menu_scroll + i;
        if (item_index >= about_menu_count)
            break;

        int y = 16 + (i * 12);

        if (item_index == about_menu_selection)
        {
            display.drawRect(0, y, 128, 12, WHITE);
        }
        display.setCursor(2, y + 2);
        if (item_index == 2)
        {
            display.print("Screen Timeout: " + String(screen_timeout));
        }
        else
        {
            display.print(about_menu[item_index]);
        }
    }

    display.display();
}

void show_deauth_selection()
{
    display.clearDisplay();
    if (wifi_scan > 0)
    {
        display.setTextSize(1);
        display.setTextWrap(false);
        display_top_outline();

        display.setTextColor(WHITE);
        display.setCursor(2, 4);
        display.print("Total: " + String(wifi_menu_count) + " (" + String(deauth_target + 1) + ")");

        for (int i = 0; i < 4; i++)
        {
            int item_index = deauth_target_scroll + i;
            if (item_index >= wifi_menu_count)
                break;

            int y = 16 + (i * 12);

            if (item_index == deauth_target)
            {
                display.drawRect(0, y, 128, 12, WHITE);
            }

            display.setCursor(2, y + 2);
            display.print(String(item_index + 1) + ". " + wifi_menu[item_index]);
        }
    }
    else
    {
        display_top_outline();
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(get_center_x("Scan required!"), 4);
        display.print("Scan required!");
        display.setCursor(0, 16);
        display.println("No network found to");
        display.println("select deauth!");
        display.setCursor(0, 42);
        display.println("Press OK to start");
        display.println("scanning!");
    }
    display.display();
}