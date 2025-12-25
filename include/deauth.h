#ifndef DEAUTH_H
#define DEAUTH_H

#include <variables.h>

void start_deauth(int wifi_number, uint16_t reason);
void stop_deauth();
bool is_deauth_running = false;
int total_elimination = 0;

extern int total_elimination;

typedef struct
{
    uint16_t frame_ctrl;
    uint16_t duration;
    uint8_t dest[6];
    uint8_t src[6];
    uint8_t bssid[6];
    uint16_t sequence_ctrl;
    uint8_t addr4[6];
} mac_hdr_t;

typedef struct
{
    mac_hdr_t hdr;
    uint8_t payload[0];
} wifi_packet_t;

typedef struct
{
    uint8_t frame_control[2] = {0xC0, 0x00};
    uint8_t duration[2];
    uint8_t station[6];
    uint8_t sender[6];
    uint8_t access_point[6];
    uint8_t fragment_sequence[2] = {0xF0, 0xFF};
    uint16_t reason;
} deauth_frame_t;

const wifi_promiscuous_filter_t filt = {
    .filter_mask = WIFI_PROMIS_FILTER_MASK_MGMT | WIFI_PROMIS_FILTER_MASK_DATA};

#endif