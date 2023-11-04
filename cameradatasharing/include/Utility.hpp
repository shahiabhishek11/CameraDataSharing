#pragma once

#include <stdint.h>
#include <string>
#include <iostream>
#include <sstream>

struct resolution_s {
    int width;
    int height;
};
class Utils {
    private:
        static int m_uid;
    public:
        template <typename list_type>
        static void log(list_type _camlist) {
            for(auto& camera : _camlist) {
                std::cout
                    << "// -------------------- //\n"
                    << "cameraid        -> " << camera.cameraId << "\n"
                    << "cameraname      -> " << camera.cameraName << "\n"
                    << "pixel           -> " << camera.pixel << "\n"
                    << "resolutions     -> " << [&]{
                        std::string list;
                        for(uint8_t i = 0; i < camera.resolutions.size(); i++) {
                            list += camera.resolutions[i] + " ";
                        } return list;
                    }() << "\n"
                    << "framerate       -> " << camera.frameRate << "\n"
                    << "sensorsize      -> " << camera.sensorSize << "\n"
                    << "fov             -> " << camera.fov << "\n"
                    << "// -------------------- //\n";
            }
        }
        static int getUID() {
            return m_uid++;
        }
        
        static bool notnull(void* _arg) { return (_arg != nullptr); }
        static bool isnull(void* _arg) { return (_arg == nullptr); }

        static resolution_s get_resolution(std::string _res) {
            std::stringstream ss(_res);
            resolution_s resolution;
            std::string tmp;
            int index = 0;
            while(std::getline(ss, tmp, 'x')) {
                ((int *)&resolution)[index++] = std::stoi(tmp);
            } return resolution;
        }
};
