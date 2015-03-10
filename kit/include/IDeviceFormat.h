/**
 * @file:       IDeviceFormat.h
 *
 * Purpose:     Object container storing a format supported by the device.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2005 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IDEVICEFORMAT__HEADER__
#define __IMAQADAPTOR__IDEVICEFORMAT__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{
    /**
     * Class IDeviceFormat
     *
     * @brief:  Object container storing a device's supported acquisition formats.
     *
     *          This class encapsulates an acquisition format supported by a device.
     *          The acquisition format name for each imaqkit::IDeviceFormat instance
     *          will be exposed to users in MATLAB. Examples of an acquisition format
     *          may include NTSC, RGB24, PAL, YUV422, etc.
     *
     *          When the exported getDeviceAttributes function is called by the toolbox
     *          engine, one of the imaqkit::IDeviceFormat name's will be provided, in
     *          order to indicate the format selected by the MATLAB end user.
     *
     *          Note, for hardware supporting device files (i.e. camera files), the file
     *          name is provided instead of an imaqkit::IDeviceFormat name.
     *
     * <span style="text-decoration: underline">Destruction:</span>
     *
     *          imaqkit::IDeviceFormat instances will be stored by the toolbox engine
     *          inside an imaqkit::IDeviceInfo object. All instances will be cached
     *          until the IMAQRESET function is invoked or MATLAB exits, at which
     *          point all instances are destroyed.
     *
     */
    class IDeviceFormat : public IMAQInterface
    {

      public:
        // *******************************************************************
        // ACCESSOR METHODS.
        // *******************************************************************
        /**
         * Return the name of the supported format.
         *
         * @return const char* : Format's name.
         */
        virtual const char* getFormatName(void) const = 0;

        /**
         * Return the ID of the supported format.
         *
         * @return int: Format's identifier.
         */
        virtual int getFormatID(void) const = 0;

        /**
         * Return true if this format is the device's default,
         * false otherwise.
         *
         * @return bool: Format default flag.
         */
        virtual bool isDefault(void) const = 0;

        // *******************************************************************
        // ADAPTOR USER DATA.
        // *******************************************************************
        /**
         * Store adaptor-specific information in the imaqkit::IDeviceFormat object.
         *
         * Adaptors can associate adaptor-specific information with an
         * imaqkit::IDeviceFormat object, by defining a C++ class that
         * derives from imaqkit::IMAQInterface.
         *
         * Since imaqkit::IDeviceFormat objects are stored inside an
         * imaqkit::IDeviceInfo object, which is provided by the engine to
         * different adaptor functions like getDeviceAttributes and createInstance,
         * storing adaptor-specific information offers adaptors an easy way to
         * transfer data around.
         *
         * Note, the adaptor-specific data will be deleted when this
         * class instance is destroyed. Refer to the imaqkit::IDeviceFormat
         * class description to determine when this class is destroyed.
         *
         * You should only call imaqkit::IDeviceFormat::setAdaptorData() once per instance.
         *
         * @param adaptorData: Adaptor-specific data to associate with this class instance.
         */
        virtual void setAdaptorData(imaqkit::IMAQInterface* adaptorData) = 0;

        /**
         * Retrieve the adaptor-specific data associated with
         * this class instance.
         *
         * To convert the adaptor-specific data from an imaqkit::IMAQInterface
         * pointer to a derived class pointer, use the C++ dynamic_cast operator.
         *
         * @return imaqkit::IMAQInterface* : Adaptor-specific data associated with this class instance.
         */
        virtual imaqkit::IMAQInterface* getAdaptorData(void) const = 0;

        // *******************************************************************
        // DESTRUCTOR.
        // *******************************************************************
        /**
         * This routine is invoked by imaqkit::IEngine when it no longer needs
         * to store device information, i.e. when IMAQRESET is called or
         * when MATLAB exits.
         */
        virtual ~IDeviceFormat(void) {};

      protected:
        // *******************************************************************
        // CONSTRUCTORS.
        // *******************************************************************
        IDeviceFormat(void) {};

        /**
         * Constructs a device format object.
         *
         * Device format objects are used to encapsulate information on
         * a supported format. Supported formats are defined by associating
         * a name with a numerical identifier.
         *
         * A format can be flagged as the device's default when it is added
         * to the imaqkit::IDeviceInfo container.
         *
         * The format ID is provided to facilitate adaptors with
         * identifying a particular format. Format ID's are not used by the
         * toolbox and can be configured to any integer value. For example,
         * numerical format identifiers defined by the hardware SDK can be
         * used as the format ID.
         *
         * Note, however, that the format name is exposed to the MATLAB user
         * via IMAQHWINFO.
         *
         * @param formatID: Format identifier.
         * @param formatName: Format name.
         */
        IDeviceFormat(int formatID, const char* formatName);

      private:
        // *******************************************************************
        // DISABLE DEFAULT METHODS.
        // *******************************************************************
        IDeviceFormat(const IDeviceFormat&);
        IDeviceFormat& operator=(const IDeviceFormat&);
    };
}

#endif
