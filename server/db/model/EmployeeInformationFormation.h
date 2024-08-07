#pragma once
#include <string>

class EmployeeInformationFormation
{
private:
    int id;
    std::string name;
    std::string gender;
    int age;
    std::string hirTime;
    bool state;
    std::string resTime;
    std::string phone;
    std::string licencePlate;
public:
    EmployeeInformationFormation(/* args */);
    ~EmployeeInformationFormation();
        // Getter 和 Setter 方法
    int getId() const;

    void setId(int newId);

    const std::string& getName() const;

    void setName(const std::string& newName) ;

    const std::string& getGender() const;

    void setGender(const std::string& newGender);

    int getAge() const;

    void setAge(int newAge);

    const std::string& getHirTime() const ;

    void setHirTime(const std::string& newHireTime);

    bool getState() const ;

    void setState(bool newState);

    const std::string& getResTime() const;

    void setResTime(const std::string& newResTime);

    const std::string& getPhone() const;

    void setPhone(const std::string& newPhone);

    const std::string& getLicencePlate() const ;

    void setLicencePlate(const std::string& newLicencePlate);
};

