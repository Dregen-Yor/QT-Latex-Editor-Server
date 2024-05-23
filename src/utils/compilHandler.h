#ifndef COMPILHANDLER_J
#define COMPILHANDLER_J

#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>
class compilHandler :public proxygen::RequestHandler{
public:
    void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;
    void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;
    void onEOM() noexcept override;
    void onUpgrade(proxygen::UpgradeProtocol prot) noexcept override;
    void requestComplete() noexcept override;
    void onError(proxygen::ProxygenError err) noexcept override;

};
#endif