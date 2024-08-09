#include "VIPInformationController.h"


VIPInformationController::VIPInformationController(VIPInformationDAO* dao):dao(dao)
{

}

VIPInformationController::~VIPInformationController()
{

}


//登录
std::string VIPInformationController::VIPLogin(std::string data){
    // 使用 nlohmann/json 解析传入的 JSON 字符串  
    try{
        auto jsonData = nlohmann::json::parse(data);  
        std::string licencePlate = jsonData.at("licence_plate").get<std::string>();  
        // 使用车牌号查询 VIP 信息  
        VIPInformation vip = dao->searchwithLicence(licencePlate); 
        if (vip.getId() != -1) { //查到了
            std::string ownerName = jsonData.at("owner_name").get<std::string>();
            std::string ownerTelephone = jsonData.at("owner_telephone").get<std::string>();
            if(vip.getOwnerName() == ownerName && vip.getOwnerTelephone() == ownerTelephone){
                return "SUCCESS";  
            }else{
                return "FAIL";  
            }
        } else {  //没查到
            return "FAIL";  
        }  
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr;
    }

}

//注册
std::string VIPInformationController::VIPRegister(std::string data){
    try{
        auto jsonData = nlohmann::json::parse(data);  
        std::string licencePlate = jsonData.at("licence_plate").get<std::string>();  
        
        // 使用车牌号查询 VIP 信息  
        VIPInformation vip = dao->searchwithLicence(licencePlate);
        
        if (vip.getId() != -1) { //查到了
            return "FAIL";
        }else{  //没查到
            std::string ownerName = jsonData.at("owner_name").get<std::string>();
            std::string ownerTelephone = jsonData.at("owner_telephone").get<std::string>();
            std::string start_time = jsonData.at("start_time").get<std::string>();
            std::string end_time = jsonData.at("end_time").get<std::string>();
            vip.setOwnerName(ownerName);
            vip.setOwnerTelephone(ownerTelephone);
            vip.setStartTime(start_time);
            vip.setEndTime(end_time);
            vip.setLicencePlate(licencePlate);
            dao->addVIPInformation(vip);
            return "SUCCESS";
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr;        
    }
}

//充值
std::string VIPInformationController::VIPCharge(std::string data){
    try{
        auto jsonData = nlohmann::json::parse(data);  
        std::string licencePlate = jsonData.at("licence_plate").get<std::string>();
        // 使用车牌号查询 VIP 信息  
        VIPInformation vip = dao->searchwithLicence(licencePlate);
        if(vip.getId() == -1){
            return "FAIL";
        }
        std::string startTime = jsonData.at("start_time").get<std::string>();
        if(vip.getEndTime() > startTime){
            return "FAIL";
        }else{
            std::string endTime = jsonData.at("end_time").get<std::string>();
            std::string ownerName = jsonData.at("owner_name").get<std::string>();
            std::string ownerTelephone = jsonData.at("owner_telephone").get<std::string>();
            vip.setLicencePlate(licencePlate);
            vip.setStartTime(startTime);
            vip.setEndTime(endTime);
            vip.setOwnerName(ownerName);
            vip.setOwnerTelephone(ownerTelephone);
            dao->updateVIPInformation(vip);
            return "SUCCESS";
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr;        
    }
}

//test