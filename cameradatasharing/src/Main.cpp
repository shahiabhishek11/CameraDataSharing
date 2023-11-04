#include "Server.h"
#include <CameraList.hpp>
#include <Globals.hpp>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

CameraList g_cameraList(filename);
std::map<cameraid_t, cv::VideoCapture> g_captureDevices;
std::map<cameraid_t, std::mutex> g_mutexMap;
// std::vector<SClient> clientList;
std::map<clientid_t, cameramap_t> clientMap;

ABSL_FLAG(std::string, target, "localhost:1999", "Server address");

int main(int argc, char *argv[]) {

    g_cameraList.initialize();
    g_cameraList.fillCaptureDevices(g_captureDevices);
    for(auto& it : g_captureDevices) {
        g_mutexMap[it.first].unlock();
    }
    std::cout << "g_mutexMap size = " << g_mutexMap.size() << "\n";
    absl::ParseCommandLine(argc, argv);
    std::string server_address = absl::GetFlag(FLAGS_target);

    std::cout << "Going to Start the Server\n";
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    SensorSharingImpl ss;
    builder.RegisterService(&ss);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on {}" << server_address << "\n";
    server->Wait();

    return 0;
}
