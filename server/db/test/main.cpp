#include <iostream>
#include "adInfomationFormationController.h"
#include "EmployeeInformationFormationController.h"
#include "parkingRecordFormationController.h"
#include "VIPInformationController.h"

using namespace std;

int main(){
    ParkingRecordFormationDAO dao;
    ParkingRecordFormationController::ptr controllerPtr 
        = make_shared<ParkingRecordFormationController>(&dao);

    string test = R"({
        "path": "/server/pic/4.jpg",
        "time": 1723187878,
        "licence_plate": "赣B98398"
    })";

    string ret = controllerPtr.get()->usePark(test);    
    
    cout << ret << endl;

    return 0;
}