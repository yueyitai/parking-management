#pragma once
#include <string>

class VIPInformation {
public:
    VIPInformation();
    ~VIPInformation();

    int getId() const;
    void setId(int id);

    std::string getLicencePlate() const;
    void setLicencePlate(const std::string& licencePlate);

    std::string getStartTime() const;
    void setStartTime(const std::string& startTime);

    std::string getEndTime() const;
    void setEndTime(const std::string& endTime);

    std::string getOwnerName() const;
    void setOwnerName(const std::string& ownerName);

    std::string getOwnerTelephone() const;
    void setOwnerTelephone(const std::string& ownerTelephone);

private:
    int id;
    std::string licencePlate;
    std::string startTime;
    std::string endTime;
    std::string ownerName;
    std::string ownerTelephone;
};