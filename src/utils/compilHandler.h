#ifndef COMPILHANDLER_J
#define COMPILHANDLER_J

#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include <glog/logging.h>
#include <nlohmann/json.hpp>
#include <folly/base64.h>
#include <string>
class compilHandler :public proxygen::RequestHandler{
public:
    void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;
    void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;
    void onEOM() noexcept override;
    void onUpgrade(proxygen::UpgradeProtocol prot) noexcept override;
    void requestComplete() noexcept override;
    void onError(proxygen::ProxygenError err) noexcept override;
private:
    std::string Jsondata;
};
#endif