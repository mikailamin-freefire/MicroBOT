#include "functions.h"

void string_to_mac(const char *mac_str, uint8_t *mac)
{
    for (int i = 0; i < 6; i++)
    {
        mac[i] = strtoul(mac_str + (i * 3), nullptr, 16);
    }
}

String mac_to_string(const uint8_t *mac)
{
    char buf[18];
    sprintf(
        buf,
        "%02X:%02X:%02X:%02X:%02X:%02X",
        mac[0],
        mac[1],
        mac[2],
        mac[3],
        mac[4],
        mac[5]);
    return String(buf);
}

void scan_networks(bool is_existed)
{
    display_sub_screen("Scanning for WiFi...");
    if (is_existed)
    {
        if (wifi_scan == 0)
            wifi_scan = WiFi.scanNetworks();
    }
    else
    {
        wifi_scan = WiFi.scanNetworks();
    }
    JsonDocument ndoc;
    JsonArray networks = ndoc["networks"].to<JsonArray>();
    wifi_menu_count = 0;
    for (int i = 0; i < wifi_scan; i++)
    {
        JsonObject network = networks.add<JsonObject>();
        network["ssid"] = WiFi.SSID(i);
        network["rssi"] = WiFi.RSSI(i);
        network["bssid"] = WiFi.BSSIDstr(i);
        network["channel"] = WiFi.channel(i);
        network["encryption"] = WiFi.encryptionType(i);
        if (i < 100)
        {
            wifi_menu[wifi_menu_count] = WiFi.SSID(i);
            wifi_menu_count++;
        }
    }
    String output;
    serializeJson(ndoc, output);
    Serial.println(output);
}