#pragma once
#include "EmployeeInformationFormation.h"
#include <sqlite3.h>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>

class EmployeeInformationFormationDAO
{
public:
    EmployeeInformationFormationDAO(/* args */);
    ~EmployeeInformationFormationDAO();

    //查询整张数据表
    std::vector<EmployeeInformationFormation> getAll();
    //插入一个记录
    bool addEmployeeInformationFormation(EmployeeInformationFormation employee);
    //根据id更新数据
    bool updateWithId(EmployeeInformationFormation employee);
    //根据id查询数据
    EmployeeInformationFormation searchWithId(int id);
    //根据车牌查询数据
    EmployeeInformationFormation searchWithLicence(std::string licence_plate);
};

