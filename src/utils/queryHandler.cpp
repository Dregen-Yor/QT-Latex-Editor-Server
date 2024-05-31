#include "queryHandler.h"

queryHandler::queryHandler(std::shared_ptr<dbconnect> m){
    c=m;
}

void queryHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers)noexcept{

}
void queryHandler::onBody(std::unique_ptr<folly::IOBuf> body)noexcept{
    if(body){
        Jsondata.append(reinterpret_cast<const char*>(body->data()), body->length());
    }
}

void queryHandler::onEOM()noexcept{
    nlohmann::json f=nlohmann::json::parse(Jsondata);
    std::string fname=f["filename"];
    std::string content=c->query(fname).c_str();
    nlohmann::json json;
    json["content"]=content;
    proxygen::ResponseBuilder(downstream_)
            .status(200, "OK")
            .header("Content-Type", "application/json")
            .body(json.dump())
            .sendWithEOM();
}

void queryHandler::onUpgrade(proxygen::UpgradeProtocol prot) noexcept {

}

void queryHandler::requestComplete() noexcept{
    delete this;
}

void queryHandler::onError(proxygen::ProxygenError err) noexcept{
    delete this;
}