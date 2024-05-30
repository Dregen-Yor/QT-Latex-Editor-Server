#include "queryallHandler.h"

MqueryallHandler::MqueryallHandler(std::shared_ptr<dbconnect> m) {
    c=m;
}

void MqueryallHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers)noexcept{

}

void MqueryallHandler::onBody(std::unique_ptr<folly::IOBuf> body)noexcept{
    folly::fbvector<sql::SQLString> query=c->queryall();
    std::vector<std::string> query1;
    for(auto i:query){
        query1.push_back(i.c_str());
    }
    Jsondata["allfile"]=query1;
}

void MqueryallHandler::onEOM()noexcept{
    proxygen::ResponseBuilder(downstream_)
            .status(200, "OK")
            .header("Content-Type", "application/json")
            .body(Jsondata.dump())
            .sendWithEOM();
}   

void MqueryallHandler::onUpgrade(proxygen::UpgradeProtocol prot)noexcept{

}

void MqueryallHandler::requestComplete()noexcept{
    delete this;
}

void MqueryallHandler::onError(proxygen::ProxygenError err)noexcept{
    delete this;
}