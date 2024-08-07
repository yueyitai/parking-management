#pragma once
#include <string>

class ParkingRecordFormation
{
private:
    int id;
    std::string licencePlate;
    int enterParkingTime;
    int outParkingTime;
    bool isDelete;
    std::string enterPicPath;
    std::string outPicPath;

public:
    ParkingRecordFormation();
    ~ParkingRecordFormation();
    int getId() const;
    void setId(int id);
    std::string getLicencePlate() const;
    void setLicencePlate(const std::string &licencePlate);
    int getEnterParkingTime() const;
    void setEnterParkingTime(int enterParkingTime);
    int getOutParkingTime() const;
    void setOutParkingTime(int outParkingTime);
    bool getIsDelete() const;
    void setIsDelete(bool isDelete);
    std::string getEnterPicPath() const;
    void setEnterPicPath(const std::string &outPicPath);
    std::string getOutPicPath() const;
    void setOutPicPath(const std::string &outPicPath);
};
