#ifndef queryHandler_H
#define queryHandler_H

#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include <glog/logging.h>
#include <nlohmann/json.hpp>
#include <folly/base64.h>
#include "dbCon.h"
#include <string>
class dbconnect;
class queryHandler :public proxygen::RequestHandler{
public:
    void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;
    void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;
    void onEOM() noexcept override;
    void onUpgrade(proxygen::UpgradeProtocol prot) noexcept override;
    void requestComplete() noexcept override;
    void onError(proxygen::ProxygenError err) noexcept override;
    queryHandler(std::shared_ptr<dbconnect> m);
private:
    std::string Jsondata;
    std::shared_ptr<dbconnect> c;
};
#endif