#include "server.h"
#include "client.h"
#include "common.h"

int main(void) {
    send_message(getServerIP(), GET,"TEST; Temp: 32; Humidity: 34.5");
    return 0;
}
