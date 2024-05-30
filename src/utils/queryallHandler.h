#ifndef QUERYALLHANDLER_H
#define QUERYALLHANDLER_H

#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include <glog/logging.h>
#include <nlohmann/json.hpp>
#include <folly/base64.h>
#include "dbCon.h"
#include <string>
class dbconnect;
class MqueryallHandler :public proxygen::RequestHandler{
public:
    void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;
    void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;
    void onEOM() noexcept override;
    void onUpgrade(proxygen::UpgradeProtocol prot) noexcept override;
    void requestComplete() noexcept override;
    void onError(proxygen::ProxygenError err) noexcept override;
    MqueryallHandler(std::shared_ptr<dbconnect> m);
private:
    nlohmann::json Jsondata;
    std::shared_ptr<dbconnect> c;
};
#endif