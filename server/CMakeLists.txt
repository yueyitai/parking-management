cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(MyProject VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含所有源文件的路径
set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/db/controller/EmployeeInformationFormationController.cpp
    ${CMAKE_SOURCE_DIR}/db/controller/VIPInformationController.cpp
    ${CMAKE_SOURCE_DIR}/db/controller/adInfomationFormationController.cpp
    ${CMAKE_SOURCE_DIR}/db/controller/parkingRecordFormationController.cpp
    ${CMAKE_SOURCE_DIR}/db/model/EmployeeInformationFormation.cpp
    ${CMAKE_SOURCE_DIR}/db/model/EmployeeInformationFormationDAO.cpp
    ${CMAKE_SOURCE_DIR}/db/model/VIPInformation.cpp
    ${CMAKE_SOURCE_DIR}/db/model/VIPInformationDAO.cpp
    ${CMAKE_SOURCE_DIR}/db/model/ad_information_formation.cpp
    ${CMAKE_SOURCE_DIR}/db/model/ad_information_formationDAO.cpp
    ${CMAKE_SOURCE_DIR}/db/model/parkingRecordFormation.cpp
    ${CMAKE_SOURCE_DIR}/db/model/parkingRecordFormationDAO.cpp
    ${CMAKE_SOURCE_DIR}/db/model/sqlite3.c
    ${CMAKE_SOURCE_DIR}/db/test/main.cpp
    # 添加其他源文件路径
)

# 包含所有头文件的路径
include_directories(
    ${CMAKE_SOURCE_DIR}/db/controller
    ${CMAKE_SOURCE_DIR}/db/model
    ${CMAKE_SOURCE_DIR}/tools/
    # 添加其他头文件路径
)

# 指定生成的可执行文件路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/db/test)

# 定义可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 如果有需要链接的库，则使用以下命令
# target_link_libraries(${PROJECT_NAME} PRIVATE some_libraries)