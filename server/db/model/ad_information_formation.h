#pragma once
#include <string>

class Ad_information_formation
{
private:
    int id;
    std::string name;
    std::string startTime;
    std::string expirat_date;
    std::string content;
    std::string phone;
    
public:
    Ad_information_formation(/* args */);
    ~Ad_information_formation();
        // Getters  
    int getId() const ;
  
    std::string getName() const ;
  
    std::string getStartTime() const;
  
    std::string getExpiratDate() const;
  
    std::string getContent() const;
  
    std::string getPhone() const;
  
    // Setters  
    void setId(int newId);
  
    void setName(const std::string& newName);
  
    void setStartTime(const std::string& newStartTime);
  
    void setExpiratDate(const std::string& newExpiratDate);
    void setContent(const std::string& newContent);
  
    void setPhone(const std::string& newPhone);
};


