#include "parkingRecordFormationController.h"


ParkingRecordFormationController::ParkingRecordFormationController(ParkingRecordFormationDAO* dao) : dao(dao)
{
    
}

ParkingRecordFormationController::~ParkingRecordFormationController()
{

}

    //使用
    std::string ParkingRecordFormationController::usePark(cJSON data){
        cJSON* root;
        try
        {
            //解析json
            cJSON* licencePlateJSON = cJSON_GetObjectItem(&data, "licence_plate");
            cJSON* timeJSON = cJSON_GetObjectItem(&data, "time");
            cJSON* pathJSON = cJSON_GetObjectItem(&data, "path");
            if(licencePlateJSON == NULL || timeJSON == NULL || pathJSON == NULL){
                throw std::runtime_error("JSON解析失败！");  
                return nullptr;
            }
            ParkingRecordFormation record(dao->searchWithLicence(std::string(licencePlateJSON->valuestring)));
            if(record.getId() == -1){//入场
                record.setLicencePlate(std::string(cJSON_Print(licencePlateJSON)));
                record.setEnterParkingTime(timeJSON->valueint);
                record.setEnterPicPath(std::string(pathJSON->valuestring));
                dao->addParkingRecordFormation(record);
                cJSON_AddNumberToObject(root, "time", 0);
            }else{//出场
                EmployeeInformationFormationDAO employeeDAO;
                VIPInformationDAO vipDAO;
                std::string licencePlate = record.getLicencePlate();
                EmployeeInformationFormation employee = employeeDAO.searchWithLicence(licencePlate);
                VIPInformation vip = vipDAO.searchwithLicence(licencePlate);
                if(employee.getId() == -1 && vip.getId() == -1){//需要收钱
                    cJSON_AddNumberToObject(root, "time", record.getEnterParkingTime());
                    cJSON_AddNumberToObject(root, "flag", 0);
                }else{//不需要收钱
                    cJSON_AddNumberToObject(root, "time", record.getEnterParkingTime());
                    cJSON_AddNumberToObject(root, "flag", 1);
                }
                record.setIsDelete(0);
                record.setOutParkingTime(timeJSON->valueint);
                record.setOutPicPath(std::string(pathJSON->valuestring));

                dao->updateParkingRecordFormation(record);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return nullptr;
        }
        std::string ret = root->valuestring;
        return ret;
    }
