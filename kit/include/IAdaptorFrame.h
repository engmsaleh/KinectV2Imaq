/**
 * @file:       IAdaptorFrame.h
 *
 * Purpose:     Interface for Image Acquisition Toolbox frames.
 *
 * $Authors:    Dave T., Chris P. $
 *
 * Copyright 2004-2013 The MathWorks, Inc. 
 *
 */

#ifndef __IMAQADAPTOR__IADAPTORFRAME__HEADER__
#define __IMAQADAPTOR__IADAPTORFRAME__HEADER__

#include <stddef.h>
#include "AdaptorFrameTypes.h"

namespace imaqkit
{

    /**
     * class IAdaptorFrame
     *
     * @brief:  Image frame interface.
     *
     * This class provides the interface for the frames that are used to
     * transfer data from an imaqkit::IAdaptor instance to the imaqkit::IEngine.
     *
     * IEngine::makeFrame() returns a pointer to an object of this type and
     * IEngine::receiveFrame() expects frames to be of this type.
     *
     * The most commonly used member functions of this class are
     * imaqkit::IAdaptorFrame::setImage() and imaqkit::IAdaptorFrame::setTime().
     * At a minimum, these functions must be called before sending a frame to
     * the imaqkit::IEngine.
     *
     */
    class IAdaptorFrame
    {

      public:
        // **********************************
        // IMAGE DATA MANAGEMENT
        // **********************************
        /**
         * Copy a rectangular region from the image frame acquired
         * from the device into a buffer in the IAdaptorFrame object.
         *
         * The image dimensions specified must describe the image frame
         * acquired from the device, taking into consideration how the
         * ROI extraction is performed. For example:
         *
         * If ROI is being handled by the hardware, then the image
         * frame acquired from the device is usually the desired
         * ROI already. In this case, the dimensions that must be
         * specified should be an XY origin of [0 0], and the full
         * width and height of the image frame acquired from the
         * device, i.e. the ROI width and height extracted by the
         * hardware.
         *
         * If ROI is being handled by the toolbox engine, then the image
         * frame acquired from the device will usually be the full
         * image resolution. In this case, the dimensions that must
         * be specified should be the desired ROI XY offsets, and the
         * width and height of the image frame acquired, i.e. the full image
         * frame size provided by the hardware. This will allow the toolbox
         * engine to extract the desired ROI from the image frame acquired
         * from the device.
         *
         * @param image: Image frame to copy into frame object.
         * @param srcWidth: Image frame's width.
         * @param srcHeight: Image frame's height.
         * @param originX: Left-most position from which to copy.
         * @param originY: Top-most position from which to copy.
         *
         */
        virtual void setImage(void* image, int srcWidth, int srcHeight, int originX, int originY) = 0;

        /**
         * Return a pointer to the image frame stored in the IAdaptorFrame object.
         *
         * @return void*: Pointer to the image frame stored in the frame object.
         *
         */
        virtual void* getImage(void) const = 0;

        /**
         * Return the dimensions of image frame.
         *
         * @return int*: Three-element array containing width, height, and number of bands.
         *
         */
        virtual int* getDims(void) const = 0;

        /**
         * Return size of image frame stored in IAdaptorFrame object.
         *
         * @return size_t: Number of bytes in image.
         */
        virtual size_t getImageSize(void) const = 0;

        /**
         * Return type of image frame. Identifies the internal
         * format used to store the image frame in the IAdaptorFrame
         * object.
         *
         * @return frametypes::FRAMETYPE: Frame type enumeration value.
         *
         */
        virtual frametypes::FRAMETYPE getFrameType(void) const = 0;

        /**
         * Return the image frame's native color space.
         *
         * @return colorspaces::COLORSPACE: Frame object's native colorspace.
         *
         */
        virtual colorspaces::COLORSPACE getColorSpace(void) const = 0;

        // **********************************
        // TIMESTAMP MANAGEMENT
        // **********************************
        /**
         * Configure the timestamp for the frame object.
         *
         * The time is specified in seconds past midnight, January 1, 1970.
         *
         * @param timestamp: The time the image frame was acquired.
         */
        virtual void setTime(double timestamp) = 0;

        /**
         * Return the time the image frame was acquired.
         *
         * The time is returned in seconds past midnight, January 1, 1970.
         *
         * @return double: The time the image frame was acquired.
         */
        virtual double getTime() const = 0;

        // **********************************
        // METADATA ITEM MANAGEMENT
        // **********************************
        /**
         * Return the names of all the metadata items associated
         * with this image frame.
         *
         * @param names: Variable to store the metadata item names.
         */
        virtual void getMetaNames(const char** names) const = 0 ;

        /**
         * Return the total number of metadata items associated
         * with this image frame.
         *
         * @return int: Total number of metadata items.
         */
        virtual int getNumMetaItems(void) const = 0;

        /**
         * Associate a double scalar metadata item with this image frame.
         *
         * @param name: Name of the metadata item.
         * @param item: New metadata item value to insert.
         */
        virtual void addMetaItem(const char* name, double item) = 0;

        /**
         * Associate a text string metadata item with this image frame.
         *
         * @param name: Name of the metadata item.
         * @param item: New metadata item value to insert.
         */
        virtual void addMetaItem(const char* name, const char* item) = 0;

        /**
         * Associate a double time value metadata item with this image frame.
         *
         * @param name: Name of the metadata item.
         * @param item: New metadata item value to insert.
         */
        virtual void addMetaItemTimeVector(const char* name, double item) = 0;

        /**
         * Associate a double Array metadata item with this image frame.
         *
         * @param name: Name of the metadata item.
         * @param item: New metadata item value to insert.
         * @param length: Length of the vector
         */
        virtual void addMetaItem(const char* name, double* item, size_t length) = 0;

        /**
         * Associate a double 2D Array metadata item with this image frame.
         *
         * @param name: Name of the metadata item.
         * @param item: New metadata item value to insert.
         * @param row: Number of rows.
         * @param col: Number of columns.
         */
        virtual void addMetaItem(const char* name, double** item, size_t row, size_t col) = 0;

        /**
         * Associate a double 3D Array metadata item with this image frame.
         *
         * @param name: Name of the metadata item.
         * @param item: New metadata item value to insert.
         * @param row: Number of rows.
         * @param col: Number of columns.
         * @param depth: Depth of the Array.
         */
        virtual void addMetaItem(const char* name, double*** item, size_t row, size_t col, size_t depth) = 0;

        /**
         * Associate a boolean Array metadata item with this image frame.
         *
         * @param name: Name of the metadata item.
         * @param item: New metadata item to insert.
         * @param length: Length of the vector
         */
        virtual void addMetaItem(const char* name, bool* item, size_t length) = 0;

        /**
         * Destroys this image frame.
         */
        virtual void destroy(void) = 0;


      protected:

        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        /**
         * Disable default constructor.
         *
         * Must remain protected in order for inheritance to work properly.
         *
         */
        IAdaptorFrame(void) {};

        /**
         * Disable default destructor.
         *
         * Must remain protected in order for inheritance to work properly.
         *
         */
        virtual ~IAdaptorFrame(void) {};

      private:
        // ***********************************************************
        // DISABLE DEFAULT METHODS.
        // ***********************************************************
        IAdaptorFrame(const IAdaptorFrame&);
        IAdaptorFrame& operator=(const IAdaptorFrame&);
    };
}
#endif
