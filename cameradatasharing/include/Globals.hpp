#pragma once

#include <CameraList.hpp>
#include <map>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
constexpr char filename[] = "../cameralist.conf";

using cameramap_t = std::map<cameraid_t,SCameraAttr>;

extern CameraList g_cameraList;
// extern std::vector<SClient> clientList;
extern std::map<clientid_t, cameramap_t> clientMap;
extern int clientID;
extern std::map<cameraid_t, cv::VideoCapture> g_captureDevices;
extern std::map<cameraid_t, std::mutex> g_mutexMap;
