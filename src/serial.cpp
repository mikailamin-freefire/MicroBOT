#include "serial.h"

void serial_loop()
{
    if (Serial.available())
    {
        String data = Serial.readStringUntil('\n');
        data.trim();

        JsonDocument doc;
        deserializeJson(doc, data);

        if (doc["link_id"].is<int>()) {
            is_linked = true;
            link_id = doc["link_id"].as<int>();
        }
        if (doc["mode"].is<String>())
        {
            sys_mode = doc["mode"].as<String>();
        }
        if (doc["sync_time"].is<long>())
        {
            long ms = doc["sync_time"].as<long>();
            struct timeval tv;
            tv.tv_sec = ms;
            tv.tv_usec = (ms % 1000);
            settimeofday(&tv, nullptr);
        }
        if (doc["deauth_target"].is<int>())
        {
            if (is_deauth_running && doc["deauth_target"].as<int>() != deauth_target)
            {
                stop_deauth();
                start_deauth(doc["deauth_target"].as<int>(), 0x01);
            }
            deauth_target = doc["deauth_target"].as<int>();
        }
        if (doc["deauth_run"].is<bool>())
        {
            if (doc["deauth_run"].as<bool>())
            {
                if (deauth_target >= 0 && wifi_scan > 0 && wifi_scan > deauth_target)
                {
                    if (!is_deauth_running)
                        start_deauth(deauth_target, 0x01);
                }
                else
                {
                    String edoc_out;
                    JsonDocument edoc;
                    edoc["error"] = "Target not found!";
                    serializeJson(edoc, edoc_out);
                    Serial.println(edoc_out);
                }
            }
            else
            {
                stop_deauth();
            }
        }
        if (doc["wifi_scan"].is<bool>() && doc["wifi_scan"].as<bool>())
        {
            if (doc["wifi_scan_is_existed"].is<bool>()) {
                scan_networks(doc["wifi_scan_is_existed"].is<bool>());
            } else {
                scan_networks();
            }
            
        }
        if (doc["reset"].is<bool>() && doc["reset"].as<bool>())
        {
            esp_restart();
        }
    }
}