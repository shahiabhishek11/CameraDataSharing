#include <grpc++/grpc++.h>
#include <gtest/gtest.h>
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <BaseTypes.hpp>
#include <Globals.hpp>

#include <thread>
#include "Server.h"
//Open CV includes
#include <opencv2/highgui.hpp>

#include <iostream>
//Opencv and GRPC namespaces
using namespace grpc;
using namespace std;
using namespace cv;

using sspkg::Configurations;
using sspkg::Request;
using sspkg::Camera;
using sspkg::RegisterInfo;
using sspkg::Frame;
using sspkg::CaptureMode;
using sspkg::Configuration;
using sspkg::Response;
using sspkg::SensorSharing;

using grpc::ClientReader;
typedef unsigned char byte;

// #define test1
// #define test2
// #define test3
// #define test4
#define test5

ABSL_FLAG(std::string, target, "localhost:1999", "Server address");

std::atomic<bool> terminate_flag{false};

void signal_handler(
	int _signal_id
) {
	terminate_flag = true;
	std::cout << "executing signal handler...\n";
}

class SensorSharingClient {
	public:
		SensorSharingClient(
			std::shared_ptr<Channel> channel
		) : stub_(SensorSharing::NewStub(channel)) {}

		/**
		 * will get called when button is pressed
		*/
		std::string registerClient() {
			RegisterInfo response;
			ClientContext context;
			Request request;
			// request.set_clientid(2294);
			Status status = stub_->register_(&context, request, &response);
			if (status.ok()) {
				// std::cout
				// 	<< "Client ID : " << response.clientid() << "\n";
				for(uint8_t i = 0; i < response.cameralist_size(); i++) {
					// std::cout
					// 	<< "Cam ID 		: " << response.cameralist(i).cameraid() << "\n"
					// 	<< "Cam Name 	: " << response.cameralist(i).cameraname() << "\n";
				}
				return "registerClient Success\n";
			} else {
				std::cout << status.error_code() << ": " << status.error_message()
						<< std::endl;
				return "registerClient failed\n";
			} 
		}

		std::string getConf() {
			ClientContext context;
			Request req;
			Configurations resp;
			req.set_clientid(0);
			auto status = stub_->getConfiguration(&context, req, &resp);
			if(status.ok()) {
				std::cout
					<< resp.conf()[0].cameraid() << "\n";
				return "getConfiguration success!\n";
			} else return "getConfiguration failure\n";
		}

		std::string getImage() {
			ClientContext context;
			Request req;
			Frame* resp = new Frame;
			req.set_clientid(0);
			req.set_cameraid("usb_video0");
			auto status
				= stub_->captureImage(&context, req, resp);
			if(status.ok()) {
				
    			cv::Mat matImg
					= cv::imdecode(
						cv::Mat(1, resp->rawbuffer().length(), CV_8UC1, (void*)resp->rawbuffer().c_str()),
						cv::IMREAD_UNCHANGED
					);
				
				cv::Mat tmp(
					static_cast<int>(resp->height()),
					static_cast<int>(resp->width()),
					CV_8UC3,
					matImg.data
				);

				// std::cout
				// 	<< "data length -> " << resp->rawbuffer().c_str() << "\n";
				// std::cout<<"\n Height "<<resp->height();
				// std::cout<<"\n Width "<<resp->width();

				cv::imwrite("captured_image" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".png", tmp);
				return "getImage success...\n";
			} else { return "getImage failed...\n"; }
		}

		std::string setConf() {
			ClientContext context;
			Request req;
			Response resp;

			Configuration* config = req.mutable_configlist()->add_conf();
			req.set_clientid(0);
			req.set_cameraid("usb_video0");
			config->set_cameraid("usb_video0");
			config->set_camerastate(true);
			config->set_capturemode(CaptureMode::image);
			config->set_resolution("640x480");

			auto status =stub_->setConfiguration(&context, req, &resp);
			if(status.ok()) {
				return "setConfiguration success...\n";
			} else return "setConfiguration failed...\n";
		}

		std::string toggleCameraState() {
			Request req;
			Response resp;
			ClientContext context;

			req.set_clientid(0);
			req.set_cameraid("usb_video0");
			
			auto status = stub_->toggleCameraState(&context,req,&resp);

			if(status.ok()) {
				return "toggle camera success";
			} else { return "toggle camera failed"; }
		}

		/**
		 * as of now this is a blocking function call
		*/
		std::string startStream() {

			Request req;
			Frame resp;
			ClientContext context;

			//auto status=stub_->startStream(&context,req,&resp);
			req.set_clientid(0);
			req.set_cameraid("usb_video0");

			std::unique_ptr<ClientReader<Frame>> reader(stub_->startStream(&context,req));

			int j = 0;
			string path = "";
			while (reader->Read(&resp)) {
	        	int datalen = resp.rawbuffer().length();
				// std::cout << "raw buffer length -> " << resp.rawbuffer().length() << "\n";
	            // cout << "Received Data " << datalen << endl;
	            // cout << "Expected data " << response.datalen() << endl;
				if (3 != resp.channel()) {
					cout << "channel Mismatch" << endl;
				}
				//Get the Mat back
				int height = resp.height();
				int width = resp.width();

				// std::cout << "Width : " << width << std::endl;
				// std::cout << "Height: " << height << std::endl;
				if ((height > 0) && (width > 0)) {
					cv::Mat matImg
						= cv::imdecode(
							cv::Mat(1, resp.rawbuffer().length(), CV_8UC1, (void*)resp.rawbuffer().c_str()),
							cv::IMREAD_UNCHANGED
						);
					cv::Mat image(
						height, width, CV_8UC3, 
						matImg.data
					);
					path = "output" + to_string(j) + ".png";
					cv::imwrite(path, image);
					j++;
				} else {
					std::cout << "height == width == 0\n";
				}
			}
			Status status = reader->Finish();

			if (status.ok()) {
				return "startStream success...\n";
			} else {
				return "startStream failed...\n";
			}
		}

		void stopStream() {
			Request req;
			Response resp;
			ClientContext context;

			auto status=stub_->stopStream(&context,req,&resp);

			if(status.ok()) {
				std::cout<<"\n Stop stream state called ...\n";		
			} else {
				std::cout<<"\n Fail to call stop stream..\n";
			}

		}

		std::string deregister() {
			Request req;
			Response resp;
			ClientContext context;

			req.set_clientid(0);
			req.set_cameraid("usb_video0");

			auto status = stub_->deregister(&context,req,&resp);

			if(status.ok()) {
				return "deregister success...\n";			
			} else {
				return "deregister failed..\n";
			}
		}

	private:
		std::unique_ptr<SensorSharing::Stub> stub_;
};

int main(int argc, char **argv) {

    absl::ParseCommandLine(argc, argv);
	signal(SIGINT, signal_handler);
    std::string target_str = absl::GetFlag(FLAGS_target);
    
	#ifdef test1
	// ---- Test 1 ---- //
	{
		SensorSharingClient client(
			grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())
		);
		std::cout << client.registerClient() << std::endl;
		std::cout << client.getConf() << std::endl;
		
		std::thread th_obj([&](){ std::cout << client.startStream(); });
		std::this_thread::sleep_for(
			std::chrono::milliseconds(5000)
		);
		client.stopStream();
		th_obj.join();
	}
	#endif

	#ifdef test2
	// ---- Test 2 ---- //
	{
		SensorSharingClient client(
			grpc::CreateChannel(
				target_str, grpc::InsecureChannelCredentials()
			)
		);
		std::cout
			<< client.registerClient() << "\n";
		std::cout
			<< client.setConf() << "\n";
		
		std::thread th_obj([&](){ std::cout << client.startStream(); });
		std::this_thread::sleep_for(
			std::chrono::milliseconds(5000)
		);
		client.stopStream();
		th_obj.join();
		client.deregister();
	}
	#endif

	#ifdef test3
	// ---- Test 3 ---- //
	{
		SensorSharingClient client(
			grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())
		);
		std::cout << client.registerClient() << "\n";
		std::cout << client.setConf() << "\n";
		
		// while(!terminate_flag) {
		// 	std::cout
		// 		<< client.getImage() << "\n";
		// 	std::this_thread::sleep_for(
		// 		std::chrono::milliseconds(1000)
		// 	);
		// }

		std::cout << client.deregister() << "\n";
	}
	#endif

	#ifdef test4
	// ---- Test 4 ---- //
	{
		SensorSharingClient client(
			grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())
		);
		std::cout << client.registerClient() << "\n";
		std::cout << client.getConf() << "\n";
		
		// while(!terminate_flag) {
		// 	std::cout
		// 		<< client.getImage() << "\n";
		// 	std::this_thread::sleep_for(
		// 		std::chrono::milliseconds(1000)
		// 	);
		// }

		client.deregister();
	}
	#endif

	#ifdef test5
	// ---- Test 5 ---- //
	{
		SensorSharingClient client(
			grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())
		);
		std::cout << client.registerClient() << "\n";
		std::cout << client.getConf() << "\n";
		std::cout << client.getImage() << "\n";
		std::cout << client.toggleCameraState() << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		std::cout << client.toggleCameraState() << "\n";
		std::cout << client.getImage() << "\n";
		std::cout << client.deregister() << "\n";

	}
	#endif

	while(!terminate_flag);
    
	return 0;
}