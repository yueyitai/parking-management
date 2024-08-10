
#pragma once
#include "nlohmann/json.hpp"
#include "parkingRecordFormationDAO.h"
#include "EmployeeInformationFormationDAO.h"
#include "VIPInformationDAO.h"

#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>

class ParkingRecordFormationController
{
private:
    ParkingRecordFormationDAO* dao;
public:
    ParkingRecordFormationController(ParkingRecordFormationDAO* dao);
    ~ParkingRecordFormationController();
    typedef std::shared_ptr<ParkingRecordFormationController> ptr;

    //使用停车场
    std::string usePark(std::string);

    //根据车牌查询
    std::string searchWithPlate(std::string std);
};


