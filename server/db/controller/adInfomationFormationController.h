#pragma once
#include "ad_information_formationDAO.h"
#include "cJSON.h"

#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>

class AdInformationFormationController
{
private:
    std::shared_ptr<Ad_information_formationDAO> dao;
public:
    typedef std::shared_ptr<AdInformationFormationController> ptr;
    AdInformationFormationController(Ad_information_formationDAO* dao);
    ~AdInformationFormationController();

    //1、插入单条广告信息
    std::string insertAdInformationFormation(cJSON data);
    //2、根据id查询单条广告信息
    std::string selectAdInformationFormationById(cJSON data);
    //3、根据id修改单条广告信息
    std::string updateAdInformationFormationById(cJSON data);
    //4、根据id删除单条广告信息
    std::string deleteAdInformationFormationById(cJSON data);
    //5、获取所有广告信息
    std::string getAllAdInformationFormation(cJSON data);

};
