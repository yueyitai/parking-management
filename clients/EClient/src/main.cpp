#include <unistd.h>

#include "EClient.h"
#include "log.h"

int main()
{
    EClient ec;

    char recvBuf[1024] = { 0 };

    if (!ec.operateDatabase(EClient::ECLIENT_GETALLINFO, recvBuf))
    {
        log_error("获取所有员工信息错误");
    }

    log_info("recvBuf:%s", recvBuf);

    char insertData[1024] = "insert data";
    if (!ec.operateDatabase(EClient::ECLIENT_INSERT_ONE_INFO,nullptr, insertData))
    {
        log_error("插入单条员工信息错误");
    }

    if (!ec.operateDatabase(EClient::ECLIENT_QUERY_ONE_INFO_BY_ID,recvBuf))
    {
        log_error("根据id查询单条员工信息错误");
    }

    log_info("recvBuf:%s", recvBuf);

    char updateData[1024] = "update data";
    if (!ec.operateDatabase(EClient::ECLIENT_UPDATE_ONE_INFO_BY_ID,nullptr, updateData))
    {
        log_error("根据id修改单条员工信息错误");
    }

    while (true)
    {
        sleep(5);
    }

    return 0;
}
