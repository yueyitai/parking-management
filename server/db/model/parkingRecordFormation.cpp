#include "parkingRecordFormation.h"

ParkingRecordFormation::ParkingRecordFormation()
{
    this->id = -1;
}

ParkingRecordFormation::~ParkingRecordFormation()
{
}

int ParkingRecordFormation::getId() const
{
    return this->id;
}
void ParkingRecordFormation::setId(int id)
{
    this->id = id;
}
std::string ParkingRecordFormation::getLicencePlate() const
{
    return this->licencePlate;
}
void ParkingRecordFormation::setLicencePlate(const std::string &licencePlate)
{
    this->licencePlate = licencePlate;
}
int ParkingRecordFormation::getEnterParkingTime() const
{
    return this->enterParkingTime;
}
void ParkingRecordFormation::setEnterParkingTime(int enterParkingTime)
{
    this->enterParkingTime = enterParkingTime;
}
int ParkingRecordFormation::getOutParkingTime() const
{
    return this->outParkingTime;
}
void ParkingRecordFormation::setOutParkingTime(int outParkingTime)
{
    this->outParkingTime = outParkingTime;
}
bool ParkingRecordFormation::getIsDelete() const
{
    return this->isDelete;
}
void ParkingRecordFormation::setIsDelete(bool isDelete)
{
    this->isDelete = isDelete;
}
std::string ParkingRecordFormation::getEnterPicPath() const
{
    return this->enterPicPath;
}
void ParkingRecordFormation::setEnterPicPath(const std::string &enterPicPath)
{
    this->enterPicPath = enterPicPath;
}
std::string ParkingRecordFormation::getOutPicPath() const
{
    return this->outPicPath;
}
void ParkingRecordFormation::setOutPicPath(const std::string &outPicPath)
{
    this->outPicPath = outPicPath;
}