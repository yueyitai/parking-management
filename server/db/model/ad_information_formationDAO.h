#pragma once
#include "ad_information_formation.h"
#include <sqlite3.h>
#include <sstream>
#include <stdexcept>
#include <vector>

class Ad_information_formationDAO
{
public:
    
    //返回整张表
    std::vector<Ad_information_formation> getAll();

    //添加一条记录
    bool addAd_information_formation(Ad_information_formation ad);

    //删除一条记录
    bool deleteaddAd_information_formation(int id);

    //修改一条记录
    bool updateaddAd_information_formation(Ad_information_formation ad);

    //根据ID查询一条记录
    Ad_information_formation getAd_information_formationById(int id);
};
