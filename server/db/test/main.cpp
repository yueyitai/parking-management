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
        "path": "/server/pic/2.jpg",
        "time": 1723187778,
        "licence_plate": "赣A8373E"
    })";

    string ret = controllerPtr.get()->usePark(test);    
    
    cout << ret << endl;

    return 0;
}