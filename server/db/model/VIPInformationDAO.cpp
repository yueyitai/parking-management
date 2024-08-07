#include <VIPInformationDAO.h>


VIPInformationDAO::VIPInformationDAO(/* args */)
{
}

VIPInformationDAO::~VIPInformationDAO()
{
}

//根据车牌查询
VIPInformation VIPInformationDAO::searchwithLicence(const std::string licence_plate){
    sqlite3 *db;  
    sqlite3_stmt *statement;  
    VIPInformation vip;  
    char *errorMessage = nullptr;  
  
    if (!openDb(db))  
    {  
        throw std::runtime_error("打开数据库失败");  
    }  
  
    std::string sql = "SELECT * FROM VIP_information_table WHERE licence_plate=?";  
  
    // 准备语句  
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &statement, &errorMessage) != SQLITE_OK)  
    {  
        // 错误处理：无法准备SQL语句  
        sqlite3_close(db);  
        if (errorMessage)  
        {  
            std::string errorMsg(errorMessage);  
            sqlite3_free(errorMessage);  
            throw std::runtime_error(errorMsg);  
        }  
        throw std::runtime_error("SQLite准备语句失败，但无具体错误信息");  
    }  
  
    // 绑定参数  
    sqlite3_bind_text(statement, 1, licence_plate.c_str(), -1, SQLITE_STATIC);  
  
    // 执行查询  
    while (sqlite3_step(statement) == SQLITE_ROW)  
    {  
        vip.setId(sqlite3_column_int(statement, 0));  
        vip.setLicencePlate((const char *)sqlite3_column_text(statement, 1));  
        vip.setStartTime((const char *)sqlite3_column_text(statement, 2));
        vip.setEndTime((const char *)sqlite3_column_text(statement, 3));
        vip.setOwnerName((const char *)sqlite3_column_text(statement, 4));
        vip.setOwnerTelephone((const char *)sqlite3_column_text(statement, 5));
        break;  
    }  
  
    // 清理资源  
    sqlite3_finalize(statement);  
    sqlite3_close(db);  
  
    // 返回记录，无论是否找到匹配项  
    return vip;  
}

//更新数据
bool VIPInformationDAO::updateVIPInformation(const VIPInformation vip){
    sqlite3 *db;  
    char *errorMessage = nullptr;  
    sqlite3_stmt* stmt;  
    if (!openDb(db))  
    {  
        throw std::runtime_error("打开数据库失败");  
        return false;  
    }  
  
    std::string sql = "UPDATE parking_record_form SET licence_plate=?, start_time=?, end_time=?, owner_name=?, owner_telephone=? WHERE id=?";  
  
    // 准备SQL语句  
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &errorMessage) != SQLITE_OK)  
    {  
        sqlite3_close(db);  
        if (errorMessage)  
        {  
            std::string errorMsg(errorMessage);  
            sqlite3_free(errorMessage);  
            throw std::runtime_error(errorMsg);  
        }  
        throw std::runtime_error("SQLite准备语句失败，但无具体错误信息");  
        return false;  
    }  
  
    // 绑定数据  
    sqlite3_bind_text(stmt, 1, vip.getLicencePlate().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_text(stmt, 2, vip.getStartTime().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_text(stmt, 3, vip.getEndTime().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_text(stmt, 4, vip.getOwnerName().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_text(stmt, 5, vip.getOwnerTelephone().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_int(stmt, 6, vip.getId());
  
    // 执行更新  
    if (sqlite3_step(stmt) != SQLITE_DONE)  
    {  
        std::string errorMsg(sqlite3_errmsg(db));  
        sqlite3_finalize(stmt);  
        sqlite3_close(db);  
        throw std::runtime_error(errorMsg);  
    }  
  
    // 清理资源  
    sqlite3_finalize(stmt);  
    sqlite3_close(db);  
  
    // 如果没有错误，则返回true  
    return true;  
}

//添加记录
bool VIPInformationDAO::addVIPInformation(const VIPInformation vip){
    sqlite3 *db;  
    sqlite3_stmt *statement;  
    char *errorMessage = nullptr;  
  
    if (!openDb(db))  
    {  
        throw std::runtime_error("打开数据库失败");  
        return false;  
    }  
  
    // 准备SQL语句  
    std::string sql = "INSERT INTO parking_record_form (licence_plate, start_time, end_time, owner_name, owner_telephone) VALUES (?, ?, ?, ?, ?)";  
  
    // 准备语句  
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &statement, &errorMessage) != SQLITE_OK)  
    {  
        sqlite3_close(db);  
        if (errorMessage)  
        {  
            std::string errorMsg(errorMessage);  
            sqlite3_free(errorMessage);  
            throw std::runtime_error(errorMsg);  
        }  
        throw std::runtime_error("SQL准备语句失败");  
    }  
  
    // 绑定参数  
    sqlite3_bind_text(statement, 1, vip.getLicencePlate().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_text(statement, 2, vip.getStartTime().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_text(statement, 3, vip.getEndTime().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_text(statement, 4, vip.getOwnerName().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_text(statement, 5, vip.getOwnerTelephone().c_str(), -1, SQLITE_STATIC);  
  
    // 执行SQL语句  
    if (sqlite3_step(statement) != SQLITE_DONE)  
    {  
        sqlite3_finalize(statement);  
        sqlite3_close(db);  
        if (errorMessage)  
        {  
            std::string errorMsg(errorMessage);  
            sqlite3_free(errorMessage);  
            throw std::runtime_error(errorMsg);  
        }  
        throw std::runtime_error("SQL执行失败");  
    }  
  
    // 清理资源  
    sqlite3_finalize(statement);  
    sqlite3_close(db);  
  
    return true;  
}

inline bool openDb(sqlite3 *db)
{

    // 打开数据库连接
    if (sqlite3_open("parkingManagementDb.db", &db) != SQLITE_OK)
    {
        return false;
    }
    else
        return true;
}