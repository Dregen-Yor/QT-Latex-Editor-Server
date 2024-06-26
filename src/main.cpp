#include <folly/File.h>
#include <folly/Memory.h>
#include <folly/init/Init.h>
#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>
#include <proxygen/httpserver/filters/DirectResponseHandler.h>
#include <atomic>

#include <glog/logging.h>
#include <memory>
#include <iostream>

#include "utils/compilHandler.h"
#include "utils/queryallHandler.h"
#include "utils/queryHandler.h"
#include "utils/dbCon.h"
using namespace proxygen;
using folly::SocketAddress;

// using Protocol = HTTPServer::Protocol;
DEFINE_int32(http_port, 1503, "Port to listen on");
DEFINE_int32(http2_port, 1502, "Port to listen on with HTTP/2 protocol");
DEFINE_string(ip, "127.0.0.1", "IP/Hostname to bind to");
DEFINE_int32(threads,
             0,
             "Number of threads to listen on. Numbers <= 0 "
             "will use the number of cores on this machine.");
namespace {
class KFTEXHandlerFactory : public RequestHandlerFactory {
   public:
    void onServerStart(folly::EventBase* /*evb*/) noexcept override {}

    void onServerStop() noexcept override {}

    RequestHandler *onRequest(RequestHandler*,HTTPMessage* message) noexcept override {
        if (message->getPath() == "/compile") {
            LOG(INFO)<< "编译pdf文件";
            return new compilHandler(c);
        }else if(message->getPath() == "/queryall") {
            LOG(INFO)<<"查询所有pdf文件";
            return new MqueryallHandler(c);
        }else if(message->getPath()=="/query"){
            LOG(INFO)<<"查询文件内容";
            return new queryHandler(c);
        }
        else {
            LOG(INFO)<<"Page Not Found";
            return new DirectResponseHandler(404, "Not Found",
                                             "Page not found");
        }
    }
private:
    std::shared_ptr<dbconnect> c=std::make_shared<dbconnect>();
};

}  // namespace
int main(int argc, char* argv[]) {
    
    folly::init(&argc, &argv, true);
    FLAGS_logtostderr =1;
    std::vector<HTTPServer::IPConfig> IPs = {
        {folly::SocketAddress(FLAGS_ip, FLAGS_http_port, true),
         HTTPServer::Protocol::HTTP},
         {folly::SocketAddress(FLAGS_ip, FLAGS_http2_port, true),HTTPServer::Protocol::HTTP2}
    };

    if (FLAGS_threads <= 0) {
        FLAGS_threads = sysconf(_SC_NPROCESSORS_ONLN);
        CHECK_GT(FLAGS_threads, 0);
    }
    HTTPServerOptions options;
    options.threads = static_cast<size_t>(FLAGS_threads);
    options.idleTimeout = std::chrono::milliseconds(60000);
    options.shutdownOn = {SIGINT, SIGTERM};
    options.enableContentCompression = true;
    options.h2cEnabled = true;
    options.handlerFactories =
        RequestHandlerChain().addThen<KFTEXHandlerFactory>().build();
    // auto diskIOThreadPool = std::make_shared<folly::CPUThreadPoolExecutor>(
    //     FLAGS_threads,
    //     std::make_shared<folly::NamedThreadFactory>("StaticDiskIOThread"));
    // folly::setUnsafeMutableGlobalCPUExecutor(diskIOThreadPool);
    HTTPServer server(std::move(options));
    server.bind(IPs);
    // // Start HTTPServer mainloop in a separate thread
    std::thread t([&]() { server.start(); });
    t.join();
    LOG(INFO) << "Sever closed";
    google::ShutdownGoogleLogging();
    return 0;
}