#pragma once

#include <BaseTypes.hpp>
#include <CameraList.hpp>

/**
 * @brief : As soon as the client app opens up an implicit call to Register will occur
 * @note [ acceptance criteria ]
 * 1. must return a unique client ID
 * 2. must return the CameraList to user
*/
SRegisterInfo Register();

/**
 * @brief : on call from user it will receive a configuration array as second argument
 *          and will set the conf array created for this client on server with the values passed
 * @note [ acceptance criteria ]
 * 1. must find the SClient instance based on client ID
 * 2. must set all fields from _sconf array to server local array 
*/
void setConfiguration(clientid_t _clientId, SConfiguration* _sconf);

/**
 * @brief : it will request default configurations from the server for all the available cameras.​
 * @note [ acceptance criteria ]
 * 1. find the instance of SClient using the client ID
 * 2. return the array of SConfiguration
*/
SConfiguration* getConfiguration(clientid_t _clientId);

/**
 * @brief : It will stop the camera by releasing all resources at server or it will start the camera by acquiring resources
 * @note [ acceptance criteria ]
 * 1. must find the SClient instance using the client ID
 * 2. then must find the SConfiguration instance using the camera ID
 * 3. then toggle the current camera state
*/
void toggleCameraState(clientid_t _clientId,int _cameraId);

/**
 * @brief : When the user clicks on the refresh button to take image then
 *          this function will get called and will return the image as a matrix.​
 * @note [ acceptance criteria ]
 * 1. find the SClient instance using client ID
 * 2. find the SConfiguration for given camera ID
 * 3. find the VideoCapture instance using the index for already found SConfiguration instance
 * 4. attempt to capture a frame
 * 5. return the frame in raw array format or if needed in a custom struct that may encapsulate array of bytes, height, width & pixel size
*/
cv::Mat captureImage(clientid_t _clientId,int _cameraId);

/**
 * @brief : This function will get called once the user selects the start stream button.
 *          Internally it will request to resume a thread loop at server side that will
 *          repeatedly send frames at specific intervals to the client.​
 * @note [ acceptance criteria ]
 * 1. find the client instance using client ID and VideoCapture instance using camera ID
 * 2. if no associated stream thread is available then create one and make an entru in threadID array
 * 3. also set the status flag to 'start'
*/
cv::Mat startStream(clientid_t _clientId,int _cameraId);

/**
 * @brief : This function will get called once the user selects the stop stream button.
 *          Internally it will stop the thread loop at the server side that repeatedly sends frames.​
 * @note [ acceptance criteria ]
 * 1. find the client instance using the client ID and thread ID using the camera ID
 * 2. set the thread flag to stop to pause the stream thread
*/
void stopStream(clientid_t _clientId,int _cameraId);

/**
 * @brief : This function will get called once the user close the application.
 *          Internally it will stop and clean all the windows.
 *          This RPC will release all resources as server side that were acquired 
 *          to use the cameras, for e.g, all threads will be killed and all 'VideoCapture' devices will be destroyed
 * @note [ acceptance criteria ]
 * 1. find the client instance using the client ID
 * 2. then Destroy the SConfiguration array
 * 3. and toggle all thread flags to stop
 * 4. using all thread IDs kill all threads
 * 5. destroy the VideoCapture array
*/
void deregister(clientid_t _clientId);
