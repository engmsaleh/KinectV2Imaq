/**
 * @file:       mwadaptorimaq.h
 *
 * Purpose:     Defines exported C functions required of an adaptor.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */

#ifndef __IMAQADAPTOR__MWADAPTORIMAQ__HEADER__
#define __IMAQADAPTOR__MWADAPTORIMAQ__HEADER__

// *******************************************************************
// IMAGE ACQUISITION TOOLBOX ADAPTOR KIT INCLUDES.
// *******************************************************************
// Hardware & Video Source Information Containers.
#include "IVideoSourceInfo.h"
#include "IDeviceInfo.h"
#include "IDeviceFormat.h"
#include "IHardwareInfo.h"

// Property Interfaces
#include "IPropContainer.h"
#include "IPropFactory.h"
#include "IPropInfo.h"
#include "IPropPostSetListener.h"
#include "IPropCustomGetFcn.h"
#include "IPropCommandFcn.h"

//Property Intergace for Engine
#include "IEnginePropContainer.h"
#include "IEnginePropFactory.h"
#include "IEnginePropInfo.h"
#include "IEnginePropPostSetListener.h"
#include "IEnginePropCustomGetFcn.h"


// Trigger Interfaces.
#include "ITriggerInfo.h"
#include "ITriggerStatus.h"

// Utilities.
#include "IAdaptorFrame.h"
#include "ICriticalSection.h"
#include "IAutoCriticalSection.h"

// Access to the Image Acquisition Engine Interface.
#include "imaqfcnexports.h"
#include "IEngine.h"

// Image Acquisition Adaptor Interface.
#include "IAdaptor.h"


// *******************************************************************
// CONSTANTS FOR IMAGE ACQUISITION ADAPTORS TO REFERENCE.
// *******************************************************************
namespace imaqkit
{
    /// ID for erroring if the specified format is not supported by the device.
    const char* const unsupportedFormatID = "imaq:videoinput:noFormat";

    /// Message for erroring if the specified format is not support by the device.
    const char* const unsupportedFormatMsg = "The FORMAT specified is not supported by this device and is not a valid device file.\nSee IMAQHWINFO(ADAPTORNAME).";
}


// *******************************************************************
// C FUNCTIONS ADAPTORS MUST EXPORT.
// *******************************************************************
/**
 * Exported function to initialize the adaptor.  This function is called
 * directly after the adaptor DLL is loaded into memory, and gives the
 * adaptor a chance to perform initializations before any adaptor object
 * is created.
 *
 * This function is called:
 *
 *  <ul>
 *  <li> When the user executes the IMAQHWINFO or VIDEOINPUT
 *       function for the very first time; or </li>
 *  <li> When the user executes the IMAQHWINFO or VIDEOINPUT
 *       function after having called IMAQRESET </li>
 *  </ul>
 *
 * NOTE: This function will be called only once, before any other exported
 * C functions or imaqkit::IAdaptor instances are ever created.
 *
 */
extern "C" IMAQ_ADAPTOR_IMPORT void initializeAdaptor(void);

/**
 * Exported function to uninitialize the adaptor.  This function is called just
 * before the adaptor DLL is unloaded, and gives the adaptor a chance to delete
 * any dynamically allocated memory, uninitialize any SDK libraries, perform any
 * global clean up, etc.
 *
 * This function is called:
 *
 *  <ul>
 *  <li> When the state of the toolbox is reset using IMAQRESET; or </li>
 *  <li> When MATLAB exits. </li>
 *  </ul>
 *
 * NOTE: This function will be called only once, after all imaqkit::IAdaptor instances
 * have been destroyed by the toolbox engine.
 *
 */
extern "C" IMAQ_ADAPTOR_IMPORT void uninitializeAdaptor(void);

/**
 * Exported function called when the toolbox engine needs to enumerate all the
 * hardware devices currently available on the user's system.
 *
 * Hardware device information is provided by populating the imaqkit::IHardwareInfo
 * hardware container. To populate the hardware container:
 *
 *  <ul>
 *  <li> Create an imaqkit::IDeviceInfo instance for every available device; </li>
 *  <li> Populate the imaqkit::IDeviceInfo instance with as many
 *       imaqkit::IDeviceFormat instances, each describing the available video
 *       formats supported by each device. If the device supports camera files,
 *       indicate this with the imaqkit::IDeviceInfo::setDeviceFileSupport method; </li>
 *  <li> Once the imaqkit::IDeviceInfo instance has been populated with
 *       imaqkit::IDeviceFormat instances, add the imaqkit::IDeviceInfo instance
 *       to the hardware container using the imaqkit::IHardwareInfo::addDevice method. </li>
 *  </ul>
 *
 * @param hardwareContainer : Hardware information container.
 *
 */
extern "C" IMAQ_ADAPTOR_IMPORT void getAvailHW(imaqkit::IHardwareInfo* hardwareContainer);

/**
 * Exported function used by the toolbox engine to determine device specific attributes.
 *
 * This function is invoked by the toolbox engine when a VIDEOINPUT object is created.
 * Information defined by the adaptor for each supported device and format combination is
 * cached by the toolbox engine until an IMAQRESET is performed by the end user.
 *
 * @param deviceInfo: imaqkit::IDeviceInfo handle corresponding to the device to be accessed.
 *                    The handle will be one of the imaqkit::IDeviceInfo objects created
 *                    in the getAvailHW function.
 *
 * @param formatName: The desired acquisition format name selected by the user. This
 *                    will be either one of the format names defined for a specific board,
 *                    or a device filename such as a camera file.
 *
 * @param devicePropFact: Object used to create and add device specific properties.
 *
 * @param sourceContainer: Object used to create and add device specific video sources.
 *
 * @param hwTriggerInfo: Object used to create and add valid hardware trigger configurations.
 *
 */
extern "C" IMAQ_ADAPTOR_IMPORT void getDeviceAttributes(const imaqkit::IDeviceInfo* deviceInfo, const char* formatName,
                                                        imaqkit::IPropFactory* devicePropFact,  imaqkit::IVideoSourceInfo* sourceContainer,
                                                        imaqkit::ITriggerInfo* hwTriggerInfo);

/**
 * Exported function to return a new instance of an imaqkit::IAdaptor.
 *
 * This function is invoked by the toolbox engine for every VIDEOINPUT object
 * instance created by the end user. When the end user deletes a VIDEOINPUT object,
 * the destructor for the imaqkit::IAdaptor object will be invoked.
 *
 * @param engine:     The imaqkit::IEngine handle allows adaptors to
 *                    communicate with the toolbox engine.
 *
 * @param deviceInfo: imaqkit::IDeviceInfo handle indicating the device selected
 *                    by the end user. The handle will be one of the imaqkit::IDeviceInfo
 *                    objects created in the getAvailHW function.
 *
 * @param formatName: The desired acquisition format name selected by the user. This
 *                    will be either one of the format names defined for a specific board,
 *                    or a device filename such as a camera file.
 *
 * @return imaqkit::IAdaptor*: Handle to the adaptor object. NULL if no handle can be created.
 *
 */
extern "C" IMAQ_ADAPTOR_IMPORT imaqkit::IAdaptor* createInstance(imaqkit::IEngine* engine, const imaqkit::IDeviceInfo* deviceInfo,
                                                                 const char* formatName);

#endif
