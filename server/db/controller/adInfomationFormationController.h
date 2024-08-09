#pragma once
#include "ad_information_formationDAO.h"
//#include "cJSON.h"

#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>

#include "nlohmann/json.hpp"

class AdInformationFormationController
{
private:
    Ad_information_formationDAO* dao;
public:
    typedef std::shared_ptr<AdInformationFormationController> ptr;
    AdInformationFormationController(Ad_information_formationDAO* dao);
    ~AdInformationFormationController();

    //1、插入单条广告信息
    std::string insertAdInformationFormation(std::string data);
    //2、根据id查询单条广告信息
    std::string selectAdInformationFormationById(std::string data);
    //3、根据id修改单条广告信息
    std::string updateAdInformationFormationById(std::string data);
    //4、根据id删除单条广告信息
    std::string deleteAdInformationFormationById(std::string data);
    //5、获取所有广告信息
    std::string getAllAdInformationFormation();

};
