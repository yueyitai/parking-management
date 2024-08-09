#include <EmployeeInformationFormationDAO.h>

// inline bool openDb(sqlite3 *db)
// {

//     // 打开数据库连接
//     if (sqlite3_open("parkingManagementDb.db", &db) != SQLITE_OK)
//     {
//         return false;
//     }
//     else
//         return true;
// }

inline bool openDb(sqlite3 **db)
{
    // 注意这里的参数是 sqlite3** 类型
    if (sqlite3_open("parkingManagementDb.db", db) != SQLITE_OK)
    {
        // 如果打开失败，db 指针可能没有被修改，但这里我们假设它仍然是 nullptr 或无效的
        // （实际上，sqlite3_open 可能会尝试设置 *db 为一个错误状态，但在这里我们不考虑这种情况）
        return false;
    }
    else
    {
        // 如果打开成功，db 指针现在指向一个有效的数据库连接
        return true;
    }
}

EmployeeInformationFormationDAO::EmployeeInformationFormationDAO(/* args */)
{
}

EmployeeInformationFormationDAO::~EmployeeInformationFormationDAO()
{
}

// 查询整张数据表
std::vector<EmployeeInformationFormation> EmployeeInformationFormationDAO::getAll()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    std::vector<EmployeeInformationFormation> employeeVec;
    const char *errorMessage = nullptr;

    // 打开数据库
    if (!openDb(&db))
    {
        throw std::runtime_error("打开数据库失败");
    }

    // 准备SQL语句
    std::string sql = "SELECT * FROM Employee_information_form";

    // 编译SQL语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &errorMessage) != SQLITE_OK)
    {
        // 如果编译失败，关闭数据库并抛出异常
        sqlite3_close(db);
        if (errorMessage)
        {
            std::string errorMsg(errorMessage);
            throw std::runtime_error(errorMsg);
            sqlite3_free((void *)errorMessage);
        }
        throw std::runtime_error("SQLite准备语句失败，但无具体错误信息");
    }

    // 遍历查询结果
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        EmployeeInformationFormation employee;
        // 数据库中的列顺序和EmployeeInformationFormation的成员变量顺序一致
        employee.setId(sqlite3_column_int(stmt, 0));

        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        if (name)
        {
            employee.setName(name);
        }

        const char *gender = (const char *)sqlite3_column_text(stmt, 2);
        if (gender)
        {
            employee.setGender(gender);
        }

        employee.setAge(sqlite3_column_int(stmt, 3));

        const char *hirTime = (const char *)sqlite3_column_text(stmt, 4);
        if (hirTime)
        {
            employee.setHirTime(hirTime);
        }

        employee.setState(sqlite3_column_int(stmt, 5));

        const char *resTime = (const char *)sqlite3_column_text(stmt, 6);
        if (resTime)
        {
            employee.setResTime(resTime);
        }

        const char *phone = (const char *)sqlite3_column_text(stmt, 7);
        if (phone)
        {
            employee.setPhone(phone);
        }

        const char *licencePlate = (const char *)sqlite3_column_text(stmt, 8);
        if (licencePlate)
        {
            employee.setLicencePlate(licencePlate);
        }

        employeeVec.push_back(employee);
    }

    // 检查是否有错误发生
    // if (sqlite3_errcode(db) != SQLITE_OK)
    // {
    //     std::string errorMsg(sqlite3_errmsg(db));
    //     sqlite3_finalize(stmt);
    //     sqlite3_close(db);
    //     throw std::runtime_error(errorMsg);
    // }

    // 清理资源
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return employeeVec;
}

// 插入一个记录
bool EmployeeInformationFormationDAO::addEmployeeInformationFormation(EmployeeInformationFormation employee)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *errorMessage = nullptr;

    if (sqlite3_open("parkingManagementDb.db", &db) != SQLITE_OK)
    {
        // 如果打开失败，db 指针可能没有被修改，但这里我们假设它仍然是 nullptr 或无效的
        // （实际上，sqlite3_open 可能会尝试设置 *db 为一个错误状态，但在这里我们不考虑这种情况）
        return false;
    }

    // 准备SQL语句
    std::string sql = "INSERT INTO Employee_information_form (name, gender, age, hir_time, phone, licence_plate) VALUES (?, ?, ?, ?, ?, ?)";
    // 编译SQL语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        // 获取错误消息
        errorMessage = sqlite3_errmsg(db);
        sqlite3_close(db);
        if (errorMessage)
        {
            std::string errorMsg(errorMessage);
            // sqlite3_free((void *)errorMessage);
            throw std::runtime_error("SQLite准备语句失败: " + errorMsg);
        }
        else
        {
            throw std::runtime_error("SQLite准备语句失败，但无具体错误信息");
        }
    }
    // 绑定参数
    sqlite3_bind_text(stmt, 1, employee.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, employee.getGender().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, employee.getAge());
    sqlite3_bind_text(stmt, 4, employee.getHirTime().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, employee.getPhone().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, employee.getLicencePlate().c_str(), -1, SQLITE_STATIC);

    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
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

// 更新数据
bool EmployeeInformationFormationDAO::updateWithId(EmployeeInformationFormation employee)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *errorMessage = nullptr;

    if (!openDb(&db))
    {
        throw std::runtime_error("打开数据库失败");
    }

    // 准备SQL语句
    std::string sql = "UPDATE Employee_information_form SET name=?, gender=?, age=?, hir_time=?, res_time=?, phone=?, licence_plate=?, state=? WHERE id=?";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        // 获取错误消息
        errorMessage = sqlite3_errmsg(db);
        sqlite3_close(db);
        if (errorMessage)
        {
            std::string errorMsg(errorMessage);
            // sqlite3_free((void *)errorMessage);
            throw std::runtime_error("SQLite准备语句失败: " + errorMsg);
        }
        else
        {
            throw std::runtime_error("SQLite准备语句失败，但无具体错误信息");
        }
    }
    std::cout << employee.getName().c_str() << std::endl;
    // 绑定参数
    sqlite3_bind_text(stmt, 1, employee.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, employee.getGender().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, employee.getAge());
    sqlite3_bind_text(stmt, 4, employee.getHirTime().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, employee.getResTime().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, employee.getPhone().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, employee.getLicencePlate().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 8, employee.getState());
    sqlite3_bind_int(stmt, 9, employee.getId());

    // 执行SQL语句
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
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
// 根据id查询数据
EmployeeInformationFormation EmployeeInformationFormationDAO::searchWithId(int id)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    EmployeeInformationFormation employee;
    employee.setId(-1); // 初始化一个默认值，以防找不到员工
    char *errorMessage = nullptr;
    if (!openDb(&db))
    {
        throw std::runtime_error("打开数据库失败");
        return employee;
    }

    std::string sql = "select * from Employee_information_form where id=?";
    // 准备SQL语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    // 绑定参数
    if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    // 执行SQL语句
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        employee.setId(sqlite3_column_int(stmt, 0));

        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        if (name)
        {
            employee.setName(name);
        }

        const char *gender = (const char *)sqlite3_column_text(stmt, 2);
        if (gender)
        {
            employee.setGender(gender);
        }

        employee.setAge(sqlite3_column_int(stmt, 3));

        const char *hirTime = (const char *)sqlite3_column_text(stmt, 4);
        if (hirTime)
        {
            employee.setHirTime(hirTime);
        }

        employee.setState(sqlite3_column_int(stmt, 5));

        const char *resTime = (const char *)sqlite3_column_text(stmt, 6);
        if (resTime)
        {
            employee.setResTime(resTime);
        }

        const char *phone = (const char *)sqlite3_column_text(stmt, 7);
        if (phone)
        {
            employee.setPhone(phone);
        }

        const char *licencePlate = (const char *)sqlite3_column_text(stmt, 8);
        if (licencePlate)
        {
            employee.setLicencePlate(licencePlate);
        }
    }

    // 清理资源
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return employee;
}

//根据车牌查询
EmployeeInformationFormation EmployeeInformationFormationDAO::searchWithLicence(std::string licence_plate)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    EmployeeInformationFormation employee;
    employee.setId(-1); // 初始化一个默认值，以防找不到员工
    char *errorMessage = nullptr;

    if (!openDb(&db))
    {
        throw std::runtime_error("打开数据库失败");
        return employee;
    }

    std::string sql = "select * from Employee_information_form where licence_plate=?";
    // 准备SQL语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        sqlite3_close(db);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, licence_plate.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    // 执行SQL语句
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        employee.setId(sqlite3_column_int(stmt, 0));

        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        if (name)
        {
            employee.setName(name);
        }

        const char *gender = (const char *)sqlite3_column_text(stmt, 2);
        if (gender)
        {
            employee.setGender(gender);
        }

        employee.setAge(sqlite3_column_int(stmt, 3));

        const char *hirTime = (const char *)sqlite3_column_text(stmt, 4);
        if (hirTime)
        {
            employee.setHirTime(hirTime);
        }

        employee.setState(sqlite3_column_int(stmt, 5));

        const char *resTime = (const char *)sqlite3_column_text(stmt, 6);
        if (resTime)
        {
            employee.setResTime(resTime);
        }

        const char *phone = (const char *)sqlite3_column_text(stmt, 7);
        if (phone)
        {
            employee.setPhone(phone);
        }

        const char *licencePlate = (const char *)sqlite3_column_text(stmt, 8);
        if (licencePlate)
        {
            employee.setLicencePlate(licencePlate);
        }
    }

    // 清理资源
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return employee;
}
