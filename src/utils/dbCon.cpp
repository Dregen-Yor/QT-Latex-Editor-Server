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
        std::unique_ptr<sql::PreparedStatement> stmnt(c->prepareStatement("insert into file (name,content) values (?)"));
        stmnt->setString(1, content);
        stmnt->setString(2,content);
        stmnt->executeQuery();
        LOG(INFO)<<"数据库上传成功";
    }catch(std::exception &e){
        LOG(ERROR)<<"数据库上传错误";
    }
}
dbconnect::~dbconnect(){

}