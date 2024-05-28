#include "compilHandler.h"

compilHandler::compilHandler(std::shared_ptr<dbconnect> m){
    c=m;
}

void compilHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers)noexcept{

}

void compilHandler::onBody(std::unique_ptr<folly::IOBuf> body)noexcept{
    if(body){
        Jsondata.append(reinterpret_cast<const char*>(body->data()), body->length());
    }
}

void compilHandler::onEOM()noexcept{
    try{
        nlohmann::json f=nlohmann::json::parse(Jsondata);
        std::string fname=f["filename"];
        std::string fdata=f["filedata"];
        c->insert(fname,fdata);
        std::ofstream outFile(fname+".tex",std::ios::trunc);
        outFile<< fdata;
        outFile.close();
        std::string command ="latexmk -xelatex  -halt-on-error "+fname+".tex";
        int result = std::system(command.c_str());
        if(result==0){
            std::ifstream pdf(fname+".pdf",std::ios::binary);
            std::stringstream buffer;
            buffer << pdf.rdbuf();
            proxygen::ResponseBuilder(downstream_)
            .status(200, "OK")
            .header("Content-Type", "application/pdf")
            .body(buffer.str())
            .sendWithEOM();
            std::system("latexmk -C");

        }
        else{
            proxygen::ResponseBuilder(downstream_)
            .status(400, "Bad Request")
            .body("编译错误")
            .sendWithEOM();
        }
    }catch(const std::exception& e){
        proxygen::ResponseBuilder(downstream_)
        .status(400, "Bad Request")
        .body("编译错误")
        .sendWithEOM();
    };

    
}

void compilHandler::onUpgrade(proxygen::UpgradeProtocol prot)noexcept{

}

void compilHandler::requestComplete()noexcept{
    delete this;
}

void compilHandler::onError(proxygen::ProxygenError err)noexcept{
    LOG(ERROR)<<"An error occured";
    delete this;
}
