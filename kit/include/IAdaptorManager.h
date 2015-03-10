/**
 * @file:       IAdaptorManager.h
 *
 * Purpose:     Internal engine interface for accessing imaqkit::IAdaptor.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2005 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IADAPTORMANAGER__HEADER__
#define __IMAQADAPTOR__IADAPTORMANAGER__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{
    class IEngine;

    /**
     * Class IAdaptorManger
     *
     * @brief:  Interface abstracting functionality used to operate
     *          imaqkit::IAdaptor.
     *
     *          This class is not intended to be directly used by adaptors.
     *
     */
    class IAdaptorManager : public IMAQInterface
    {

      public:
        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        IAdaptorManager(void) {};
        virtual ~IAdaptorManager(void) {};

        // *******************************************************************
        // ACQUISITION CONTROL.
        // *******************************************************************
        /**
         * Open the device connection for exclusive use.
         *
         */
        virtual void open(void) = 0;

        /**
         * Close the device connection.
         *
         */
        virtual void close(void) = 0;

        /**
         * Restart the acquisition device using the last acquisition settings.
         *
         * @return bool: True if the device was successfully started.
         *
         */
        virtual bool restart(void) = 0;

        /**
         * Stop the acquisition of images.
         *
         * @return bool: True if the device was successfully stopped.
         *
         */
        virtual bool stop(void) = 0;

        // *******************************************************************
        // STATUS INFORMATION.
        // *******************************************************************
        /**
         * Check if the device is currently open.
         *
         * This method will not return true until imaqkit::IAdaptor::openDevice
         * returns successfully.
         *
         * @return bool: True if the adaptor is an open state.
         *
         */
        virtual bool isOpen(void) const = 0;

        /**
         * Check if the device is currently acquiring data.
         *
         * This method will not return true until imaqkit::IAdaptor::startCapture
         * returns successfully.
         *
         * @return bool: True if the adaptor is currently acquiring images.
         *
         */
        virtual bool isAcquiring(void) const = 0;

        /**
         * Determines if the user has requested hardware triggers when
         * acquiring a trigger's worth of data.
         *
         * @return bool : True if hardware triggers are to be used.
         */
        virtual bool isHardwareTriggerMode(void) const = 0;

        /**
         * Request the handle to the image acquisition engine interface.
         *
         * @return imaqkit::IEngine*: interface to the image acquisition engine.
         */
        virtual imaqkit::IEngine* getEngine(void) const = 0;

        /**
         * Returns the total number of frames to acquire per trigger.
         *
         * @return int : Total nmber of frames per trigger.
         */
        virtual int getTotalFramesPerTrigger(void) const = 0;

        /**
         * Returns the current frame count indicating the number
         * frames sent to the imaqkit::IEngine.
         *
         * @return int : Current number of frames provided to imaqkit::IEngine.
         */
        virtual int getFrameCount(void) const = 0;

        // *******************************************************************
        // ACQUISITION CHARACTERISTICS.
        // *******************************************************************
        /**
         * Get the current ROI parameters.  The default implementation
         * returns the full image size as ROI.
         *
         * @param originX: The x-coordinate of the ROI origin
         * @param originY: The y-coordinate of the ROI origin
         * @param width: The width of the rectanglar ROI
         * @param height: The height of the rectanglar ROI
         */
        virtual void getROI(int& originX, int& originY, int& width, int& height) = 0;

        /**
         * Set the current ROI parameters.
         *
         * @param originX: The x-coordinate of the ROI origin
         * @param originY: The y-coordinate of the ROI origin
         * @param width: The width of the rectanglar ROI
         * @param height: The height of the rectanglar ROI
         */
        virtual void setROI(const int originX, const int originY, const int width, const int height) = 0;

        // *******************************************************************
        // UTILITY METHODS.
        //    The following methods are used to subset images according
        //    to the user requested frame grab interval and frame delay.
        // *******************************************************************
        /**
         * Increments the frame count. This method should be invoked when
         * a frame is acquired from the device.
         */
        virtual void incrementFrameCount(void) = 0;

        /**
         * Checks to see if next frame acquired is to be sent to the
         * imaqkit::IEngine. This method subsets the acquired frames
         * properly given the frame grab interval and frame delay.
         *
         * @return bool: True if the frame should be sent to the engine.
         *
         */
        virtual bool isSendFrame(void) const = 0;

        /**
         * If true, indicates that another frame needs to be acquired.
         *
         * @return bool: True if more frames need to be acquired.
         */
        virtual bool isAcquisitionNotComplete(void) const = 0;

        /**
         * If true, signifies the next frame needs to wait for a
         * hardware trigger event to be received.
         *
         * @return bool: True if the next frame should wait for a hardware event.
         *
         */
        virtual bool useHardwareTrigger(void) const = 0;
    };
}

#endif
