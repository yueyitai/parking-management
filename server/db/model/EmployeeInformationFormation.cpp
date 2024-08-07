#include "EmployeeInformationFormation.h"

EmployeeInformationFormation::EmployeeInformationFormation(/* args */)
{
    this->id = -1;
}

EmployeeInformationFormation::~EmployeeInformationFormation()
{
}

int EmployeeInformationFormation::getId() const
{
    return id;
}

void EmployeeInformationFormation::setId(int newId)
{
    id = newId;
}

const std::string &EmployeeInformationFormation::getName() const
{
    return name;
}

void EmployeeInformationFormation::setName(const std::string &newName)
{
    name = newName;
}

const std::string &EmployeeInformationFormation::getGender() const
{
    return gender;
}

void EmployeeInformationFormation::setGender(const std::string &newGender)
{
    gender = newGender;
}

int EmployeeInformationFormation::getAge() const
{
    return age;
}

void EmployeeInformationFormation::setAge(int newAge)
{
    age = newAge;
}

const std::string &EmployeeInformationFormation::getHirTime() const
{
}

void EmployeeInformationFormation::setHirTime(const std::string &newHireTime)
{
    hirTime = newHireTime;
}

bool EmployeeInformationFormation::getState() const
{
    return state;
}

void EmployeeInformationFormation::setState(bool newState)
{
    state = newState;
}

const std::string &EmployeeInformationFormation::getResTime() const
{
}

void EmployeeInformationFormation::setResTime(const std::string &newResTime)
{
    resTime = newResTime;
}

const std::string &EmployeeInformationFormation::getPhone() const
{
    return phone;
}

void EmployeeInformationFormation::setPhone(const std::string &newPhone)
{
    phone = newPhone;
}

const std::string &EmployeeInformationFormation::getLicencePlate() const
{
    return licencePlate;
}

void EmployeeInformationFormation::setLicencePlate(const std::string &newLicencePlate)
{
    licencePlate = newLicencePlate;
}