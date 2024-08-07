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
        VIPInformation vip(dao->searchwithLicence(licencePlateJSON->string));
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
    
}

//充值
std::string VIPInformationController::VIPCharge(cJSON data){

}

//test