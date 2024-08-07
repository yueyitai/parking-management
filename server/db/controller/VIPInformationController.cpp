#include "VIPInformationController.h"


VIPInformationController::VIPInformationController(VIPInformationDAO* dao):dao(dao)
{

}

VIPInformationController::~VIPInformationController()
{

}


//登录
std::string VIPInformationController::VIPLogin(cJSON data){
    cJSON* root;
    try
    {
        cJSON* licencePlateJSON = cJSON_GetObjectItem(&data, "licence_plate");
        if(licencePlateJSON == NULL){
            throw std::runtime_error("JSON解析失败！");  
            return nullptr;
        }
        VIPInformation vip(dao->searchwithLicence(std::string(cJSON_Print(licencePlateJSON))));
        if(vip.getId() == -1){
            return nullptr;
        }
        cJSON_AddStringToObject(root, "owner_name", vip.getOwnerName().c_str());
        cJSON_AddStringToObject(root, "owner_telephone", vip.getOwnerTelephone().c_str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }
    std::string ret = cJSON_Print(root);
    return ret;
}

//注册
std::string VIPInformationController::VIPRegister(cJSON data){
    cJSON* root;
    try{
        cJSON* licence_plate_json = cJSON_GetObjectItem(&data, "licence_plate");
        if(licence_plate_json == NULL){
            throw std::runtime_error("JSON解析失败！");
            return nullptr;
        }
        VIPInformation vip(dao->searchwithLicence(std::string(cJSON_Print(licence_plate_json))));
        if(vip.getId() == -1){
            cJSON* start_time_json = cJSON_GetObjectItem(&data, "start_time");
            cJSON* end_time_json = cJSON_GetObjectItem(&data, "end_time");
            cJSON* owner_name_json = cJSON_GetObjectItem(&data, "owner_name");
            cJSON* owner_telephone_json = cJSON_GetObjectItem(&data, "owner_telephone");
            vip.setLicencePlate(std::string(cJSON_Print(licence_plate_json)));
            vip.setStartTime(std::string(cJSON_Print(start_time_json)));
            vip.setEndTime(std::string(cJSON_Print(end_time_json)));
            vip.setOwnerName(std::string(cJSON_Print(owner_name_json)));
            vip.setOwnerTelephone(std::string(cJSON_Print(owner_telephone_json)));
            dao->addVIPInformation(vip);
            return std::string("SUCCESS");
        }
        return std::string("FAIL");
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr;
    }
    return std::string("FAIL");
}

//充值
std::string VIPInformationController::VIPCharge(cJSON data){
    cJSON* root;
    try
    {
        cJSON* licence_plate_json = cJSON_GetObjectItem(&data, "licence_plate");
        if(licence_plate_json == NULL){
            throw std::runtime_error("JSON解析失败！");
            return nullptr;
        }
        VIPInformation vip(dao->searchwithLicence(std::string(cJSON_Print(licence_plate_json))));
        cJSON* start_time_json = cJSON_GetObjectItem(&data, "start_time");
        if(vip.getEndTime() > std::string(cJSON_Print(start_time_json))){//可能会有问题，不知道能不能这样比较
            throw std::runtime_error("还在VIP期间！");
            return nullptr;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }
    
}

//test