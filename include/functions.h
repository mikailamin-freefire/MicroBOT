#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "variables.h"
#include "display.h"

void string_to_mac(const char *mac_str, uint8_t *mac);
String mac_to_string(const uint8_t *mac);
void scan_networks(bool is_existed = false);

#endif
