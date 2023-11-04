#pragma once

#include "sensorsharing.grpc.pb.h"
#include <grpc++/grpc++.h>

#include <thread>
#include <chrono>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using sspkg::Configurations;
using sspkg::Request;
using sspkg::Camera;
using sspkg::RegisterInfo;
using sspkg::Frame;
using sspkg::CaptureMode;
using sspkg::Configuration;
using sspkg::Response;
using sspkg::SensorSharing;

class SensorSharingImpl final : public SensorSharing::Service {
    public:
        ::grpc::Status register_(
            ::grpc::ServerContext* context,
            const ::Request* request,
            ::RegisterInfo* response
        );
        ::grpc::Status captureImage(
            ::grpc::ServerContext* context,
            const ::Request* request,
            ::Frame* response
        );
        ::grpc::Status getConfiguration(
            ::grpc::ServerContext* context,
            const ::Request* request,
            ::Configurations* response
        );
        ::grpc::Status setConfiguration(
            ::grpc::ServerContext* context,
            const ::Request* request,
            :: Response* response
        );

        ::grpc::Status toggleCameraState(
            ::grpc::ServerContext* context,
            const ::Request* request,
            :: Response* response
        );

        ::grpc::Status startStream(
            ::grpc::ServerContext* context,
            const ::Request* request,
            ::grpc::ServerWriter<Frame>* response
        );


        ::grpc::Status stopStream(
            ::grpc::ServerContext* context,
            const ::Request* request,
            :: Response* response
        );

        ::grpc::Status deregister(
            ::grpc::ServerContext* context,
            const ::Request* request,
            :: Response* response
        );

        void init_seq(cv::VideoCapture&);
        
};