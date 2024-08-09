#include "ad_information_formationDAO.h"
#include <iostream>
inline bool openDb(sqlite3 **db)
{

    // 打开数据库连接
    if (sqlite3_open("parkingManagementDb.db", db) != SQLITE_OK)
    {
        return false;
    }
    else
        return true;
}

    //返回整张表
    std::vector<Ad_information_formation> Ad_information_formationDAO::getAll(){
        sqlite3 *db;  
        sqlite3_stmt* stmt;  
        std::vector<Ad_information_formation> adVec;  
        const char *errorMessage = nullptr;  
    
        // 打开数据库  
        if (!openDb(&db)) {  
            throw std::runtime_error("打开数据库失败");  
        }  
    
        // 准备SQL语句  
        std::string sql = "SELECT * FROM ad_information_table";  
    
        // 编译SQL语句  
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt,nullptr) != SQLITE_OK) {  
            // 如果编译失败，关闭数据库并抛出异常  
            sqlite3_close(db);  
            if (errorMessage) {  
                std::string errorMsg(errorMessage);  
                //sqlite3_free(errorMessage);  
                throw std::runtime_error(errorMsg);  
            }  
            throw std::runtime_error("SQLite准备语句失败，但无具体错误信息");  
        }  
    
        // 遍历查询结果  
        while (sqlite3_step(stmt) == SQLITE_ROW) {  
            Ad_information_formation ad;  
    
            ad.setId(sqlite3_column_int(stmt, 0));  
            ad.setName((const char*)sqlite3_column_text(stmt, 1));  
            ad.setStartTime((const char*)sqlite3_column_text(stmt, 2));  
            ad.setExpiratDate((const char*)sqlite3_column_text(stmt, 3));  
            ad.setContent((const char*)sqlite3_column_text(stmt, 4));  
            ad.setPhone((const char*)sqlite3_column_text(stmt, 5));  

    
            adVec.push_back(ad);  
        }  
    
        // 检查是否有错误发生 
        // if (sqlite3_errcode(db) != SQLITE_OK) {  
        //     std::string errorMsg(sqlite3_errmsg(db));  
        //     sqlite3_finalize(stmt);  
        //     sqlite3_close(db);  
        //     throw std::runtime_error(errorMsg);  
        // }  
    
        // 清理资源  
        sqlite3_finalize(stmt);  
        sqlite3_close(db);  
    
        return adVec;  
    }

    //添加一条记录
    bool Ad_information_formationDAO::addAd_information_formation(Ad_information_formation ad){
        sqlite3 *db;  
        sqlite3_stmt* stmt;  
        const char *errorMessage = nullptr;  
    
        // 打开数据库  
        if (!openDb(&db)) {  
            throw std::runtime_error("打开数据库失败");  
        }  
    
        // 准备SQL语句  
        std::string sql = "INSERT INTO ad_information_table (name, start_date, expirat_date, content, phone) VALUES (?, ?, ?, ?, ?)";  
    
        // 编译SQL语句  
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {  
                // 获取错误消息
                errorMessage = sqlite3_errmsg(db);
                sqlite3_close(db);  
                if (errorMessage) {
                    std::string errorMsg(errorMessage);
                    // sqlite3_free((void *)errorMessage); 
                    throw std::runtime_error("SQLite准备语句失败: " + errorMsg);
                } else {
                    throw std::runtime_error("SQLite准备语句失败，但无具体错误信息"); 
                }
            }  
    
        std::string name = ad.getName();
        std::cout << name<< std::endl;
        std::string starttime = ad.getStartTime();
        std::cout << starttime<< std::endl;
        std::string expiratdate = ad.getExpiratDate();
        std::cout << expiratdate<< std::endl;
        std::string content = ad.getContent();
        std::cout << content<< std::endl;
        std::string phone = ad.getPhone();
        std::cout << phone<< std::endl;

        // 绑定参数  
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);  
        sqlite3_bind_text(stmt, 2, starttime.c_str(), -1, SQLITE_STATIC);  
        sqlite3_bind_text(stmt, 3, expiratdate.c_str(), -1, SQLITE_STATIC);  
        sqlite3_bind_text(stmt, 4, content.c_str(), -1, SQLITE_STATIC);  
        sqlite3_bind_text(stmt, 5, phone.c_str(), -1, SQLITE_STATIC);
    
        // 执行SQL语句  
        if (sqlite3_step(stmt) != SQLITE_DONE) {  
            // 如果执行失败，获取错误信息并抛出异常  
            std::string errorMsg(sqlite3_errmsg(db));  
            sqlite3_finalize(stmt);  
            sqlite3_close(db);  
            throw std::runtime_error(errorMsg);  
        }  
    
        // 清理资源  
        sqlite3_finalize(stmt);  
        sqlite3_close(db);  
    
        // 插入成功  
        return true;  
    }

    //删除一条记录
    bool Ad_information_formationDAO::deleteaddAd_information_formation(int id){
        sqlite3 *db;  
        sqlite3_stmt* stmt;  
        const char *errorMessage = nullptr;  
    
        // 打开数据库  
        if (!openDb(&db)) {  
            throw std::runtime_error("打开数据库失败");  
        }  
    
        // 准备SQL语句  
        std::string sql = "DELETE FROM ad_information_table WHERE id=?";  
    
        // 编译SQL语句  
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt,nullptr) != SQLITE_OK) {  
            // 如果编译失败，关闭数据库并抛出异常  
            sqlite3_close(db);  
            if (errorMessage) {  
                std::string errorMsg(errorMessage);  
                //sqlite3_free(errorMessage);  
                throw std::runtime_error(errorMsg);  
            }  
            throw std::runtime_error("SQLite准备语句失败，但无具体错误信息");  
        }  
    
        // 绑定参数  
        sqlite3_bind_int(stmt, 1, id);  
        
    
        // 执行SQL语句  
        if (sqlite3_step(stmt) != SQLITE_DONE) {  
            // 如果执行失败，获取错误信息并抛出异常  
            std::string errorMsg(sqlite3_errmsg(db));  
            sqlite3_finalize(stmt);  
            sqlite3_close(db);  
            throw std::runtime_error(errorMsg);  
        }  
    
        // 清理资源  
        sqlite3_finalize(stmt);  
        sqlite3_close(db);  
    
        // 删除成功  
        return true;  
    }

    //修改一条记录
    bool Ad_information_formationDAO::updateaddAd_information_formation(Ad_information_formation ad){
        sqlite3 *db;  
        sqlite3_stmt* stmt;  
        const char *errorMessage = nullptr;  

        if (!openDb(&db)) {  
            throw std::runtime_error("打开数据库失败");  
        }  

        // 准备SQL语句  
        std::string sql = "UPDATE ad_information_table SET name=?, start_date=?, expirat_date=?, content=?, phone=? WHERE id=?";  
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt,nullptr) != SQLITE_OK) {  
            sqlite3_close(db);  
            if (errorMessage) {  
                std::string errorMsg(errorMessage);  
                //sqlite3_free(errorMessage);  
                throw std::runtime_error(errorMsg);  
            }  
            throw std::runtime_error("SQLite准备语句失败，但无具体错误信息");  
        }  

        // 绑定参数  
        std::string name = ad.getName();
        std::cout << name<< std::endl;
        std::string starttime = ad.getStartTime();
        std::cout << starttime<< std::endl;
        std::string expiratdate = ad.getExpiratDate();
        std::cout << expiratdate<< std::endl;
        std::string content = ad.getContent();
        std::cout << content<< std::endl;
        std::string phone = ad.getPhone();
        std::cout << phone<< std::endl;
        int id = ad.getId();
        std::cout << id<< std::endl;

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);  
        sqlite3_bind_text(stmt, 2, starttime.c_str(), -1, SQLITE_STATIC);  
        sqlite3_bind_text(stmt, 3, expiratdate.c_str(), -1, SQLITE_STATIC);  
        sqlite3_bind_text(stmt, 4, content.c_str(), -1, SQLITE_STATIC);  
        sqlite3_bind_text(stmt, 5, phone.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 6, id);  

        // 执行SQL语句  
        if (sqlite3_step(stmt) != SQLITE_DONE) {  
            // 错误处理  
            std::string errorMsg(sqlite3_errmsg(db));  
            sqlite3_finalize(stmt);  
            sqlite3_close(db);  
            throw std::runtime_error(errorMsg);  
        }  

        // 清理资源  
        sqlite3_finalize(stmt);  
        sqlite3_close(db);  

        return true;  
    }



Ad_information_formation Ad_information_formationDAO::getAd_information_formationById(int id){

    // 打开数据库连接
    sqlite3 *db;
    if (!openDb(&db))
    {
        throw std::runtime_error("Failed to open database");
    }
    // 准备SQL语句
    std::string sql = "SELECT * FROM ad_information_table WHERE id = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare statement");
    }
    // 绑定参数
    if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to bind parameter");

    }

    Ad_information_formation ad_information_formation;
    // 执行查询
    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        //throw std::runtime_error("Failed to execute query");
        return ad_information_formation;
    }
    // 提取结果
    
    ad_information_formation.setId(sqlite3_column_int(stmt, 0));
    ad_information_formation.setName(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    ad_information_formation.setStartTime(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
    ad_information_formation.setExpiratDate(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
    ad_information_formation.setContent(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
    ad_information_formation.setPhone(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5)));
    // 清理资源
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return ad_information_formation;
}