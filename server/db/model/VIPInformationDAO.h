#pragma once
#include "VIPInformation.h"
#include <sqlite3.h>
#include <sstream>
#include <stdexcept>

class VIPInformationDAO
{
private:
    /* data */
public:
    VIPInformationDAO(/* args */);
    ~VIPInformationDAO();

    //根据车牌查询
    VIPInformation searchwithLicence(const std::string licence_plate);

    //更新数据
    bool updateVIPInformation(const VIPInformation vip);

    //添加记录
    bool addVIPInformation(const VIPInformation vip);
};
