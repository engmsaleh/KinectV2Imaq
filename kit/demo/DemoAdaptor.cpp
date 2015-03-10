/**
 * @file:       DemoAdaptor.cpp
 *
 * Purpose:     Implements DemoAdaptor class methods.
 *
 * $Copyright 2001-2014 The MathWorks, Inc.
 *
 *
 */

#include "mwdemoimaq.h"
#include "DemoAdaptor.h"
#include "DemoPropListener.h"
#include "DemoSourceListener.h"
#include "DemoDeviceFormat.h"
#include "DemoTimestampGetFcn.h"
#include <string>

#include <exception>
#ifndef _WIN32
#include <unistd.h>  /* usleep */
#endif

//******************************************
//  CONSTRUCTOR/DESTRUCTOR
//******************************************
DemoAdaptor::DemoAdaptor(imaqkit::IEngine* engine, const imaqkit::IDeviceInfo* deviceInfo, const char* formatName):
    imaqkit::IAdaptor(engine),
    _di(deviceInfo),
    _sendThread(static_cast<Thread>(NULL)),
    _formatName(formatName),
    _acquisitionActive(false)
{

    // Perform any necessary device initialization and create listeners for device-specific properties.
    initDevice();

    // Create a critical section handle.
    _driverGuard = imaqkit::createCriticalSection();
    _acquisitionActiveGuard = imaqkit::createCriticalSection();
}

// The destructor calls the imaqkit::IAdaptor::close() method, not the
// closeDevice() method. The close() method calls the closeDevice() method.
DemoAdaptor::~DemoAdaptor()
{

    // Stop the device.
    stop();

    // Close the device.
    close();

    // Cleanup - deallocate the critical section handle.
    delete _driverGuard;
}

//  Device Initialization Method
//  Setup property listeners to get notification of changes to their values.
void DemoAdaptor::initDevice()
{

    // Get the engine property container.
    _enginePropContainer = getEngine()->getEnginePropContainer();

    _enginePropContainer->addListener("SelectedSourceName", new DemoSourceListener(this));

    // Get a handle to the property container for device-specific properties
    // associated with the imaqkit::IEngine object.
    imaqkit::IPropContainer* adaptorPropContainer = getEngine()->getAdaptorPropContainer();

    // Determine the number of properties in the container.
    int numDeviceProps = adaptorPropContainer->getNumberProps();

    // Allocate a string array for storing property names.
    const char **devicePropNames = new const char*[numDeviceProps];

    // Get the property names and store them in the string array.
    adaptorPropContainer->getPropNames(devicePropNames);

    // Cycle through each property and add listeners to those that are device
    // specific.
    for (int i = 0; i < numDeviceProps; i++) {

        // Add custom get functions to the timestamp properties.  For the other properties
        // add post-set listeners.
        if ((std::string(demo::TIMESTAMP_STRING_STR) == devicePropNames[i]) ||
            (std::string(demo::TIMESTAMP_INT_STR) == devicePropNames[i])) {
            adaptorPropContainer->setCustomGetFcn(devicePropNames[i], new DemoTimestampGetFcn(this));
        } else {
            // Get the property information object.
            imaqkit::IPropInfo* propInfo = adaptorPropContainer->getIPropInfo(devicePropNames[i]);

            // Check to see whether the property is device-specific. Do not create
            // create property listeners for non device-specific properties such
            // as 'Parent' and 'Tag'.
            if (propInfo->isPropertyDeviceSpecific()) {
                adaptorPropContainer->addListener(devicePropNames[i], new DemoPropListener(this));
            }
        }
    }

    // Clean up the array of property names.
    delete [] devicePropNames;
}

// Return a string identifying the name of the vendor's device driver.
const char* DemoAdaptor::getDriverDescription() const
{
    return demo::DRIVER_DESCRIPTION_STR;
}

// Return a string identifying the version of the vendor's device driver.
const char* DemoAdaptor::getDriverVersion() const
{
    return demo::DRIVER_VERSION_STR;
}

// Return the width of the frame, in pixels, as defined by the video format specified.
int DemoAdaptor::getMaxWidth() const
{

    // Get the format information object.
    DemoDeviceFormat* formatInfo = getFormatInfo();

    if (formatInfo) {
        // Return the image width information stored in the DemoDeviceFormat object.
        return formatInfo->getFormatWidth();
    } else {
        // If no format information is found because the device is configured to
        // use the camera file, query the SDK to determine the image width.
        // Since no SDK is used in this demo, it just returns a made-up
        // number.
        return demo::DEMO_DEFAULT_WIDTH;
    }
}

// Return the height of the frame, in pixels, as defined by the video format specified.
int DemoAdaptor::getMaxHeight() const
{

    // Get the format information object.
    DemoDeviceFormat* formatInfo = getFormatInfo();

    if (formatInfo) {
        // Return the image height information stored in the DemoDeviceFormat object.
        return formatInfo->getFormatHeight();
    } else {
        // If no format information is found because the device is configured to
        // use the camera file, query the SDK to determine the image height.
        // Since no SDK is used in this demo, it just returns a made-up
        // number.
        return demo::DEMO_DEFAULT_HEIGHT;
    }
}

imaqkit::frametypes::FRAMETYPE DemoAdaptor::getFrameType() const
{

    // Get the format information object.
    DemoDeviceFormat* formatInfo = getFormatInfo();

    if (formatInfo) {
        // Return the frame type stored in the DemoDeviceFormat object.
        return formatInfo->getFormatFrameType();
    } else {
        // If no format information is found because the device is configured to
        // use the camera file, query the SDK to determine the image frame type.
        // Since no SDK is used in this demo, it just returns a common frame
        // type.
        return imaqkit::frametypes::RGB24_PACKED;
    }
}

bool DemoAdaptor::isAcquisitionActive(void) const
{
    std::auto_ptr<imaqkit::IAutoCriticalSection> acquisitionActiveSection(imaqkit::createAutoCriticalSection(_acquisitionActiveGuard, true));
    return _acquisitionActive;
}

void DemoAdaptor::setAcquisitionActive(bool state)
{
    std::auto_ptr<imaqkit::IAutoCriticalSection> acquisitionActiveSection(imaqkit::createAutoCriticalSection(_acquisitionActiveGuard, true));
    _acquisitionActive = state;
}

// Return the number of bands of data returned: RGB is 3, monochrome is 1.
int DemoAdaptor::getNumberOfBands() const
{

    // Get the format information object.
    DemoDeviceFormat* formatInfo = getFormatInfo();

    if (formatInfo) {
        // Return the number of color bands stored in the DemoDeviceFormat object.
        return formatInfo->getFormatNumBands();
    } else {
        // If no format information is found because the device is configured to
        // use the camera file, query the SDK to determine the image width.
        // Since no SDK is used in this demo, it just returns a made-up
        // number.
        return demo::DEMO_DEFAULT_NUMBER_OF_BANDS;
    }
}

// Set up the device for acquisition.
bool DemoAdaptor::openDevice()
{

    // Check if the device is already opened.
    // If it is, then nothing else needs to be done.
    if (isOpen())
        return true;

#ifdef _WIN32
    // Create a thread for capturing images from the image acquisition
    // device and sending those images back to the IMAQ engine.
    _sendThread = CreateThread(NULL, 0, sendThread, this, 0, &_sendThreadID);

    // Check that the thread was successfully created.
    if (_sendThread == NULL) {
        return false;
    }

    // Post a "dummy" message to ensure that the thread has been created.
    // PostThreadMessage returns 0 if it fails to successfully post a message.
    // If it fails, the thread probably hasn't been created yet, so
    // keep trying until the message is successfully posted.
    while (PostThreadMessage(_sendThreadID, WM_USER + 1, 0, 0) == 0) {
        Sleep(1);
    }
#else
    // do nothing for non Windows
#endif

    return true;
}

//  Engine calls this method to start an acquisition.
bool DemoAdaptor::startCapture()
{

    // Check if the device is opened.
    // Acquisition is not possible if the device is not already opened.
    if (! isOpen())
        return false;

    // ************************************************
    // * CONFIGURE THE IMAGE ACQUISITION DEVICE PROPERTIES.
    // Add code here to call into the image acquisition device's SDK
    // to configure the device settings (ie. video format, frame rate, et cetera).
    // ************************************************

    // Configure device-specific properties by calling notifyAllListeners()
    // to invoke all property listener objects. The property listeners
    // notify() method is responsible for configuring the image acquisition
    // device properties.
    getEngine()->getAdaptorPropContainer()->notifyAllListeners();

    // ************************************************
    // * IF NECESSARY, TURN ON THE IMAGE ACQUISITION DEVICE FOR ACQUISITION
    // Add code here to initialize device to start getting data or initialize
    // acquisition.
    // ************************************************

    // Set the acquiring frames flag.
    setAcquisitionActive(true);

#ifdef _WIN32
    // Post message to sendThread() to tell it to begin capturing images and sending
    // those images back to the IMAQ engine.
    PostThreadMessage(_sendThreadID, WM_USER, 0, 0);
    return true;
#else
    int errcode = pthread_create(&_sendThread, NULL, this->sendThread, this);
    return (errcode == 0);
#endif

}


// The startCapture() method posts a message to this ThreadProc to see if
// the acquisition is complete. This method calls the
// imaqkit::IAdaptor::isAcquisitionNotComplete method to see if the requested
// number of frames have been acquired.
ThreadReturnType CALLING_CONVENTION DemoAdaptor::sendThread(void* param)
{

    DemoAdaptor* adaptor = reinterpret_cast<DemoAdaptor*>(param);

#ifdef _WIN32
    // Set the thread priority.
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // If message is not WM_QUIT, then it is a non-zero value.
    // Continue the while loop until a WM_QUIT message is received.
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {

        switch (msg.message) {
          case WM_USER:
            sendFrame(adaptor);
            break;
        }//switch-case WM_USER

    }//while message is not WM_QUIT
    return 0;
#else
    while (adaptor->isAcquisitionActive()) {
        sendFrame(adaptor);
    }

    return NULL;
#endif
}

void DemoAdaptor::sendFrame(DemoAdaptor* adaptor)
{

    std::auto_ptr<imaqkit::IAutoCriticalSection> driverSection(imaqkit::createAutoCriticalSection(adaptor->_driverGuard, false));

    // Initialize the offset for the image data generated by this
    // demo adaptor to 0. Increasing the offset makes the image
    // stream from right to left.
    int offset = 0;

    // Since the demo adaptor generates images inside the acquisition
    // while loop below, save the image format information
    // here to make it more efficient.
    int imageWidth = adaptor->getMaxWidth();
    int imageHeight = adaptor->getMaxHeight();
    int imageBands = adaptor->getNumberOfBands();

    while (adaptor->isAcquisitionNotComplete() && adaptor->isAcquisitionActive()) {
        driverSection->enter();

        // **************************************************************
        // * IF NECESSARY, CONFIGURE THE HARDWARE TRIGGER.
        // If the adaptor supports external triggering, add the
        // following code to check the trigger mode requested by the
        // user.

        // Check if the trigger mode is set to 'hardware'.
        if (adaptor->useHardwareTrigger()) {
            // Add code here to configure the image acquisition
            // device for hardware triggering.
        }
        // **************************************************************

        // **************************************************************
        // * GRAB IMAGE DATA FROM THE IMAGE ACQUISITION DEVICE
        // Add code here to grab a frame from the image
        // acquisition device.
        //
        // Normally the adaptor queries the SDK to return image
        // data from the imaging device. However, since this demo
        // adaptor only simulates what an adaptor would normally do
        // and no imaging device is used, it has to generate
        // the image data.
        // The code to generate image data is demo adaptor specific
        // and shouldn't used by your adaptor. Instead, adaptors
        // should be able to query their SDK for image data.

        // Create a buffer for storing the frame.
        size_t bufferSize = imageWidth * imageHeight * imageBands;
        unsigned char* imBuffer = NULL;
        try {
            imBuffer = new unsigned char[bufferSize];
        } catch (const std::bad_alloc&) {
            imaqkit::adaptorError(adaptor, "imaq:demo:badFrameAlloc", "Unable to allocate memory for frame.");
            // Because we are not on the MATLAB thread, we need to return to avoid continuing further.
            return;
        }

        size_t reference = 0;
        if (imageBands == 1) {
            // Generate a random image data in place of actual "grabbing" a frame.
            for (int height = 0; height < imageHeight; height++) {
                for (int width = 0; width < imageWidth; width++) {
                    imBuffer[reference++] = (width + offset) % 255;
                }
            }
        } else {
            for (int height = 0; height < imageHeight; height++) {
                for (int width = 0; width < imageWidth; width++) {
                    imBuffer[reference++] = (width - offset) % 255;
                    imBuffer[reference++] = (height - offset) % 255;
                    imBuffer[reference++] = (width + height - offset) % 255;
                }
            }
        }

        offset += demo::IMAGE_DATA_OFFSET;

        // Delay each frame for about 30 milliseconds.
        // Normally the adaptor waits for an image to be acquired
        // by the camera and the delay between images is dependent
        // on the camera's frame rate. However, since this demo
        // adaptor generates image data to simulate what an
        // adaptor would normally do, it uses a small pause
        // after each frame to make the frame rate look realistic.
        // Without this pause, the frame rate would look
        // abnormally high.
        // This pause is demo adaptor specific and doesn't indicate
        // that it should necessarily be used for your adaptor.
#ifdef _WIN32
        Sleep(demo::IMAGE_FRAME_PAUSE_TIME);
#else
        usleep(demo::IMAGE_FRAME_PAUSE_TIME * 1000);
#endif

        // **************************************************************

        // Check if the adaptor needs to send the frame back to the IMAQ engine.
        if (adaptor->isSendFrame()) {

            // Get the region of interest information.
            int roiOriginX, roiOriginY, roiWidth, roiHeight;
            adaptor->getROI(roiOriginX, roiOriginY, roiWidth, roiHeight);

            // Determine the frame type.
            imaqkit::frametypes::FRAMETYPE frameType = adaptor->getFrameType();

            // Create an imaqkit::IAdaptorFrame object for storing the image data.
            imaqkit::IAdaptorFrame* frame = adaptor->getEngine()->makeFrame(frameType,  //frametype
                                                                            roiWidth,  //width
                                                                            roiHeight);  //height

            // Put the image data and format information into the IAdaptorFrame object.
            frame->setImage(imBuffer, imageWidth, imageHeight, roiOriginX, roiOriginY);
            //frame->setImage(imBuffer, roiWidth, roiHeight, 0, 0);

            // Set the image's timestamp to be the current time.
            frame->setTime(imaqkit::getCurrentTime());

            // Send the IAdaptorFrame object back to the IMAQ engine.
            adaptor->getEngine()->receiveFrame(frame);
        }// if isSendFrame()

        // Increment the frame count.
        adaptor->incrementFrameCount();

        // Cleanup. Deallocate imBuffer.
        delete [] imBuffer;
        driverSection->leave();
    }//while(isAcquisitionNotComplete() && adaptor->isAcquisitionActive())

}

//  Engine calls this method to stop an acquisition.
bool DemoAdaptor::stopCapture()
{

    // Check if the device is acquiring data.
    // If the device is not acquiring data then nothing else needs to be done.
    if (!isAcquiring())
        return true;

    // Set the acquire frame flag to false to stop the while loop in sendThread().
    setAcquisitionActive(false);

#ifndef _WIN32
    void* status;
    int errcode = pthread_join(_sendThread, &status);
#endif

    // Enter the critical section to ensure that you exit the sendThread()'s
    // while loop before continuing.
    std::auto_ptr<imaqkit::IAutoCriticalSection> driverSection(imaqkit::createAutoCriticalSection(_driverGuard, true));

    // *********************************************************************
    // * IF NECESSARY, STOP THE DEVICE FROM ACQUIRING DATA.
    // *********************************************************************
    // Add code here to stop the image acquisition device from acquiring data.
    // *********************************************************************

    // Leave the critical section.
    driverSection->leave();

    return true;
}

// Terminate the threads used for acquisition
bool DemoAdaptor::closeDevice()
{

    // Check if the device is opened.
    // If it is not opened, then nothing more needs to be done.
    if (!isOpen())
        return true;

#ifdef _WIN32
    // Terminate and close image the send thread.
    if (_sendThread) {
        // Post an WM_QUIT message to sendThread() thread.
        PostThreadMessage(_sendThreadID, WM_QUIT, 0, 0);

        // Give the thread a chance to finish.
        WaitForSingleObject(_sendThread, demo::SINGLE_OBJECT_WAIT_TIME);

        // Close sendThread() thread handle.
        CloseHandle(_sendThread);
        _sendThread = NULL;
    }
#else
#endif

    return true;
}

// Utility function used to get the device format object.
DemoDeviceFormat* DemoAdaptor::getFormatInfo() const
{

    // First get the specified format's imaqkit::IDeviceFormat object from the
    // imaqkit::IDeviceInfo object, using the getDeviceFormat() method.
    imaqkit::IDeviceFormat* selectedFormat = _di->getDeviceFormat(_formatName);

    // Return the specified format's DemoDeviceFormat object. This object
    // is stored in the imaqkit::IDeviceFormat object. Use the getAdaptorData()
    // method of the imaqkit::IDeviceFormat object.
    // If the user specified a camera file,  no format has been saved.
    if (selectedFormat) {
        return dynamic_cast<DemoDeviceFormat*>(selectedFormat->getAdaptorData());
    } else {
        return NULL;
    }
}
