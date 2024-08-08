#include "adInfomationFormationController.h"

    AdInformationFormationController::AdInformationFormationController(Ad_information_formationDAO* dao) : dao(dao){

    }
    AdInformationFormationController::~AdInformationFormationController(){

    }

//1、插入单条广告信息
std::string AdInformationFormationController::insertAdInformationFormation(std::string data){
    try{
        auto jsonData = nlohmann::json::parse(data); 
        std::string name = jsonData.at("name").get<std::string>();
        std::string startTime = jsonData.at("start_time").get<std::string>();
        std::string expiratDate = jsonData.at("expirat_date").get<std::string>();
        std::string content = jsonData.at("content").get<std::string>();
        std::string phone = jsonData.at("phone").get<std::string>();
        Ad_information_formation adinfo;
        adinfo.setName(name);
        adinfo.setStartTime(startTime);
        adinfo.setExpiratDate(expiratDate);
        adinfo.setContent(content);
        adinfo.setPhone(phone);
        bool res = dao->addAd_information_formation(adinfo);
        if(res){
            return "SUCCESS";
        }else{
            return "FAIL";
        }    
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr; 
    }

}
//2、根据id查询单条广告信息
std::string AdInformationFormationController::selectAdInformationFormationById(std::string data){
    nlohmann::json j;
    std::string ret = nullptr;
    try{
        auto jsonData = nlohmann::json::parse(data); 
        int id = jsonData.at("id").get<int>();
        Ad_information_formation ad_info = dao->getAd_information_formationById(id);
        if(ad_info.getId() != -1){
            j["id"] = ad_info.getId();
            j["name"] = ad_info.getName();
            j["start_time"] = ad_info.getStartTime();
            j["expirat_date"] = ad_info.getExpiratDate();
            j["content"] = ad_info.getContent();
            j["phone"] = ad_info.getPhone();
            ret = j.dump();
            return ret;
        }else{
            return "FAIL";
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr; 
    }
}
//3、根据id修改单条广告信息
std::string AdInformationFormationController::updateAdInformationFormationById(std::string data){
    try{
        auto jsonData = nlohmann::json::parse(data);
        Ad_information_formation ad_info;
        ad_info.setId(jsonData.at("id").get<int>());
        ad_info.setName(jsonData.at("name").get<std::string>());
        ad_info.setStartTime(jsonData.at("start_time").get<std::string>());
        ad_info.setExpiratDate(jsonData.at("expirat_date").get<std::string>());
        ad_info.setContent(jsonData.at("content").get<std::string>());
        ad_info.setPhone(jsonData.at("phone").get<std::string>());
        bool ret = dao->updateaddAd_information_formation(ad_info);
        if(ret){
            return "SUCCESS";
        }else{
            return "FAIL";
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr; 
    }
}
//4、根据id删除单条广告信息
std::string AdInformationFormationController::deleteAdInformationFormationById(std::string data){
    try{
        auto jsonData = nlohmann::json::parse(data);
        int id = jsonData.at("id").get<int>();
        bool ret = dao->deleteaddAd_information_formation(id);
        if(ret){
            return "SUCCESS";
        }else{
            return "FAIL";
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr; 
    }
}
//5、获取所有广告信息
std::string AdInformationFormationController::getAllAdInformationFormation(){
    std::vector<Ad_information_formation> ad_info_list = dao.get()->getAll();
    nlohmann::json jArray = nlohmann::json::array();
    try{
        // 遍历 vector，将每个 EmployeeInformationFormation 对象添加到 JSON 数组中
        for (const auto& ad_info : ad_info_list) {
            jArray.push_back({
            {"id", ad_info.getId()},
            {"name", ad_info.getName()},
            {"start_time", ad_info.getStartTime()},
            {"expirat_time", ad_info.getExpiratDate()},
            {"content", ad_info.getContent()},
            {"phone", ad_info.getPhone()},
            });
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        return nullptr; 
    }
    return jArray.dump();
}