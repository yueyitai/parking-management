#pragma once
#include "parkingRecordFormation.h"
#include <sqlite3.h>
#include <sstream>
#include <stdexcept>
#include <iostream>

class ParkingRecordFormationDAO
{
public:
    /*
        插入
    */
    bool addParkingRecordFormation(ParkingRecordFormation record);
    // 更新/软删除
    bool updateParkingRecordFormation(ParkingRecordFormation &record);
    // 根据车牌查询
    ParkingRecordFormation searchWithLicence(const std::string licence);
    // 根据车牌删除
    bool DeleteWithliecence(const std::string licence);
    // 根据id查询
    ParkingRecordFormation searchWithId(int id);
};