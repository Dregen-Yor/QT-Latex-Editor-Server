#include "dbCon.h"
#include <glog/logging.h>
dbconnect::dbconnect(){
    driver=sql::mariadb::get_driver_instance();
    url="jdbc:mariadb://localhost:3306/tex";
    properties=sql::Properties({{"user", "qt"}, {"password", "22119797sgx"}});
    c=std::unique_ptr<sql::Connection>(driver->connect(url, properties));

    
}
void dbconnect::insert(std::string name,std::string content){
    try{
        std::unique_ptr<sql::PreparedStatement> stmnt(c->prepareStatement("insert into file (name,content) values (?,?) ON DUPLICATE KEY UPDATE name=values(name),content=values(content);"));
        stmnt->setString(1, sql::SQLString(name));
        stmnt->setString(2,sql::SQLString(content));
        stmnt->executeUpdate();
        LOG(INFO)<<"数据库上传成功";
    }catch(sql::SQLException &e){
        std::cout<<e.what();
        LOG(ERROR)<<"数据库上传错误";
    }
}
dbconnect::~dbconnect(){

}

folly::fbvector<sql::SQLString> dbconnect::queryall(){
    folly::fbvector<sql::SQLString> res;
    try{
        std::unique_ptr<sql::Statement> stmt(c->createStatement());
        std::unique_ptr<sql::ResultSet> resset(stmt->executeQuery("select * from file"));
        while(resset->next()){
            res.push_back(resset->getString("name"));
        }
    }catch(sql::SQLException &e){
        std::cout<<e.what();
    }
    return res;
}
sql::SQLString dbconnect::query(std::string name){

    sql::SQLString res;
    try{
        std::unique_ptr<sql::PreparedStatement> stmnt(c->prepareStatement("select content from file where name=?"));
        stmnt->setString(1,sql::SQLString(name));
        std::unique_ptr<sql::ResultSet> resset(stmnt->executeQuery());
        if(resset->next()){
            res=resset->getString("content");
        }
    }catch(sql::SQLException &e){
        std::cout<<e.what();
    }
    return res;
}