/**
 * @file:       IHardwareInfo.h
 *
 * Purpose:     Container storing information on available hardware.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2005 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IHARDWAREINFO__HEADER__
#define __IMAQADAPTOR__IHARDWAREINFO__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    /// Forward declare.
    class IDeviceInfo;

    /**
     * Class IHardwareInfo
     *
     * @brief:  Container storing information on the available hardware
     *          an adaptor has access to.
     *
     * This class is used by adaptors to inform the toolbox engine what
     * hardware is currently available and supported.
     *
     * When the user invokes the IMAQHWINFO function for the first time, the
     * getAvailHW function is called and provided an instance of this class,
     * which the adaptor populates with hardware information. The information
     * provided by the adaptor is cached by the toolbox engine.
     *
     * <strong>Destruction:</strong>
     *
     * The contents of this class are destroyed when hardware information
     * is no longer needed, i.e. when IMAQRESET is called, or when MATLAB exits.
     *
     */
    class IHardwareInfo : public IMAQInterface
    {

      public:
        // *******************************************************************
        // DEVICE INFORMATION MANAGEMENT.
        // *******************************************************************
        /**
         * Create a device information object (imaqkit::IDeviceInfo) for storing
         * information specific to a board or device.
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
         * @param id: Device or board ID as seen by the MATLAB user.
         * @param name: Device or board name as seen by the MATLAB user.
         *
         * @return imaqkit::IDeviceInfo* : Interface to a device information object.
         */
        virtual imaqkit::IDeviceInfo* createDeviceInfo(int id, const char* name) = 0;

        /**
         * Add a device information object (imaqkit::IDeviceInfo), created with
         * imaqkit::IHardwareInfo::createDeviceInfo(), to the hardware
         * information object (imaqkit::IHardwareInfo).
         *
         * The toolbox engine will be unaware of any device information that
         * is not added to the imaqkit::IHardwareInfo object.
         *
         * @param device: Device information object to add.
         */
        virtual void addDevice(imaqkit::IDeviceInfo* device) = 0;

        // *******************************************************************
        // ADAPTOR USER DATA.
        // *******************************************************************
        /**
         * Store adaptor-specific information in the imaqkit::IHardwareInfo object.
         *
         * Adaptors can associate adaptor-specific information with an
         * imaqkit::IHardwareInfo object, by defining a C++ class that
         * derives from imaqkit::IMAQInterface.
         *
         * Storing adaptor-specific information offers adaptors an easy way to
         * transfer data around.
         *
         * Note, the adaptor-specific data will be deleted when this
         * class instance is destroyed. Refer to the imaqkit::IHardwareInfo
         * class description to determine when this class is destroyed.
         *
         * You should only call imaqkit::IHardwareInfo::setAdaptorData() once per instance.
         *
         * @param adaptorData: Adaptor-specific data to associate with this class instance.
         *
         */
        virtual void setAdaptorData(imaqkit::IMAQInterface* adaptorData) = 0;

        /**
         * Retrieve the adaptor-specific data associated with
         * this class instance.
         *
         * To convert the adaptor-specific data from an imaqkit::IMAQInterface
         * pointer to a derived class pointer, use the C++ dynamic_cast operator.
         *
         * @return imaqkit::IMAQInterface*: Adaptor specific data associated with this class instance.
         */
        virtual imaqkit::IMAQInterface* getAdaptorData(void) const = 0;

      protected:
        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        IHardwareInfo(void) {};
        virtual ~IHardwareInfo(void) {};

      private:
        // ***********************************************************
        // DISABLE DEFAULT METHODS.
        // ***********************************************************
        IHardwareInfo& operator=(const IHardwareInfo&);
        IHardwareInfo(const IHardwareInfo&);
    };
}

#endif
