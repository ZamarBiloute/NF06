#include <stdbool.h>
#include <stdio.h>
#include "Const.h"
#include <stdarg.h>

#include <stdio.h>
#include <stdarg.h>


#if DEBUG_ACTIF
void Afficher_msg_debug(const char *message, ...)
{
    if (!DEBUG_ACTIF || message == NULL) {
        return;
    }

    va_list args;
    va_start(args, message);

    printf("[DEBUG] : ");
    vprintf(message, args);

    va_end(args);
    fflush(stdout);
}
#endif
