#include "const.h"
#pragma once

#if DEBUG_ACTIF
#define AFF_DEBUG(...) Afficher_msg_debug(__VA_ARGS__)
#else
#define AFF_DEBUG(...)
#endif

void Afficher_msg_debug(const char *message, ...);