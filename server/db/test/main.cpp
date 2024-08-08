#include <iostream>
#include "adInfomationFormationController.h"
#include "EmployeeInformationFormationController.h"
#include "parkingRecordFormationController.h"
#include "VIPInformationController.h"

using namespace std;

int main(){
    try
    {
        EmployeeInformationFormationDAO dao;
        EmployeeInformationFormationController::ptr controllerPtr = 
            std::make_shared<EmployeeInformationFormationController>(&dao);
        
            std::string test = R"({
                "name": "张三",
                "gender": "男",
                "age": 26,
                "hir_time": "2024-8-11",
                "state": 1,
                "phone": "13769831597",
                "licence_plate": "赣A68E73"
            })";

        std::string ret = controllerPtr.get()->insert(test);
        cout << ret << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}