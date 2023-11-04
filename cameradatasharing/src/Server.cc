#include "Server.h"
#include "ServerImpl.hpp"

#include <Globals.hpp>
#include <Utility.hpp>
#define ATTEMPTS 3

using namespace std;
using namespace grpc;
using namespace chrono;

void SensorSharingImpl::init_seq(cv::VideoCapture &_vc)
{
    cv::Mat mat;
    for (int index = 0; index < 5; index++) {
        _vc.read(mat);
    }
}

/**
 * @note :  maybe we should create a instance in clientMap
 *          on register function itself
 */
::grpc::Status SensorSharingImpl::register_(
    ::grpc::ServerContext *context,
    const ::Request *request,
    ::RegisterInfo *response)
{
    std::cout << "executing register_ rpc call\n";

    SRegisterInfo &&ret = Register();
    clientid_t cid = Utils::getUID();
    response->set_clientid(cid);
    for (uint8_t i = 0; i < g_cameraList.size(); i++)
    {
        Camera *cam = response->add_cameralist();
        cam->set_cameraid(g_cameraList[i].cameraId);
        cam->set_cameraname(g_cameraList[i].cameraName);
        cam->set_pixel(g_cameraList[i].pixel);
        cam->set_framerate(g_cameraList[i].frameRate);
        cam->set_sensorsize(g_cameraList[i].sensorSize);
        cam->set_fov(g_cameraList[i].fov);
        for (uint8_t j = 0; j < g_cameraList[i].resolutions.size(); j++)
        {
            cam->add_resolutions(g_cameraList[i].resolutions[j]);
        }
    }
    return ::grpc::Status::OK;
}

/**
 * @brief :
 *      1. create an instance of SClient
 *      2. create a Configuration array using default values from CameraList
 *      3. create Video Capture device array also
 *
 * @note first we find if there is any entry against the requested client ID
 *       if yes then we will simply assign the newly created client at that index
 *       else we will make an entry at the end
 *
 * @note This will have some problems that the sequence
 *       of client IDs will not be retained
 *
 */
::grpc::Status SensorSharingImpl::getConfiguration(
    ::grpc::ServerContext *context,
    const ::Request *request,
    ::Configurations *response)
{

    try
    {
        // SClient& client = clientList.at(request->clientid());
        cameramap_t &cam_map = clientMap.at(request->clientid());

        std::cout
            << "found existing client...\n";
        for (auto &cam : cam_map)
        {
            Configuration *conf = response->add_conf();
            conf->set_cameraid(cam.second.configuration.cameraId);
            conf->set_camerastate(cam.second.configuration.cameraState);
            conf->set_capturemode(
                static_cast<CaptureMode>(cam.second.configuration.captureMode));
            conf->set_resolution(cam.second.configuration.resolution);
        }

        // ---- old tested code ---- //
        // int index = 0;
        // while(index < g_cameraList.size()) {
        //     Configuration* conf = response->add_conf();
        //     conf->set_cameraid(client.configuration[index].cameraId);
        //     conf->set_camerastate(client.configuration[index].cameraState);
        //     conf->set_capturemode(
        //         static_cast<CaptureMode>(client.configuration[index].captureMode)
        //     );
        //     conf->set_resolution(client.configuration[index].resolution);
        //     index++;
        // }
        // ------------------------ //
    }
    catch (...)
    {

        std::cout
            << "making new entry for a client...\n";

        cameramap_t cam_map;

        // SClient tmpClient;
        // tmpClient.configuration = new SConfiguration[g_cameraList.size()];
        // tmpClient.captureDevice = new cv::VideoCapture[g_cameraList.size()];
        // tmpClient.threadId      = new int[g_cameraList.size()];
        // tmpClient.threadFlag    = new bool[g_cameraList.size()];

        // uint8_t index = 0;
        for (auto &cam : g_cameraList)
        {

            SCameraAttr attr;
            attr.configuration.cameraId = cam.cameraId;
            attr.configuration.cameraState = true;
            attr.configuration.captureMode = ECaptureMode::image;
            attr.configuration.resolution = cam.resolutions[0];

            resolution_s res = Utils::get_resolution(cam.resolutions[0]);

            std::cout
                << "GetConfig::Height" << res.height << "\n"
                << "GetConfig::Width " << res.width << "\n"
                << "camera id = " << cam.cameraId << "\n";
            attr.captureDevice = &(g_captureDevices[cam.cameraId]);
            // attr.captureDevice.open("/dev/" + cam.cameraId);
            if (!attr.captureDevice->isOpened())
            {
                std::runtime_error(
                    "could not initialize cv::VideoCapture for camera id [" + cam.cameraId + "]");
            }
            //Moved the .set lines after the .open function. 
            //Resolution is automatically selected to the closest supported or the highest supported.
            // std::cout<<"width after captureDevice:"<<(attr.captureDevice.get(cv::CAP_PROP_FRAME_WIDTH))<<std::endl;
            // std::cout<<"height after captureDevice:"<<(attr.captureDevice.get(cv::CAP_PROP_FRAME_HEIGHT))<<std::endl;
            // attr.captureDevice.set(cv::CAP_PROP_FRAME_WIDTH, res.width);
            // attr.captureDevice.set(cv::CAP_PROP_FRAME_HEIGHT, res.height);

            attr.threadFlag = false;
            attr.threadId = -1;

            cam_map.insert(std::make_pair(cam.cameraId, attr));

            // ---- old tested mechanism with clientList & SClient ---- //
            // tmpClient.configuration[index].cameraId
            //     = cam.cameraId;
            // tmpClient.configuration[index].cameraState
            //     = true;
            // tmpClient.configuration[index].captureMode
            //     = ECaptureMode::image;
            // tmpClient.configuration[index].resolution
            //     = cam.resolutions[0];
            // tmpClient.captureDevice[index]
            //     = cv::VideoCapture(cam.cameraId);
            // resolution_s res = Utils::get_resolution(cam.resolutions[0]);
            // tmpClient.captureDevice[index].set(cv::CAP_PROP_FRAME_WIDTH, res.width);
            // tmpClient.captureDevice[index].set(cv::CAP_PROP_FRAME_HEIGHT, res.height);
            // /**
            //  * while creating the VideoCapture instance ask prady
            //  * to create a pipeline object here only using the resolution
            //  * being used above
            // */
            // tmpClient.threadFlag[index]
            //     = false;
            // tmpClient.threadId[index]
            //     = -1;
            // -------------------------------------------------------- //

            Configuration *conf = response->add_conf();
            conf->set_cameraid(cam.cameraId);
            conf->set_camerastate(attr.configuration.cameraState);
            conf->set_capturemode(CaptureMode::image);
            conf->set_resolution(cam.resolutions[0]);

            // index++;
        }

        clientMap.insert_or_assign(request->clientid(), cam_map);
    }

    return ::grpc::Status::OK;
}

::grpc::Status SensorSharingImpl::setConfiguration(
    ::grpc::ServerContext *context,
    const ::Request *request,
    ::Response *response)
{
    std::cout << "\nexecuting setConfiguration...\n";

    /**
     * first check if there is an entry for the client ID passed
     * if yes then set the new configuration in that instance of SClient
     * else create a new instance of SClient and prepare the configuration array and push into the clientList
     */

    try
    {

        cameramap_t &cam_map = clientMap.at(request->clientid());
        // clientMap.erase(request->clientid());
        std::cout << "requested client ID -> " << request->clientid() << "\n";
        std::cout << "requested cam ID -> " << request->cameraid() << "\n";
        std::cout << "configlist size -> " << request->configlist().conf_size() << "\n";

        for (int index = 0; index < request->configlist().conf_size(); index++)
        {

            const Configuration &conf = request->configlist().conf(index);

            SCameraAttr attr;
            attr.configuration.cameraId = conf.cameraid();
            attr.configuration.cameraState = conf.camerastate();
            attr.configuration.captureMode = static_cast<ECaptureMode>(conf.capturemode());
            attr.configuration.resolution = conf.resolution();

            resolution_s res = Utils::get_resolution(conf.resolution());
            std::cout << "\n setConfig::Height" << res.height << std::endl;
            std::cout << "\n setConfig::Width " << res.width << std::endl;
            // cam_map[conf.cameraid()].captureDevice->release();
            // attr.captureDevice.open("/dev/" + conf.cameraid());
            attr.captureDevice = &(g_captureDevices[conf.cameraid()]);
            if (!attr.captureDevice->isOpened())
            {
                std::runtime_error(
                    "could not initialize cv::VideoCapture for camera id [" + conf.cameraid() + "]");
            }
            //Moved the .set lines after the .open function.
            // attr.captureDevice->set(cv::CAP_PROP_FRAME_WIDTH, res.width);
            // attr.captureDevice->set(cv::CAP_PROP_FRAME_HEIGHT, res.height);
            // std::cout<<"width after captureDevice in setConfig:"<<(attr.captureDevice.get(cv::CAP_PROP_FRAME_WIDTH))<<std::endl;
            // std::cout<<"height after captureDevice in setConfig:"<<(attr.captureDevice.get(cv::CAP_PROP_FRAME_HEIGHT))<<std::endl;


            attr.threadFlag = false;
            attr.threadId = -1;

            cam_map.insert_or_assign(conf.cameraid(), attr);

            // ---- old tested code ---- //
            // const Configuration& c = request->configlist().conf(index);
            // client.threadFlag[index] = false;
            // client.configuration[index].cameraId    = c.cameraid();
            // std::cout << "cam ID -> " << c.cameraid() << "\n";
            // client.configuration[index].cameraState = c.camerastate();
            // client.configuration[index].captureMode = static_cast<ECaptureMode>(c.capturemode());
            // client.configuration[index].resolution  = c.resolution();
            // /**
            //  * here only configuration array is being filled
            //  * do we need to fill other three arrays of SClient as well?
            //  * @note : here we will have to create at least the captureDevice array
            //  * using the resolutions passed
            // */
            // resolution_s res = Utils::get_resolution(c.resolution());
            // client.captureDevice[index] = cv::VideoCapture(c.cameraid());
            // // client.captureDevice[index].set(cv::CAP_PROP_HW_DEVICE, c.cameraid());
            // client.captureDevice[index].set(cv::CAP_PROP_FRAME_HEIGHT, res.height);
            // client.captureDevice[index].set(cv::CAP_PROP_FRAME_WIDTH, res.width);
            // // client.captureDevice[index].set(cv::CAP_PROP_BUFFERSIZE, 3);
            // // init_seq(client.captureDevice[index]);
            // -------------------------- //
        }
    }
    catch (...)
    {

        cameramap_t cam_map;

        for (int index = 0; index < request->configlist().conf_size(); index++)
        {

            const Configuration &conf = request->configlist().conf(index);
            SCameraAttr attr;
            attr.configuration.cameraId = conf.cameraid();
            attr.configuration.cameraState = conf.camerastate();
            attr.configuration.captureMode = static_cast<ECaptureMode>(conf.capturemode());
            attr.configuration.resolution = conf.resolution();

            resolution_s res = Utils::get_resolution(conf.resolution());
            std::cout << "\n setConfig::Height" << res.height << std::endl;
            std::cout << "\n setConfig::Width " << res.width << std::endl;
            // attr.captureDevice.open(conf.cameraid());
            attr.captureDevice = &(g_captureDevices[conf.cameraid()]);
            if (!attr.captureDevice->isOpened())
            {
                std::runtime_error(
                    "could not initialize cv::VideoCapture for camera id [" + (conf.cameraid()) + "]");
            }

            // attr.captureDevice.set(cv::CAP_PROP_FRAME_WIDTH, res.width);
            // attr.captureDevice.set(cv::CAP_PROP_FRAME_HEIGHT, res.height);
            // std::cout<<"width after captureDevice in setConfig(catch block):"<<(attr.captureDevice.get(cv::CAP_PROP_FRAME_WIDTH))<<std::endl;
            // std::cout<<"height after captureDevice in setConfig(catch block):"<<(attr.captureDevice.get(cv::CAP_PROP_FRAME_HEIGHT))<<std::endl;

            attr.threadFlag = false;
            attr.threadId = -1;
            cam_map.insert_or_assign(conf.cameraid(), attr);
        }
        clientMap.insert(std::make_pair(request->clientid(), cam_map));

        // ---- old tested code ---- //
        // SClient client;
        // client.configuration    = new SConfiguration[request->configlist().conf_size()];
        // client.captureDevice    = new cv::VideoCapture[request->configlist().conf_size()];
        // client.threadFlag       = new bool[request->configlist().conf_size()];
        // client.threadId         = new int[request->configlist().conf_size()];
        // std::cout << "configlist size -> " << request->configlist().conf_size() << "\n";
        // for(uint8_t index = 0; index < request->configlist().conf_size(); index++) {
        //     const Configuration& c = request->configlist().conf(index);
        //     client.configuration[index].cameraId
        //         = c.cameraid();
        //     client.configuration[index].cameraState
        //         = c.camerastate();
        //     client.configuration[index].captureMode
        //         = static_cast<ECaptureMode>(c.capturemode());
        //     client.configuration[index].resolution
        //         = c.resolution();
        //     resolution_s res = Utils::get_resolution(c.resolution());
        //     std::cout
        //         << "res::width -> " << res.width << " : "
        //         << "res::height -> " << res.height << "\n";
        //     std::cout << "cameraid -> " << client.configuration[index].cameraId << "\n";
        //     client.captureDevice[index] = cv::VideoCapture(c.cameraid());
        //     // client.captureDevice[index].set(cv::CAP_PROP_HW_DEVICE, c.cameraid());
        //     client.captureDevice[index].set(cv::CAP_PROP_FRAME_HEIGHT, res.height);
        //     client.captureDevice[index].set(cv::CAP_PROP_FRAME_WIDTH, res.width);
        //     // client.captureDevice[index].set(cv::CAP_PROP_BUFFERSIZE, 3);
        //     // init_seq(client.captureDevice[index]);
        // }
        // clientMap.insert_or_assign(request->clientid(), client);
        // ------------------------- //
    }

    return ::grpc::Status::OK;
}

::grpc::Status SensorSharingImpl::captureImage(
    ::grpc::ServerContext *context,
    const ::Request *request,
    ::Frame *response)
{
    /**
     * this function will find a video capture device instance
     * using the camera id
     * then read a frame and make a grpc::Frame type to send
     */

    std::cout << "executing captureImage rpc...\n";
    std::cout
        << "client id : [" << request->clientid() << "]\n"
        << "camera id : [" << request->cameraid() << "]\n";

    try
    {
        int currentAttemptCount=1;

        currentAttemptCount++;
        std::cout<<"Starting while loop \n";
        cameramap_t &cam_map = clientMap.at(request->clientid());
        SCameraAttr &cam_attr = cam_map[request->cameraid()];
        std::cout << cam_attr.configuration.resolution;
        cv::VideoCapture &cap_device = *(cam_attr.captureDevice);

        std::cout<<"in capture width"<<(cap_device.get(cv::CAP_PROP_FRAME_WIDTH))<<std::endl;
        std::cout<<"in capture height"<<(cap_device.get(cv::CAP_PROP_FRAME_HEIGHT))<<std::endl;

        resolution_s res = Utils::get_resolution(cam_attr.configuration.resolution);
        
        cv::Mat tmp_img;
        cv::Mat local_image;
        std::uint64_t timestamp;

        
        cap_device.read(tmp_img);
        if(tmp_img.size().width <= 0 && tmp_img.size().height <= 0 ) {
            std::cout << "recreating VideoCapture for [" << request->cameraid() << "]\n";
            cap_device.release();
            cap_device.open("/dev/" + request->cameraid());
            if (!cap_device.isOpened()) {
                std::runtime_error(
                    "could not initialize cv::VideoCapture for camera id [" + (request->cameraid()) + "]");
            }
            resolution_s res = Utils::get_resolution(cam_attr.configuration.resolution);
            cap_device.set(cv::CAP_PROP_FRAME_WIDTH, res.width);
            cap_device.set(cv::CAP_PROP_FRAME_HEIGHT, res.height);

        }

        init_seq(cap_device);

        if(g_mutexMap[request->cameraid()].try_lock()) {
            cap_device >> local_image;
            g_mutexMap[request->cameraid()].unlock();
            // break;
        }
        else
        {
            std::cout<<" Sleep State \n";
            // std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    
        timestamp=duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        cv::Mat resized_down;
        cv::resize(local_image, resized_down, cv::Size(res.width, res.height));
        std::cout
            << "width -> " << local_image.size().width << " : "
            << "height -> " << local_image.size().height << "\n";
        std::vector<u_char> buffer;
        std::cout << "buffer var created...\n";
        cv::imencode(".png", resized_down, buffer);

        // // ---- old code ---- //
        // cv::Mat local_image;
        // cap_device >> local_image;
        // std::cout
        //     << "width -> " << local_image.size().width << " : "
        //     << "height -> " << local_image.size().height << "\n";
        // std::vector<u_char> buffer;
        // std::cout << "buffer var created...\n";
        // cv::imencode(".png", local_image, buffer);
        // // ------------- //

        std::cout << "imencoded...\n";
        std::string str(buffer.begin(), buffer.end());
        std::cout << "std::string var created...\n";
        std::cout << "image buffer length : " << buffer.size() << "\n";

        response->set_rawbuffer(str);
        response->set_channel(local_image.channels());
        response->set_width(local_image.size().width);
        response->set_height(local_image.size().height);
        response->set_timestamp(timestamp);

        return ::grpc::Status::OK;
    }
    catch (...)
    {
        std::cout << "requested client id & camera id led to an exception";
        return ::grpc::Status::CANCELLED;
    }

    // ---- old tested code ---- //
    // std::cout << "executing captureImage rpc...\n";
    // uint8_t index = 0;
    // std::cout << "client ID -> " << request->clientid() << "\n";
    // SClient& client = clientMap[request->clientid()];
    // std::cout << "clientlist size -> " << clientMap.size() << "\n";
    // std::cout << "after index access...\n";
    // std::cout << "( " << client.configuration[index].cameraId << ":" <<  request->cameraid() << " )\n";
    // while( index < g_cameraList.size() ) {
    //     if(
    //         client.configuration[index].cameraId == request->cameraid()
    //     ) {
    //         break;
    //     } else index++;
    // }
    // std::cout << "index in capture -> " << (int)index << "\n";
    // cv::Mat local_image;
    // init_seq(client.captureDevice[index]);
    // client.captureDevice[index] >> (local_image);
    // std::cout
    //     << "width -> " << local_image.size().width << " : "
    //     << "height -> " << local_image.size().height << "\n";
    // // cv::imwrite("/home/sdv-2534/Desktop/img.png",local_image);
    // // std::string str((char *)local_image.data);
    // //str+='\0';
    // std::vector<u_char> temp;
    // cv::imencode(".png",local_image,temp);
    // std::string str(temp.begin(),temp.end());
    // std::cout<<"\n Length ---> " <<temp.size()<<"\n";
    // response->set_rawbuffer(str);
    // response->set_channel(local_image.channels());
    // response->set_width(local_image.size().width);
    // response->set_height(local_image.size().height);
    // ------------------------ //
}

::grpc::Status SensorSharingImpl::toggleCameraState(
    ::grpc::ServerContext *context,
    const ::Request *request,
    ::Response *response)
{

    std::cout << "executing toggleCameraState rpc...\n";
    std::cout
        << "client id : [" << request->clientid() << "]\n"
        << "camera id : [" << request->cameraid() << "]\n";

    try
    {
        /**
         * @note : if try executes that means camera
         *         still exists and was not diabled
         *         thus we will set all variables and delete that entry
         */
        cameramap_t &cam_map = clientMap.at(request->clientid());
        auto &cam_attr = cam_map.at(request->cameraid());
        cam_attr.threadFlag = false;
        std::cout<<"Before EX-ORing cam_attr.configuration.cameraState"<<cam_attr.configuration.cameraState<<std::endl;
        cam_attr.configuration.cameraState ^= true;
        std::cout<<"After EX-ORing cam_attr.configuration.cameraState"<<cam_attr.configuration.cameraState<<std::endl;
        auto it = cam_map.erase(request->cameraid());

        std::cout << "[DISABLING]: removing cam [" << request->cameraid() << "]\n";
    }
    catch (...)
    {
        auto it = std::find_if(g_cameraList.begin(), g_cameraList.end(), [&](SCamera &_cam)
                               {
            if(_cam.cameraId == request->cameraid()) {
                return true;
            } else return false; });

        if (it == g_cameraList.end())
        {
            std::cout << "could not find a camera with supplied ID...\n";
            return ::grpc::Status::CANCELLED;
        }

        cameramap_t &cam_map = clientMap.at(request->clientid());
        SCameraAttr attr;
        attr.configuration.cameraId = it->cameraId;
        attr.configuration.cameraState = true;
        attr.configuration.captureMode = static_cast<ECaptureMode>(request->configlist().conf(0).capturemode());
        attr.configuration.resolution = request->configlist().conf(0).resolution();

        resolution_s res = Utils::get_resolution(attr.configuration.resolution);
        // attr.captureDevice.open(it->cameraId);
        attr.captureDevice = &(g_captureDevices[it->cameraId]);
        if (!attr.captureDevice->isOpened())
        {
            std::runtime_error(
                "could not initialize cv::VideoCapture for camera id [" + (it->cameraId) + "]");
        }
        
        // attr.captureDevice.set(cv::CAP_PROP_FRAME_WIDTH, res.width);
        // attr.captureDevice.set(cv::CAP_PROP_FRAME_HEIGHT, res.height);

        attr.threadFlag = false;
        attr.threadId = -1;

        cam_map.insert(std::make_pair(it->cameraId, attr));
        std::cout << "[ENABLING]: adding cam [" << request->cameraid() << "]\n";
    }
    // ---- old tested code ---- //
    // std::cout<<"\n  Inside toggleCameraState function";
    // int index = 0;
    // SClient& client = clientMap[request->clientid()];
    // while( index < g_cameraList.size() ) {
    //     if(
    //         client.configuration[index].cameraId == request->cameraid()
    //     ) { break; }
    //     else index++;
    // }
    // if( client.configuration[index].cameraState == true ) {
    //     client.configuration[index].cameraState = false;
    //     /**
    //      * @note :  also need to destroy the capture device
    //      *          because that is the only resource being used at server side
    //     */
    // } else { client.configuration[index].cameraState = true; }
    // /**
    //  * here write the code to turn off the atomic thread flag
    //  * to stop the stream thread while loop
    // */
    // ----------------------------- //

    return ::grpc::Status::OK;
}

/**
 * @note : this function must find the correct instance of video capture device from client array
 *         then must directly use it to fetch frames
 */
::grpc::Status SensorSharingImpl::startStream(
    ::grpc::ServerContext *context,
    const ::Request *request,
    ::grpc::ServerWriter<Frame> *response)
{

    std::cout << "executing startstream...\n";
    std::cout
        << "client id : [" << request->clientid() << "]\n"
        << "camera id : [" << request->cameraid() << "]\n";

    cameramap_t &cam_map = clientMap.at(request->clientid());
    SCameraAttr &cam_attr = cam_map[request->cameraid()];
    cv::VideoCapture &cap_device = *(cam_attr.captureDevice);
    cam_attr.threadFlag = true;

    while (cam_attr.threadFlag)
    {

        cv::Mat frame1;
        resolution_s res = Utils::get_resolution(cam_attr.configuration.resolution);
        cv::Mat frame;
        if(g_mutexMap[request->cameraid()].try_lock()) {
            cap_device >> frame1;
            g_mutexMap[request->cameraid()].unlock();
        } else {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(50)
            );    
            continue;
        }
        cv::resize(frame1, frame, cv::Size(res.width, res.height));

        std::vector<u_char> temp;
        cv::imencode(".png", frame, temp);
        std::string str(temp.begin(), temp.end());
        std::uint64_t timestamp;
        Frame f;
        f.set_rawbuffer(str);
        f.set_channel(frame.channels());
        f.set_width(frame.size().width);
        f.set_height(frame.size().height);
        f.set_timestamp(timestamp);
        if (!response->Write(f))
        {
            // break;
        }
        std::this_thread::sleep_for(
            std::chrono::milliseconds(50)
        );
    }

    // ---- old tested code ---- //
    // std::cout
    //     << "executing startStream...\n";
    // /**
    //  * create a thread with this while loop to keep sending frames to client
    //  * fetch the thread ID and store in the threadID array
    //  * enable the threadFlag for the same index
    // */
    // // std::cout << "clientID -> " << request->clientid() << "\n";
    // SClient& client = clientMap[request->clientid()];
    // int index = 0;
    // while( index < g_cameraList.size() ) {
    //     if(
    //         client.configuration[index].cameraId == request->cameraid()
    //     ) { break; }
    //     else index++;
    // }
    // client.threadFlag[index] = true;
    // cv::VideoCapture* capture = &(client.captureDevice[request->cameraid()]);
    // std::string path = "";
    // // std::cout << "1\n";
    // int j = 0;
    // // std::cout << "threadFlag[index] -> " << client.threadFlag[index] << "\n";
    // while(client.threadFlag[index]) {
    //     // std::cout << "2\n";
    //     cv::Mat frame;
    //     // std::cout << "raw buffer length --------- \n";
    //     (*capture) >> frame;
    //     path = "img" + to_string(j++) + ".png";
    //     // cv::imwrite(path, image);
    //     // std::string bytes(reinterpret_cast<char*>(frame.data));
    //     // std::cout << "raw buffer length -> " << bytes.length() << "\n";
    //     std::vector<u_char> temp;
    //     cv::imencode(".png",frame,temp);
    //     std::string str(temp.begin(),temp.end());
    //     std::cout<<"\n Length --->"<<temp.size()<<"\n";
    //     Frame f;
    //     f.set_rawbuffer(str);
    //     f.set_channel(frame.channels());
    //     f.set_width(frame.size().width);
    //     f.set_height(frame.size().height);
    //     response->Write(f);
    //     // std::this_thread::sleep_for(
    //     //     std::chrono::milliseconds(500)
    //     // );
    // }
    // ----------------------------- //

    return ::grpc::Status::OK;
}

::grpc::Status SensorSharingImpl::stopStream(
    ::grpc::ServerContext *context,
    const ::Request *request,
    ::Response *response)
{

    std::cout << "executing startstream...\n";
    std::cout
        << "client id : [" << request->clientid() << "]\n"
        << "camera id : [" << request->cameraid() << "]\n";

    cameramap_t &cam_map = clientMap.at(request->clientid());
    SCameraAttr &cam_attr = cam_map[request->cameraid()];
    cam_attr.threadFlag = false;

    // ---- old tested code ---- //
    // std::cout<<"\n  Inside stopStream function\n";
    // /**
    //  * this function must set the client.threadFlag[index] value to false
    //  * which will in turn terminate the while loop in the startStream call
    // */
    // SClient& client = clientMap[request->clientid()];
    // int index = 0;
    // while( index < g_cameraList.size() ) {
    //     if(
    //         client.configuration[index].cameraId == request->cameraid()
    //     ) { break; }
    //     else index++;
    // }
    // client.threadFlag[index] = false;
    // ----------------------------- //
    return ::grpc::Status::OK;
}

::grpc::Status SensorSharingImpl::deregister(
    ::grpc::ServerContext *context,
    const ::Request *request,
    ::Response *response)
{
    std::cout << "executing deregister...\n";
    std::cout
        << "client id : [" << request->clientid() << "]\n"
        << "camera id : [" << request->cameraid() << "]\n";

    cameramap_t &cam_map = clientMap.at(request->clientid());
    auto it = cam_map.begin();
    while (!cam_map.empty())
    {
        it = cam_map.erase(it);
    }
    clientMap.erase(request->clientid());
    std::cout << "after clearing the cam_map...\n";

    // ---- old tested code ---- //
    // std::cout<<"\n  executing deregister...\n";
    // /**
    //  * this function will iterate over all arrays in clientList
    //  * it will first turen off all threadFlags to false
    //  * then will destroy all arrays in SCLient
    // */
    // SClient& client = clientMap[request->clientid()];
    // for(int index = 0; index < g_cameraList.size(); index++) {
    //     client.threadFlag[index] = false;
    // }
    // delete[] client.threadId;
    // delete[] client.threadFlag;
    // delete[] client.configuration;
    // delete[] client.captureDevice;
    // ---------------------------- //

    return ::grpc::Status::OK;
}
