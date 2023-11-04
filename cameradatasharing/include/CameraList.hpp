#pragma once

#include <BaseTypes.hpp>
#include <fstream>
#include <stdexcept>
#include <list>
#include <Utility.hpp>

// ---- proposed data structure ---- //
class CameraList :std::vector<SCamera> {
    public:
        using std::vector<SCamera>::begin;
        using std::vector<SCamera>::end;
        using std::vector<SCamera>::size;
        using std::vector<SCamera>::operator[];
    public:
        CameraList(std::string _filePath) : m_filePath(_filePath) {}
        /**
         * @brief
         *      - initialize() will find a config file
         *      - then parse it to create array of SCamera
        */
        void initialize() {

            std::fstream fileHandle(m_filePath);
            if(!fileHandle.is_open()) throw std::runtime_error("could not open/find cameralist.conf file");

            while(true) {
                std::string data;
                if(!std::getline(fileHandle,data)) break;
                
                std::stringstream ss(data);
                SCamera camera;
                std::string resolutions;
                ss
                    >> camera.cameraId
                    >> camera.cameraName
                    >> camera.pixel
                    >> resolutions
                    >> camera.frameRate
                    >> camera.sensorSize
                    >> camera.fov;
                uint8_t index = 0;
                std::stringstream ss1(resolutions);
                std::string tmpRes;
                while(std::getline(ss1, tmpRes, ',')) {
                    camera.resolutions.push_back(tmpRes);
                    tmpRes.clear();
                }
                this->push_back(camera);
            }

        }
        void fillCaptureDevices(std::map<cameraid_t, cv::VideoCapture>&  _captureDevices){
           
            for(auto& var: (*this)){
                _captureDevices.insert(
                    std::make_pair<cameraid_t,cv::VideoCapture>(
                        var.cameraId.c_str(),cv::VideoCapture(std::string("/dev/")+var.cameraId)
                    )
                );
                
                int indexn = var.resolutions.size() - 1;
                resolution_s res = Utils::get_resolution(var.resolutions[indexn]);

                std::cout<<"Set height: "<<res.height<<"Set width: "<<res.width<<std::endl;
                std::cout<<"cameraID "<<var.cameraId<<std::endl;

                _captureDevices[var.cameraId].set(cv::CAP_PROP_FRAME_HEIGHT, res.height);
                _captureDevices[var.cameraId].set(cv::CAP_PROP_FRAME_WIDTH, res.width);

                std::cout
                    <<"Height after set max res : "<<_captureDevices[var.cameraId].get(cv::CAP_PROP_FRAME_HEIGHT)
                    <<"Width after set max res : "<<_captureDevices[var.cameraId].get(cv::CAP_PROP_FRAME_WIDTH)<<std::endl;
            }
        }
    private:
        const std::string m_filePath;
};
// --------------------------------- //