#include <VIPInformation.h>

    VIPInformation::VIPInformation() : id(-1) {} // 默认构造函数，初始化id为0  
    VIPInformation::~VIPInformation() {} // 析构函数，目前不需要特别处理  
  
    // getId 方法  
    int VIPInformation::getId() const {  
        return id;  
    }  
  
    // setId 方法  
    void VIPInformation::setId(int id) {  
        this->id = id;  
    }  
  
    // getLicencePlate 方法  
    std::string VIPInformation::getLicencePlate() const {  
        return licencePlate;  
    }  
  
    // setLicencePlate 方法  
    void VIPInformation::setLicencePlate(const std::string& licencePlate) {  
        this->licencePlate = licencePlate;  
    }  
  
    // getStartTime 方法  
    std::string VIPInformation::getStartTime() const {  
        return startTime;  
    }  
  
    // setStartTime 方法  
    void VIPInformation::setStartTime(const std::string& startTime) {  
        this->startTime = startTime;  
    }  
  
    // getEndTime 方法  
    std::string VIPInformation::getEndTime() const {  
        return endTime;  
    }  
  
    // setEndTime 方法  
    void VIPInformation::setEndTime(const std::string& endTime) {  
        this->endTime = endTime;  
    }  
  
    // getOwnerName 方法  
    std::string VIPInformation::getOwnerName() const {  
        return ownerName;  
    }  
  
    // setOwnerName 方法  
    void VIPInformation::setOwnerName(const std::string& ownerName) {  
        this->ownerName = ownerName;  
    }  
  
    // getOwnerTelephone 方法  
    std::string VIPInformation::getOwnerTelephone() const {  
        return ownerTelephone;  
    }  
  
    // setOwnerTelephone 方法  
    void VIPInformation::setOwnerTelephone(const std::string& ownerTelephone) {  
        this->ownerTelephone = ownerTelephone;  
    } 