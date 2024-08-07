#include <ad_information_formation.h>
Ad_information_formation::Ad_information_formation(/* args */) : id(-1)
{
}

Ad_information_formation::~Ad_information_formation()
{
}

int Ad_information_formation::getId() const {  
        return id;  
    }  
  
    std::string Ad_information_formation::getName() const {  
        return name;  
    }  
  
    std::string Ad_information_formation::getStartTime() const {  
        return startTime;  
    }  
  
    std::string Ad_information_formation::getExpiratDate() const {
        return expirat_date;  
    }  
  
    std::string Ad_information_formation::getContent() const {  
        return content;  
    }  
  
    std::string Ad_information_formation::getPhone() const {  
        return phone;  
    }  
  
    // Setters  
    void Ad_information_formation::setId(int newId) {  
        id = newId;  
    }  
  
    void Ad_information_formation::setName(const std::string& newName) {  
        name = newName;  
    }  
  
    void Ad_information_formation::setStartTime(const std::string& newStartTime) {  
        startTime = newStartTime;  
    }  
  
    void Ad_information_formation::setExpiratDate(const std::string& newExpiratDate) {
        expirat_date = newExpiratDate;  
    }  
  
    void Ad_information_formation::setContent(const std::string& newContent) {  
        content = newContent;  
    }  
  
    void Ad_information_formation::setPhone(const std::string& newPhone) {  
        phone = newPhone;  
    }  