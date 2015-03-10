/**
 * @file:       IVideoSourceInfo.h
 *
 * Purpose:     Container for storing video source information.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IVIDEOSOURCEINFO__HEADER__
#define __IMAQADAPTOR__IVIDEOSOURCEINFO__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    /**
     * Class IVideoSourceInfo
     *
     * @brief:  Container used to store video source information.
     *
     * This class is used by adaptors to inform the toolbox engine what
     * video acquisition sources a hardware device has available.
     *
     * When the exported getDeviceAttributes function is called by the toolbox
     * engine, an imaqkit::IVideoSourceInfo object is provided to the adaptor.
     * The adaptor must populate the imaqkit::IVideoSourceInfo object with video
     * source information supported by the selected device (as indicated by the
     * imaqkit::IDeviceInfo object provided) for the given acquisition video format.
     *
     * Each video source defined by the adaptor is presented in MATLAB as a
     * VIDEOSOURCE object. Each video source object represents a collection
     * of one or more physical data sources that are treated as a single
     * entity. The number of video source objects that must be defined depends
     * on the device and the video format selected by the user, but at a minimum,
     * one video source must be defined for a device.
     *
     * For more information on video acquisition sources, refer to the
     * "Creating Image Acquisition Objects" in the Image Acquisition Toolbox
     * User's Guide.
     *
     */
    class IVideoSourceInfo : public IMAQInterface
    {

      public:
        // *******************************************************************
        // ENGINE-ADAPTOR METHODS.
        // *******************************************************************
        /**
         * Adds a video source to the container.
         *
         * The video source ID is provided to facilitate adaptors with
         * identifying a particular source. Source ID's are not used by the
         * toolbox and can be configured to any integer value. For example,
         * numerical source identifiers defined by the hardware SDK can be
         * used as the sourceID.
         *
         * Note, however, that the video source name is exposed to the MATLAB user
         * via VIDEOSOURCE objects.
         *
         * @param sourceName: Name of the source.
         * @param sourceID: Numerical identifier for the source.
         */
        virtual void addAdaptorSource(const char* sourceName, const unsigned int sourceID) = 0;

        /**
         * Returns the total number of sources that have been added.
         *
         * @return size_t: Total number of sources added.
         */
        virtual size_t getNumberOfSources(void) = 0;

        /**
         * Read an element section off the device portion of an IMDF file.
         *
         * If video source information is known a priori, it can be stored
         * in the device section of an IMDF file, under its own element name.
         * This element name can then be provided to this function at run-time
         * in order to instruct the toolbox engine to load video source
         * information from the IMDF file.
         *
         * An element name is the "name" attribute of an &lt;include&gt; section.
         *
         * @param elementName: Element name in the IMDF file.
         */
        virtual void includeIMDFSection(const char* elementName) = 0;

      protected:
        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        IVideoSourceInfo() {};
        virtual ~IVideoSourceInfo(void) {};

      private:
        // ***********************************************************
        // DISABLE DEFAULT METHODS.
        // ***********************************************************
        IVideoSourceInfo& operator=(const IVideoSourceInfo&);
        IVideoSourceInfo(const IVideoSourceInfo&);
    };
}

#endif
