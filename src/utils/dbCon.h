#ifndef CONNECT_H
#define CONNECT_H
#include <conncpp.hpp>
#include <string>
#include <iostream>
#include <folly/FBVector.h>
class dbconnect{

private:
    sql::Driver* driver=nullptr;
    sql::SQLString url;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> c;
public:
    dbconnect();
    ~dbconnect();
    void insert(std::string name,std::string content);
    folly::fbvector<sql::SQLString> queryall();
    sql::SQLString query(std::string name);
};

#endif