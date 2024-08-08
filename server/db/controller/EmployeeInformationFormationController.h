
#pragma once
#include "nlohmann/json.hpp"
#include "EmployeeInformationFormationDAO.h"

#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <vector>

class EmployeeInformationFormationController
{
private:
    std::shared_ptr<EmployeeInformationFormationDAO> dao;
public:
    EmployeeInformationFormationController(EmployeeInformationFormationDAO *dao);

    typedef std::shared_ptr<EmployeeInformationFormationController> ptr;
    //获取所有员工
    std::string getAllEmployee();

    //根据id查询
    std::string searchWithId(std::string data);

    //根据id更新
    std::string updateWithId(std::string data);

    //插入
    std::string insert(std::string data);
};

