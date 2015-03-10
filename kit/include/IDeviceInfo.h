/**
 * @file:       IDeviceInfo.h
 *
 * Purpose:     Container for device specific information.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2005 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IDEVICEINFO__HEADER__
#define __IMAQADAPTOR__IDEVICEINFO__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    /// Forward declare.
    class IDeviceFormat;

    /**
     * Class IDeviceInfo
     *
     * @brief:  A device information object.
     *
     * Responsible for encapsulating all information specific to a
     * single image capture device or board. An adaptor must create a
     * new imaqkit::IDeviceInfo object for each available hardware device.
     *
     * A hardware device is exposed in MATLAB as a device ID and name
     * pair. All IDs *must* be unique since the MATLAB user will be
     * relying on a unique device ID to identify a device for a given adaptor.
     *
     * In order for an imaqkit::IDeviceInfo object to be valid,
     * it must either:
     *
     *     <ul>
     *     <li> Provide at least 1 supported acquisition format; or </li>
     *     <li> Indicate the device supports device files (i.e. camera files). </li>
     *     </ul>
     *
     * <span style="text-decoration: underline">Destruction:</span>
     *
     * Instances of this class are destroyed when hardware information
     * is no longer needed, i.e. when IMAQRESET is called, or when MATLAB exits.
     *
     */
    class IDeviceInfo : public IMAQInterface
    {

      public:
        // *******************************************************************
        // DEVICE FORMAT MANAGEMENT.
        // *******************************************************************
        /**
         * Create an imaqkit::IDeviceFormat object for storing video format information
         * supported by a board or device.
         *
         * Device format objects are used to encapsulate information on
         * a supported format. Supported formats are defined by associating
         * a name with a numerical identifier.
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
         * @param id: Format ID.
         * @param name: Format name as seen by the MATLAB user.
         *
         * @return imaqkit::IDeviceFormat* : Interface to a device format object.
         */
        virtual imaqkit::IDeviceFormat* createDeviceFormat(int id, const char* name) = 0;

        /**
         * Add an imaqkit::IDeviceFormat object to the imaqkit::IDeviceInfo object.
         *
         * When imaqkit::IDeviceFormat objects are added, they can be identified as
         * a default, or non-default format. The default format is communicated to the
         * MATLAB user with IMAQHWINFO. The MATLAB VIDEOINPUT object constructor will
         * use the default format if the user does not specify a video format.
         *
         * If the imaqkit::IDeviceFormat object is not flagged as default, or non-default
         * when it is added, it will be flagged as non-default.
         *
         * @param format: Format supported by the device.
         * @param defaultFlag: True if the format being added is the default format.
         */
        virtual void addDeviceFormat(imaqkit::IDeviceFormat* format, bool defaultFlag = false) = 0;

        // *******************************************************************
        // DEVICE INFO SETTINGS.
        // *******************************************************************
        /**
         * Return the device ID.
         *
         * @return int: Hardware device identifier.
         *
         */
        virtual int getDeviceID(void) const = 0;

        /**
         * Return the device name.
         *
         * @return const char*: Hardware device name.
         *
         */
        virtual const char* getDeviceName(void) const = 0;

        /**
         * Configure the flag indicating if the hardware
         * device supports device configuration files (i.e. camera files).
         *
         * By default, a device is flagged as not supporting
         * device files.
         *
         * @param deviceFileSupported: True if device supports device files, false otherwise.
         *
         */
        virtual void setDeviceFileSupport(bool deviceFileSupported = false) = 0;

        /**
         * Return the value of the flag that indicates if the hardware
         * device supports device configuration files (i.e. camera files).
         *
         * @return bool: True if device supports device files, false otherwise.
         *
         */
        virtual bool getDeviceFileSupport(void) const = 0;

        // *******************************************************************
        // SUPPORTED DEVICE FORMATS.
        // *******************************************************************
        /**
         * Return the total number of device formats currently supported
         * by the device.
         *
         * @return int: Number of supported formats.
         */
        virtual int getNumberOfDeviceFormats(void) const = 0;

        /**
         * Return the imaqkit::IDeviceFormat object with the given name.
         *
         * If no device format exists with the given name, NULL is returned.
         *
         * Device format names are case sensitive.
         *
         * @param formatName: Format name to look up.
         *
         * @return imaqkit::IDeviceFormat*: Device format object.
         */
        virtual imaqkit::IDeviceFormat* getDeviceFormat(const char* formatName) const = 0;

        // *******************************************************************
        // DEFAULT FORMATS.
        // *******************************************************************
        /**
         * Return true if the default format has been set,
         * false otherwise.
         *
         * @return bool: Flag indicating if the default format has been set.
         */
        virtual bool isDefaultFormatSet(void) const = 0;

        /**
         * Return the name of the device's default format.
         *
         * If no formats are available, an empty string ("") is returned.
         *
         * @return const char* : Default format name.
         */
        virtual const char* getDefaultFormatName(void) const = 0;

        /**
         * Return the device's default format.
         *
         * If no format has been flagged as the default
         * when this method is called, the function returns the
         * first available format as the default.
         *
         * If no formats are available, NULL is returned.
         *
         * @return imaqkit::IDeviceFormat* : Default format object.
         */
        virtual imaqkit::IDeviceFormat* getDefaultFormat(void) const = 0;

        // *******************************************************************
        // ADAPTOR USER DATA.
        // *******************************************************************
        /**
         * Store adaptor-specific information in the imaqkit::IDeviceInfo object.
         *
         * Adaptors can associate adaptor-specific information with an
         * imaqkit::IDeviceInfo object, by defining a C++ class that
         * derives from imaqkit::IMAQInterface.
         *
         * Since imaqkit::IDeviceInfo objects are provided by the engine to
         * different adaptor functions like getDeviceAttributes and createInstance,
         * storing adaptor-specific information offers adaptors an easy way to
         * transfer data around.
         *
         * Note, the adaptor-specific data will be deleted when this
         * class instance is destroyed. Refer to the imaqkit::IDeviceInfo
         * class description to determine when this class is destroyed.
         *
         * You should only call imaqkit::IDeviceInfo::setAdaptorData() once per instance.
         *
         * @param adaptorData: Adaptor-specific data to associate with this class instance.
         */
        virtual void setAdaptorData(imaqkit::IMAQInterface* adaptorData) = 0;

        /**
         * Retrieve adaptor-specific data associated with
         * this class instance.
         *
         * To convert the adaptor-specific data from an imaqkit::IMAQInterface
         * pointer to a derived class pointer, use the C++ dynamic_cast operator.
         *
         * @return imaqkit::IMAQInterface* : Adaptor specific data associated with this class instance.
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
        virtual ~IDeviceInfo(void) {};

      protected:
        // *******************************************************************
        // CONSTRUCTORS.
        // *******************************************************************
        IDeviceInfo(void) {};

        /**
         * Encapsulates information specific to a device. Information includes
         * the device or board identifier and its name.
         *
         * The identifier for the board or device is the same ID presented
         * to the MATLAB user through IMAQHWINFO. This ID must be unique in
         * order for a MATLAB user to successfully identify the desired device.
         *
         * It is recommended adaptors use monotonically increasing IDs starting
         * with 1, not 0.
         *
         * The name for the board or device is the same name presented
         * to the MATLAB user through IMAQHWINFO.
         *
         * @param deviceID: Device or board identifier.
         * @param deviceName: Device or board name.
         */
        IDeviceInfo(int deviceID, const char* deviceName);

      private:
        // ***********************************************************
        // DISABLE DEFAULT METHODS.
        // ***********************************************************
        IDeviceInfo(const IDeviceInfo&);
        IDeviceInfo& operator=(const IDeviceInfo&);
    };
}

#endif
