/**
 * @file:       IAdaptor.h
 *
 * Purpose:     Parent class for all Image Acquisition Toolbox adaptors.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2005 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IADAPTOR__HEADER__
#define __IMAQADAPTOR__IADAPTOR__HEADER__

#include <memory>
#include <limits.h>
#include "IAdaptorFrame.h"
#include "IMAQInterface.h"
#include "imaqfcnexports.h"
#include "IAdaptorManager.h"

namespace imaqkit
{
    /// Forward declare.
    class IEngine;

    /**
     * Class IAdaptor
     *
     * @brief:  Parent class for all Image Acquisition Toolbox adaptors.
     *
     *          Defines the communciation interface between an adaptor
     *          and the imaqkit::IEngine for the purposes of controling an
     *          acquisition, configuring settings, and accessing general
     *          driver information.
     *
     *          Each imaqkit::IAdaptor instance is associated with a specific
     *          video format or device file (i.e. camera file) specified by
     *          the user.
     *
     */
    class IAdaptor : public imaqkit::IMAQInterface
    {

      public:
        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        /**
         * Interface used by the image acquisition engine (imaqkit::IEngine)
         * for accessing and controlling an adaptor.
         *
         * @param engine: Handle to the image acquisition engine.
         */
        IAdaptor(imaqkit::IEngine* engine)
        {
            _adaptorManager = imaqkit::createAdaptorManager(this, engine);
        };

        /**
         * Destructor for the adaptor object.
         *
         * Note, in order for the destructors to be called on the derived
         * classes, all destructors must be defined as virtual.
         *
         */
        virtual ~IAdaptor(void)
        {
            delete _adaptorManager;
        }

        // *******************************************************************
        // ACQUISITION CONTROL.
        // *******************************************************************
        /**
         * Open the device connection for exclusive use.
         *
         */
        inline void open(void)
        {
            _adaptorManager->open();
        };

        /**
         * Close the device connection.
         *
         */
        inline void close(void)
        {
            _adaptorManager->close();
        };

        /**
         * Restart the acquisition device using the last acquisition settings.
         *
         * @return bool: True if the device was successfully started.
         *
         */
        inline bool restart(void)
        {
            return _adaptorManager->restart();
        }

        /**
         * Stop the acquisition of images.
         *
         * @return bool: True if the device was successfully stopped.
         *
         */
        inline bool stop(void)
        {
            return _adaptorManager->stop();
        };

        // *******************************************************************
        // STATUS INFORMATION.
        // *******************************************************************
        /**
         * Check if the device is currently open.
         *
         * This function will not return true until imaqkit::IAdaptor::openDevice()
         * returns successfully.
         *
         * @return bool: True if the adaptor is an open state.
         *
         */
        inline bool isOpen(void) const
        {
            return _adaptorManager->isOpen();
        };

        /**
         * Check if the device is currently acquiring data.
         *
         * This function will not return true until imaqkit::IAdaptor::startCapture()
         * returns successfully.
         *
         * @return bool: True if the adaptor is currently acquiring images.
         *
         */
        inline bool isAcquiring(void) const
        {
            return _adaptorManager->isAcquiring();
        };

        /**
         * Determine if the user has configured the acquisition to use
         * hardware triggers.
         *
         * True indicates external hardware triggers are to be used when acquiring data.
         *
         * False indicates non-hardware triggers are being used.
         *
         * @return bool : True if hardware triggers are to be used.
         */
        inline bool isHardwareTriggerMode(void) const
        {
            return _adaptorManager->isHardwareTriggerMode();
        };

        /**
         * Request the handle to the image acquisition engine interface.
         *
         * @return imaqkit::IEngine*: Interface to the image acquisition engine.
         */
        inline imaqkit::IEngine* getEngine(void) const
        {
            return _adaptorManager->getEngine();
        }

        /**
         * Return the total number of frames to acquire per trigger.
         *
         * @return int : Total number of frames per trigger.
         */
        virtual inline int getTotalFramesPerTrigger(void) const
        {
            return _adaptorManager->getTotalFramesPerTrigger();
        };

        /**
         * Return the current frame count indicating the number of
         * frames sent to imaqkit::IEngine.
         *
         * @return int : The current number of frames provided to imaqkit::IEngine.
         */
        inline int getFrameCount(void) const
        {
            return _adaptorManager->getFrameCount();
        };

        // *******************************************************************
        // ACQUISITION CHARACTERISTICS.
        // *******************************************************************
        /**
         * Return the current region-of-interest (ROI) settings.
         *
         * ROI consists of a rectangular area with an x and y offset, and
         * a width and height.
         *
         * This method can be overloaded by an adaptor in order to manually handle
         * ROI configurations, either to leverage hardware ROI support, or apply
         * scaling values to the ROI.
         *
         * Note, if imaqkit::IAdaptor::getROI is overloaded, imaqkit::IAdaptor::setROI
         * must also be overloaded.
         *
         * By default, if imaqkit::IAdaptor::getROI is not overloaded, ROI configurations
         * will be handled in software by imaqkit::IEngine.
         *
         * @param originX: The x-coordinate of the ROI origin.
         * @param originY: The y-coordinate of the ROI origin.
         * @param width: The width of the rectangular ROI.
         * @param height: The height of the rectangular ROI.
         */
        virtual void getROI(int& originX, int& originY, int& width, int& height) const
        {
            _adaptorManager->getROI(originX, originY, width, height);
        };

        /**
         * Configure the region-of-interest (ROI) settings.
         *
         * ROI consists of a rectangular area with an x and y offset, and
         * a width and height.
         *
         * This method can be overloaded by an adaptor in order to manually handle
         * ROI configurations, either to leverage hardware ROI support, or apply
         * scaling values to the ROI.
         *
         * Note, if imaqkit::IAdaptor::setROI is overloaded, imaqkit::IAdaptor::getROI
         * must also be overloaded.
         *
         * By default, the ROI will be configured to the full image resolution.
         *
         * @param originX: The x-coordinate of the ROI origin.
         * @param originY: The y-coordinate of the ROI origin.
         * @param width: The width of the rectangular ROI.
         * @param height: The height of the rectangular ROI.
         */
        virtual void setROI(const int originX, const int originY, const int width, const int height)
        {
            _adaptorManager->setROI(originX, originY, width, height);
        };

        /**
         * Return the current maximum width for an acquired image.
         *
         * The value returned should reflect the maximum width of the
         * hardware image buffer provided to the adaptor, factoring in
         * any pertinent parameters such as hardware scaling
         * factors.
         *
         * Note, if necessary, 0 can be returned if the device is not
         * in an open or acquiring state.
         *
         * @return int: The number of pixels in each line of an acquired image.
         */
        virtual int getMaxWidth(void) const = 0;

        /**
         * Return the current maximum height for an acquired image.
         *
         * The value returned should reflect the maximum height of the
         * hardware image buffer provided to the adaptor, factoring in
         * any pertinent parameters such as hardware scaling
         * factors.
         *
         * Note, if necessary, 0 can be returned if the device is not
         * in an open or acquiring state.
         *
         * @return int: The number of pixels in each line of an acquired image.
         */
        virtual int getMaxHeight(void) const = 0;

        /**
         * Return the current image frame type.
         *
         * The available imaqkit::frametypes::FRAMETYPE values are defined
         * in imaqkit::IAdaptorFrame.
         *
         * @return imaqkit::frametypes::FRAMETYPE: The frame type for images to be acquired.
         */
        virtual imaqkit::frametypes::FRAMETYPE getFrameType(void) const = 0;

        /**
         * Return the number of color bands that will be acquired.
         *
         * @return int : Number of color bands.
         */
        virtual int getNumberOfBands(void) const = 0;

        // *******************************************************************
        // ADAPTOR INFORMATION.
        // *******************************************************************
        /**
         * Return a string identifying the device driver being used.
         *
         * @return const char*: Vendor's driver description.
         */
        virtual const char* getDriverDescription(void) const = 0;

        /**
         * Return a string providing the version number of the device driver
         * being used.
         *
         * @return const char*: Vendor's driver version.
         */
        virtual const char* getDriverVersion(void) const = 0;

        // *******************************************************************
        // ADAPTOR IMPLEMENTATION ACQUISITION CONTROL.
        // *******************************************************************
        /**
         * Open the device and prepare it for acquisition.
         *
         * The adaptor does not start any acquisition until imaqkit::IAdaptor::startCapture()
         * is called.
         *
         * @return bool: True if the adaptor returns in an open state, false otherwise.
         */
        virtual bool openDevice(void) = 0;

        /**
         * Close the device and halt the acquisition. The implementation should
         * perform the following steps:
         *
         * <ul>
         * <li>Stop streaming images to imaqkit::IEngine.</li>
         * <li>Disconnect from the hardware, if practical.</li>
         * <li>Return in a closed state.</li>
         * </ul>
         *
         * @return bool: True if the adaptor returns in a closed state, false otherwise.
         */
        virtual bool closeDevice(void) = 0;

        /**
         * Start acquiring the number of images requested, sending each
         * frame to imaqkit::IEngine.
         *
         * Use imaqkit::IAdaptor::isAcquisitionNotComplete() to determine
         * when to stop the acquisition.
         *
         * The implementation should perform the following steps:
         *
         * <ul>
         * <li>Ignore the start request if the device is not open.</li>
         * <li>If imaqkit::IAdaptor::useHardwareTrigger returns true, wait for
         *     the hardware trigger condition to be met.</li>
         * <li>Send the first available frame, followed by every Nth frame.</li>
         * </ul>
         *
         * Use imaqkit::IAdaptor::incrementFrameCount() and imaqkit::IAdaptor::isSendFrame()
         * to determine if the current frame should be sent to the imaqkit::IEngine. Doing
         * so will enable support for the FrameGrabInterval setting requested by the user.
         *
         * @return bool: True if the adaptor returns in a started state, false otherwise.
         */
        virtual bool startCapture(void) = 0;

        /**
         * Stop the current image acquisition in process.
         *
         * The implementation should perform the following steps:
         *
         * <ul>
         * <li>Ignore the stop request if the device is not open or not acquiring.</li>
         * <li>Maintain a connection with the hardware, if practical.</li>
         * </ul>
         *
         * @return bool: True if the adaptor returns in a stopped state, false otherwise.
         */
        virtual bool stopCapture(void) = 0;

        // *******************************************************************
        // UTILITY METHODS.
        //    The following methods are used to subset images according
        //    to the user requested frame grab interval and frame delay.
        // *******************************************************************
        /**
         * Increment the frame count.
         *
         * This function must be invoked whenever a frame is provided by the device,
         * regardless if the frame is to be sent to the imaqkit::IEngine.
         *
         */
        inline void incrementFrameCount(void)
        {
            _adaptorManager->incrementFrameCount();
        };

        /**
         * Return true if the next frame provided by the device should be sent
         * to the imaqkit::IEngine. This method ensures the user requested frame
         * grab interval and frame delay settings are taken into account for the
         * adaptor.
         *
         * @return bool: True if the frame should be sent to the engine.
         */
        inline bool isSendFrame(void) const
        {
            return _adaptorManager->isSendFrame();
        };

        /**
         * Return true if another frame needs to be acquired.
         *
         * @return bool: True if more frames need to be acquired.
         */
        inline bool isAcquisitionNotComplete(void) const
        {
            return _adaptorManager->isAcquisitionNotComplete();
        };

        /**
         * Returns true if the adaptor needs to wait for a hardware
         * trigger condition to be met before acquiring any additional frames.
         *
         * @return bool: True if the adaptor needs to wait for a hardware trigger event.
         *
         */
        inline bool useHardwareTrigger(void) const
        {
            return _adaptorManager->useHardwareTrigger();
        };

      private:
        /**
         * Disable the default constructor. Anyone implementing
         * imaqkit::IAdaptor must provide an imaqkit::IEngine handle
         * to the constructor.
         *
         * The image acquisition engine handle is available
         * using imaqkit::IAdaptor::getEngine().
         *
         */
        IAdaptor(void);

        /// Internal adaptor manager interface.
        imaqkit::IAdaptorManager* _adaptorManager;
    };
}

#endif
