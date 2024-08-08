#include "EmployeeInformationFormationController.h"

EmployeeInformationFormationController::EmployeeInformationFormationController(EmployeeInformationFormationDAO *dao) : dao(dao){
    
}

    //获取所有员工
    std::string EmployeeInformationFormationController::getAllEmployee(){
        // 使用 nlohmann/json 库来创建 JSON 数组
        nlohmann::json jArray = nlohmann::json::array();
        try
        {
            std::vector<EmployeeInformationFormation> vec;
            vec = dao.get()->getAll();

            // 遍历 vector，将每个 EmployeeInformationFormation 对象添加到 JSON 数组中
            for (const auto& employee : vec) {
                jArray.push_back({
                    {"id", employee.getId()},
                    {"name", employee.getName()},
                    {"gender", employee.getGender()},
                    {"age", employee.getAge()},
                    {"hirTime", employee.getHirTime()},
                    {"state", employee.getState()},
                    {"resTime", employee.getResTime()},
                    {"phone", employee.getPhone()},
                    {"licencePlate", employee.getLicencePlate()}
                });
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        // 将 JSON 数组转换为 std::string
        std::string ret = jArray.dump();
        return ret;
    }

    //根据id查询
    std::string EmployeeInformationFormationController::searchWithId(std::string data){
        EmployeeInformationFormation employee;
        nlohmann::json j;
        std::string ret = nullptr;
        try {
            // 解析 JSON 字符串
            nlohmann::json dataJSON = nlohmann::json::parse(data);
            if (dataJSON.contains("id") && dataJSON["id"].is_number_integer()) {
                int id = dataJSON["id"].get<int>();
                employee = dao.get()->searchWithId(id);
                if(employee.getId() != -1){
                    j["id"] = employee.getId();
                    j["name"] = employee.getName();
                    j["gender"] = employee.getGender();
                    j["age"] = employee.getAge();
                    j["hir_time"] = employee.getHirTime();
                    j["state"] = employee.getState();
                    j["res_time"] = employee.getResTime();
                    j["phone"] = employee.getPhone();
                    j["licence_plate"] = employee.getLicencePlate();

                    ret = j.dump();
                }
            } else {
                // 如果 id 字段不存在或不是整数类型，抛出异常
                throw std::runtime_error("id字段不存在或不是整数！");
            }
            
        }
        catch (const nlohmann::json::parse_error& e) {
            // 捕获并处理 JSON 解析错误
            std::cerr << "JSON parse error: " << e.what() << '\n';
        }
        catch (const std::exception& e) {
            // 捕获并处理其他异常
            std::cerr << "Error: " << e.what() << '\n';
        }
        return ret;
    }

    //根据id更新
    std::string EmployeeInformationFormationController::updateWithId(std::string data){
        EmployeeInformationFormation employee;
        nlohmann::json dataJSON = nlohmann::json::parse(data);
        try
        {
            if (dataJSON.contains("id") && dataJSON["id"].is_number_integer()){
                employee.setId(dataJSON["id"].get<int>());
            }else {
                throw std::runtime_error("id字段不存在或不是整数！");
            }

            if (dataJSON.contains("name") && dataJSON["name"].is_string()){
                employee.setName(dataJSON["name"].get<std::string>());
            }else {
                throw std::runtime_error("name字段不存在或不是字符串！");
            }

            if (dataJSON.contains("gender") && dataJSON["gender"].is_string()){
                employee.setGender(dataJSON["gender"].get<std::string>());
            }else {
                throw std::runtime_error("gender字段不存在或不是字符串！");
            }

            if (dataJSON.contains("age") && dataJSON["age"].is_number_integer()){
                employee.setAge(dataJSON["age"].get<int>());
            }else {
                throw std::runtime_error("age字段不存在或不是整数！");
            }

            if (dataJSON.contains("hir_time") && dataJSON["gehir_timender"].is_string()){
                employee.setHirTime(dataJSON["hir_time"].get<std::string>());
            }else {
                throw std::runtime_error("hir_time字段不存在或不是字符串！");
            }

            if (dataJSON.contains("state") && dataJSON["state"].is_number_integer()){
                employee.setState(dataJSON["state"].get<int>());
            }else {
                throw std::runtime_error("state字段不存在或不是整数！");
            }

            if (dataJSON.contains("res_time") && dataJSON["res_time"].is_string()){
                employee.setResTime(dataJSON["res_time"].get<std::string>());
            }else {
                throw std::runtime_error("res_time字段不存在或不是字符串！");
            }

            if (dataJSON.contains("phone") && dataJSON["phone"].is_string()){
                employee.setPhone(dataJSON["phone"].get<std::string>());
            }else {
                throw std::runtime_error("phone字段不存在或不是字符串！");
            }

            if (dataJSON.contains("licence_plate") && dataJSON["phone"].is_string()){
                employee.setPhone(dataJSON["phone"].get<std::string>());
            }

            dao.get()->updateWithId(employee);
        }
        catch (const nlohmann::json::parse_error& e) {
            // 捕获并处理 JSON 解析错误
            std::cerr << "JSON parse error: " << e.what() << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << "未知错误：" << e.what() << '\n';
        }
        
        return "SUCCESS";
    }

    //插入
    std::string EmployeeInformationFormationController::insert(std::string data){
        EmployeeInformationFormation employee;
        nlohmann::json dataJSON = nlohmann::json::parse(data);
        try
        {

            if (dataJSON.contains("name") && dataJSON["name"].is_string()){
                employee.setName(dataJSON["name"].get<std::string>());
            }else {
                throw std::runtime_error("name字段不存在或不是字符串！");
            }

            if (dataJSON.contains("gender") && dataJSON["gender"].is_string()){
                employee.setGender(dataJSON["gender"].get<std::string>());
            }else {
                throw std::runtime_error("gender字段不存在或不是字符串！");
            }

            if (dataJSON.contains("age") && dataJSON["age"].is_number_integer()){
                employee.setAge(dataJSON["age"].get<int>());
            }else {
                throw std::runtime_error("age字段不存在或不是整数！");
            }

            if (dataJSON.contains("hir_time") && dataJSON["gehir_timender"].is_string()){
                employee.setHirTime(dataJSON["hir_time"].get<std::string>());
            }else {
                throw std::runtime_error("hir_time字段不存在或不是字符串！");
            }

            if (dataJSON.contains("state") && dataJSON["state"].is_number_integer()){
                employee.setState(dataJSON["state"].get<int>());
            }else {
                throw std::runtime_error("state字段不存在或不是整数！");
            }

            if (dataJSON.contains("phone") && dataJSON["phone"].is_string()){
                employee.setPhone(dataJSON["phone"].get<std::string>());
            }else {
                throw std::runtime_error("phone字段不存在或不是字符串！");
            }

            if (dataJSON.contains("licence_plate") && dataJSON["phone"].is_string()){
                employee.setPhone(dataJSON["phone"].get<std::string>());
            }

            dao.get()->addEmployeeInformationFormation(employee);
        }
        catch (const nlohmann::json::parse_error& e) {
            // 捕获并处理 JSON 解析错误
            std::cerr << "JSON parse error: " << e.what() << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << "未知错误：" << e.what() << '\n';
        }
        
        return "SUCCESS";
    }