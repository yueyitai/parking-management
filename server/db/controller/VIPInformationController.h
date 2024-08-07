#pragma once
#include "../model/VIPInformationDAO.h"
#include "cJSON.h"

#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>

class VIPInformationController
{
private:
    VIPInformationDAO* dao;
public:
    typedef std::shared_ptr<VIPInformationController> ptr;
    VIPInformationController(VIPInformationDAO* dao);
    ~VIPInformationController();

    //登录
    std::string VIPLogin(cJSON data);

    //注册
    std::string VIPRegister(cJSON data);

    //充值
    std::string VIPCharge(cJSON data);

    //test
};

