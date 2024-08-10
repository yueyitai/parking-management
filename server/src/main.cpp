#include "ParkingServer.h"

int main()
{
    //log_set_level(LOG_INFO);

    ParkingServer ps(20202);

    if (!ps.init())
    {
        log_error("服务器初始化失败");
        return -1;
    }

    if (!ps.run())
    {
        log_error("服务器运行失败");
        return -1;
    }

    while (true)
    {
        sleep(5);
    }

    return 0;
}
