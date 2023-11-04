/**
 * @brief this file will contain all api definitions from Server.hpp
*/

#include <iostream>
#include <BaseTypes.hpp>
#include <Globals.hpp>
#include <Utility.hpp>

SRegisterInfo Register() {
    SRegisterInfo reginfo;
    
    for(auto& cam : g_cameraList) {
        reginfo.cameraList.push_back(cam);
    } reginfo.clientId = Utils::getUID();
    
    return reginfo;
}