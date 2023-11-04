#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using clientid_t = int;
using cameraid_t = std::string;

struct SCamera
{
    cameraid_t cameraId;
    std::string cameraName;
    uint8_t pixel;              // What is pixel 
    std::vector<std::string> resolutions;
    int frameRate;
    std::string sensorSize;     // What isSensorSize and why string ?
    int fov;                    // Field of view (float)

    SCamera()
    {
        cameraId = "";
        cameraName = "";
        pixel = 0;
        frameRate = 0;
        sensorSize = "";
        fov = 0;
    }
};

enum class ECaptureMode
{
    image, video
};

struct SConfiguration
{
    cameraid_t cameraId;
    std::string resolution;
    bool cameraState;
    ECaptureMode captureMode;

    SConfiguration()
    {
        cameraId = "";
        resolution = "";
        cameraState = false;
        captureMode = ECaptureMode::image;
    }
};

struct SCameraAttr
{
    SConfiguration configuration;
    cv::VideoCapture* captureDevice;
    int threadId;
    bool threadFlag;
};

// struct SClient
// {
//     SConfiguration *configuration;
//     cv::VideoCapture *captureDevice;
//     int *threadId;
//     bool *threadFlag;
//     SClient() : configuration(nullptr), captureDevice(nullptr), threadId(nullptr), threadFlag(nullptr) {}
// };
// std::map<int,SCameraAttr> sclient;

struct SRegisterInfo
{
    int clientId;
    std::vector<SCamera> cameraList;
};
