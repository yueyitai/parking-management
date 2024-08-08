#pragma once
#include "VIPInformationDAO.h"
//#include "cJSON.h"

#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>

#include "nlohmann/json.hpp"

class VIPInformationController
{
private:
    std::shared_ptr<VIPInformationDAO> dao;
    //VIPInformationDAO* dao;
public:
    typedef std::shared_ptr<VIPInformationController> ptr;
    VIPInformationController(VIPInformationDAO* dao);
    ~VIPInformationController();

    //登录
    std::string VIPLogin(std::string data);

    //注册
    std::string VIPRegister(std::string data);

    //充值
    std::string VIPCharge(std::string data);

    //test
};

