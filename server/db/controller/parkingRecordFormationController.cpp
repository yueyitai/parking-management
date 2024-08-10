#include "parkingRecordFormationController.h"



ParkingRecordFormationController::ParkingRecordFormationController(ParkingRecordFormationDAO* dao) : dao(dao)
{
    
}

ParkingRecordFormationController::~ParkingRecordFormationController()
{

}

    //使用
    std::string ParkingRecordFormationController::usePark(std::string data){
        try
        {
            std::string path;
            std::string licencePlate;
            int time;

            //解析json
            nlohmann::json dataJSON = nlohmann::json::parse(data);
            if (dataJSON.contains("image") && dataJSON["image"].is_string()){
                path = dataJSON["image"].get<std::string>();
            }else {
                throw std::runtime_error("path字段不存在或不是字符串！");
            }

            if (dataJSON.contains("licence_plate") && dataJSON["licence_plate"].is_string()){
                licencePlate = dataJSON["licence_plate"].get<std::string>();
            }else {
                throw std::runtime_error("licence_plate字段不存在或不是字符串！");
            }

            if (dataJSON.contains("time") && dataJSON["time"].is_number_integer()){
                time = dataJSON["time"].get<int>();
            }else {
                throw std::runtime_error("time字段不存在或不是整数！");
            }

            ParkingRecordFormation record(dao->searchWithLicence(licencePlate));
            if(record.getId() == -1){//入场
                record.setLicencePlate(licencePlate);
                record.setEnterParkingTime(time);
                record.setEnterPicPath(path);
                if(dao->addParkingRecordFormation(record)){
                    return "SUCCESS";
                }else{
                    return "FAIL";
                }
            }else{//出场
                std::string licencePlate = record.getLicencePlate();
                record.setIsDelete(1);
                record.setOutParkingTime(time);
                record.setOutPicPath(path);
                if(dao->updateParkingRecordFormation(record)){
                    return "SUCCESS";
                }else{
                    return "FAIL";
                }
                
            }
        }
        catch (const nlohmann::json::parse_error& e) {
            // 捕获并处理 JSON 解析错误
            std::cerr << "JSON parse error: " << e.what() << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return "FAIL";
        }
    }


std::string ParkingRecordFormationController::searchWithPlate(std::string data){
    try
    {
        nlohmann::json j;
        nlohmann::json dataJSON = nlohmann::json::parse(data);
        std::string licencePlate;
        if (dataJSON.contains("licence_plate") && dataJSON["licence_plate"].is_string()){
            licencePlate = dataJSON["licence_plate"].get<std::string>();
        }else {
            throw std::runtime_error("licence_plate字段不存在或不是字符串！");
        }
        ParkingRecordFormation record(dao->searchWithLicence(licencePlate));

        if(record.getOutParkingTime() == 0){//入场
            j["time"] = 0;
            j["flag"] = 0;
        }else{//出场
            EmployeeInformationFormationDAO employeeDAO;
            VIPInformationDAO vipDAO;
            EmployeeInformationFormation employee = employeeDAO.searchWithLicence(licencePlate);
            VIPInformation vip = vipDAO.searchwithLicence(licencePlate);
            if((employee.getId() == -1 && vip.getId() == -1 && employee.getState()) || employee.getState() == 0){//需要收钱
                j["time"] = record.getEnterParkingTime();
                j["flag"] = 0;
            }else{//不需要收钱
                j["time"] = record.getEnterParkingTime();
                j["flag"] = 1;
            }
            record.setIsDelete(0);
            if(!dao->updateParkingRecordFormation(record)){
                return "FAIL";
            }
        }
        

        return j.dump();
    }
    catch (const nlohmann::json::parse_error& e) {
        // 捕获并处理 JSON 解析错误
        std::cerr << "JSON parse error: " << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}