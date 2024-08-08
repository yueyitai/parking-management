
#include <parkingRecordFormationDAO.h>

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

bool ParkingRecordFormationDAO::addParkingRecordFormation(ParkingRecordFormation record)
{
    sqlite3 *db;  
    sqlite3_stmt *statement;  
    char *errorMessage = nullptr;  
  
    if (!openDb(db))  
    {  
        throw std::runtime_error("打开数据库失败");  
        return false;  
    }  
  
    // 准备SQL语句  
    std::string sql = "INSERT INTO parking_record_form (licence_plate, enter_parking_time, enter_pic_path) VALUES (?, ?, ?)";  
  
    // 准备语句  
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &statement,(const char **) &errorMessage) != SQLITE_OK)  
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
    sqlite3_bind_text(statement, 1, record.getLicencePlate().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_int(statement, 2, record.getEnterParkingTime());  
    sqlite3_bind_text(statement, 3, record.getEnterPicPath().c_str(), -1, SQLITE_STATIC);  
  
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
// 更新/软删除
bool ParkingRecordFormationDAO::updateParkingRecordFormation(ParkingRecordFormation &record)
{
    sqlite3 *db;  
    char *errorMessage = nullptr;  
    sqlite3_stmt* stmt;  
    if (!openDb(db))  
    {  
        throw std::runtime_error("打开数据库失败");  
        return false;  
    }  
  
    std::string sql = "UPDATE parking_record_form SET out_parking_time=?, is_delete=?, out_pic_path=? WHERE id=?";  
  
    // 准备SQL语句  
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt,(const char **) &errorMessage) != SQLITE_OK)  
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
    sqlite3_bind_int(stmt, 1, record.getOutParkingTime());  
    sqlite3_bind_int(stmt, 2, record.getIsDelete());  
    sqlite3_bind_text(stmt, 3, record.getOutPicPath().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_int(stmt, 4, record.getId());  
  
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
// 根据车牌查询
ParkingRecordFormation ParkingRecordFormationDAO::searchWithLicence(const std::string licence)
{
    sqlite3 *db;  
    sqlite3_stmt *statement;  
    ParkingRecordFormation record;  
    char *errorMessage = nullptr;  
  
    if (!openDb(db))  
    {  
        throw std::runtime_error("打开数据库失败");
    }  
  
    std::string sql = "SELECT * FROM parking_record_form WHERE licence_plate=? AND is_delete=1";  
  
    // 准备语句  
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &statement,(const char **) &errorMessage) != SQLITE_OK)  
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
    sqlite3_bind_text(statement, 1, licence.c_str(), -1, SQLITE_STATIC);  
  
    // 执行查询  
    while (sqlite3_step(statement) == SQLITE_ROW)  
    {  
        //如果存在多个匹配项，这里将只返回第一个
        record.setId(sqlite3_column_int(statement, 0));  
        record.setLicencePlate((const char *)sqlite3_column_text(statement, 1));  
        record.setEnterParkingTime(sqlite3_column_int(statement, 2));  
        record.setOutParkingTime(sqlite3_column_int(statement, 3));  
        record.setIsDelete(sqlite3_column_int(statement, 4));  
        record.setEnterPicPath((const char *)sqlite3_column_text(statement, 5));  
        record.setOutPicPath((const char *)sqlite3_column_text(statement, 6));  
        // 如果有多个结果但只想要第一个，在这里 break 退出循环  
        break;  
    }  
  
    // 清理资源  
    sqlite3_finalize(statement);  
    sqlite3_close(db);  
  
    // 返回记录，无论是否找到匹配项  
    return record;  
}
// 根据车牌删除
bool ParkingRecordFormationDAO::DeleteWithliecence(const std::string licence)
{
}
// 根据id查询
ParkingRecordFormation ParkingRecordFormationDAO::searchWithId(int id)
{
}

