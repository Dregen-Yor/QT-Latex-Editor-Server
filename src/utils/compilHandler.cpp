#include "compilHandler.h"

void compilHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers)noexcept{

}

void compilHandler::onBody(std::unique_ptr<folly::IOBuf> body)noexcept{

}

void compilHandler::onEOM()noexcept{
    proxygen::ResponseBuilder(downstream_)
      .status(200, "OK")
      .body("Goodbye, World!")
      .sendWithEOM();
}

void compilHandler::onUpgrade(proxygen::UpgradeProtocol prot)noexcept{

}

void compilHandler::requestComplete()noexcept{
    delete this;
}

void compilHandler::onError(proxygen::ProxygenError err)noexcept{
    delete this;
}