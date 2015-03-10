/**
 * @file:       imaqfcnexports.h
 *
 * Purpose:     Exported utility functions for image acquisition adaptors.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright   2001-2014 The MathWorks, Inc.$
 *
 *
 */

#ifndef __IMAQADAPTOR__IMAQFCNEXPORTS__HEADER__
#define __IMAQADAPTOR__IMAQFCNEXPORTS__HEADER__

#include "imaqexportdef.h"
#include "IAdaptorFrame.h"

//
// Exported utility C functions for Image Acquisition Toolbox adaptors.
//
// The following functions are exported to facilitate image acquisition
// adaptor developers.
//
namespace imaqkit
{
    // Forward declarations.
    class ICriticalSection;
    class IAutoCriticalSection;
    class IEngine;
    class IAdaptor;
    class IAdaptorManager;

    // ***************************************************
    // ERRORS & WARNINGS.
    // ***************************************************
    /**
     * Generate a MATLAB warning.
     *
     * The warning message can be specified as a sprintf style
     * format string. Values for the message can be passed in
     * as optional parameters.
     *
     * Provides adaptors a way to generate warnings at the
     * MATLAB command line.
     *
     * @param msgID: Warning message ID
     * @param msg: Warning message.
     * @param ...: Values for the message.
     *
     */
    IMAQ_ADAPTOR_EXPORT
        void adaptorWarn(const char* msgID, const char* msg, ...);

    /**
     * Generate a MATLAB error.
     *
     * This function allows adaptors to generate an error back in
     * MATLAB. It can be called from any thread, at any time.
     *
     * If this function is called from the MATLAB thread, an exception
     * is automatically thrown for the adaptor. In these cases, an
     * imaqkit::IAdaptor handle is not needed and can be specified as NULL.
     *
     * Note, when this function is called from the MATLAB thread, it
     * executes synchronously and exits the calling function from the
     * point of call.
     *
     * If this function is called off the MATLAB thread, i.e. from a thread
     * owned and managed by the adaptor or hardware SDK, then a valid
     * imaqkit::IAdaptor handle must be provided. If the imaqkit::IAdaptor object
     * is currently transfering image frames, the imaqkit::IEngine will instruct
     * the adaptor to stop, as well as post an error request back to MATLAB.
     *
     * Note, when this function is called off the MATLAB thread, it executes
     * asynchronously and does not exit the calling function. Therefore, after
     * calling adaptorError you should perform whatever cleanup is necessary
     * and return from the calling function
     *
     * As a rule of thumb, if an imaqkit::IAdaptor handle is available, it
     * should always be provided. This will reduce the risk of potential bugs
     * if this function happens to be invoked off the MATLAB thread at a later date.
     *
     * The error message can be specified as a sprintf style format string.
     * Values for the message can be passed in as optional parameters.
     *
     * @param adaptor: Handle to the adaptor. NULL if called from the MATLAB thread.
     * @param msgID: Error message ID
     * @param msg: Error message.
     * @param ...: Sprintf values for the error message.
     *
     */
    IMAQ_ADAPTOR_EXPORT
        void adaptorError(const imaqkit::IAdaptor* adaptor, const char* msgID, const char* msg, ...);

    // ***************************************************
    // THREADING UTILITIES.
    // ***************************************************
    /**
     * Instantiate a new critical section object.
     *
     * Critical section objects allow adaptors to protect resources
     * accessed from multiple threads.
     *
     * Using imaqkit::ICriticalSection and imaqkit::IAutoCriticalSection objects
     * together will prevent deadlocks in cases where an exception is thrown while
     * a thread is waiting to enter code sections or access resources that are being
     * protected.
     *
     * Adaptors creating imaqkit::ICriticalSection objects must be
     * sure to destroy them when they are no longer needed
     * by calling delete on the pointer returned by this function.
     * For example:
     *
     * @code
     *
     * // To protect resources or a section of code from being accessed simultaneously
     * // across threads, create an imaqkit::ICriticalSection object. The
     * // imaqkit::ICriticalSection object can be used wherever a section of code
     * // needs to be protected. Be sure to destroy the imaqkit::ICriticalSection object
     * // when it is no longer needed.
     * class MyAdaptor{
     *
     * public:
     *    MyAdaptor(void){
     *        // This critical section will allow MyAdaptor methods to access
     *        // resources or sections of code in a thread safe manner.
     *        _section = imaqkit::createCriticalSection();
     *    }
     *
     *    ~MyAdaptor(void){
     *        // Destroy the critical section object.
     *        delete _section;
     *    }
     *
     * private:
     *    /// Critical section object.
     *    imaqkit::ICriticalSection* _section;
     * }
     *
     * @endcode
     *
     * See the imaqkit::ICriticalSection class for additional
     * information.
     *
     * @return imaqkit::ICriticalSection*: Critical section object.
     */
    IMAQ_ADAPTOR_EXPORT
        imaqkit::ICriticalSection* createCriticalSection(void);

    /**
     * Instantiate a new auto critical section object.
     *
     * Auto critical section objects can be used to wrap imaqkit::ICriticalSection
     * objects in a way that guarantees the section will be released
     * upon going out of scope, or if an exception occurs.
     *
     * Using imaqkit::ICriticalSection and imaqkit::IAutoCriticalSection objects
     * together will prevent deadlocks in cases where an exception is thrown while
     * a thread is waiting to enter code sections or access resources that are being
     * protected.
     *
     * Because this function instantiates a new imaqkit::IAutoCriticalSection
     * object, it must be destroyed when it is no longer needed.
     *
     * In order to properly manage these critical section objects, the use of
     * a smart pointer that retains sole ownership of an object is recommended.
     * For example, the following paradigm is suggested:
     *
     * @code
     *
     * // To protect resources or a section of code from being accessed simultaneously
     * // across threads, create an imaqkit::IAutoCriticalSection object, which:
     * //    1) Automatically enters (locks) the imaqkit::ICriticalSection object provided; and
     * //    2) Automatically leaves (releases) it when the imaqkit::IAutoCriticalSection object is destroyed.
     * //
     * // Auto destroy the imaqkit::IAutoCriticalSection pointer by using a smart pointer
     * // like std::auto_ptr<> object.
     * imaqkit::IAutoCriticalSection* autoSection = imaqkit::createAutoCriticalSection(_section);
     * std::auto_ptr<imaqkit::IAutoCriticalSection> section(autoSection);
     * ...
     *
     * // Access resources or sections of code in a thread safe manner.
     * // When the auto_ptr object goes out of scope, i.e. when the method returns
     * // or if an exception occurs, everything will be released and destroyed correctly.
     * ...
     *
     * @endcode
     *
     * See the imaqkit::IAutoCriticalSection class for information on its methods.
     *
     * @param section: The critical section object to enter/leave.
     * @param enter: True to indicate the critical section object should be entered upon creation.
     *
     * @return imaqkit::IAutoCriticalSection*: Auto critical section object.
     *
     */
    IMAQ_ADAPTOR_EXPORT
        imaqkit::IAutoCriticalSection* createAutoCriticalSection(imaqkit::ICriticalSection* section, bool enter = true);

    // ***************************************************
    // MISC UTILITIES.
    // ***************************************************
    /**
     * Return the color space for a given frame type.
     *
     * This function can be used by the imaqkit::IAdaptor::getColorSpace
     * method in order to determine the color space of the frame
     * returned by the imaqkit::IEngine::makeFrame function.
     *
     * The definition for the returned enumeration can be found
     * in IAdaptorFrame.h
     *
     * @param frameType: The image frame type being used.
     *
     * @return imaqkit::colorspaces::COLORSPACE: The enumerated color space of the frame.
     */
    IMAQ_ADAPTOR_EXPORT
        imaqkit::colorspaces::COLORSPACE getFrameColorSpace(imaqkit::frametypes::FRAMETYPE frameType);

    /**
     * Request the current system time value.
     *
     * Returns the current system time in seconds past
     * midnight, January 1, 1970, which can be used as the
     * timestamp for an imaqkit::IAdaptorFrame object.
     *
     * @return double: Current system time value.
     */
    IMAQ_ADAPTOR_EXPORT
        double getCurrentTime(void);

    /**
     * Query the toolbox to determine if a particular hidden
     * feature (i.e. hidden setting) has been turned on.
     *
     * Hidden features provide adaptor developers a way to
     * enable or disable settings, for the purpose of
     * debugging or working around adaptor specific issues.
     *
     * In general, these settings are left undocumented and are
     * offered to a user as a means of temporarily working around
     * an adaptor specific issue.
     *
     * An example use case would be an adaptor that anticipates
     * hardware or driver problems with a certain class of devices.
     * If this is an isolated issue, a hidden feature could be offered
     * to the end user as a means of disabling the adaptor from
     * accessing this class of devices.
     *
     * Another use case would be to simply report debugging messages
     * from the adaptor in order to gather diagnostic information from
     * a user, for the purpose of troubleshooting a hardware specific problem.
     *
     * Adaptors can create new hidden features by defining
     * them at the MATLAB command line. For example:
     *
     * @code
     *
     * >> % Create a new hidden feature by
     * >> % specifying a name and default value.
     * >> imaqmex('addfeature', '-MyNewFeatureName', true)
     *
     * >> % Query the current hidden feature setting.
     * >> imaqmex('feature', '-MyNewFeatureName')
     *
     * ---------------------------
     *
     * // In the adaptor C code, query the toolbox engine
     * // for the current hidden feature setting.
     * bool isOn = imaqkit::isFeatureOn("-MyNewFeatureName");
     *
     * @endcode
     *
     * If the hidden feature is not turned on, or does not
     * exist, false is returned.
     *
     * @param feature: Name of the feature.
     *
     * @return bool: True if feature is turned on.
     */
    IMAQ_ADAPTOR_EXPORT
        bool isFeatureOn(const char* feature);

    /**
     * Query the toolbox to determine if a particular hidden
     * feature (i.e. hidden setting) has been set.
     *
     * Hidden features provide adaptor developers a way to
     * store settings, for the purpose of storing values that
     * do not fit into the device specific properties, debugging
     * or working around adaptor specific issues.
     *
     * In general, these settings are left undocumented and are
     * offered to a user as a way to adjust a value used by an adaptor.
     *
     * An example use case would be an adaptor that has a timeout value
     * that may need to be adjusted, but that the adaptor writer
     * does not feel is appropriate as a device specific property.
     *
     * Adaptors can create new hidden features by defining
     * them at the MATLAB command line. For example:
     *
     * @code
     *
     * >> % Create a new hidden feature by
     * >> % specifying a name and default value.
     * >> imaqmex('addfeature', '-MyNewFeatureName', 3.4)
     *
     * >> % Query the current hidden feature setting.
     * >> imaqmex('feature', '-MyNewFeatureName')
     *
     * ---------------------------
     *
     * // In the adaptor C code, query the toolbox engine
     * // for the current hidden feature setting.
     * double value = imaqkit::getNumericFeatureValue("-MyNewFeatureName");
     *
     * @endcode
     *
     * If the hidden feature does not exist, 0 is returned.
     *
     * @param feature: Name of the feature.
     *
     * @return double: Value for the feature.
     */
    IMAQ_ADAPTOR_EXPORT
        double getNumericFeatureValue(const char* feature);

    // ***************************************************
    // INTERNAL UTILITIES USED BY THE ADAPTOR KIT.
    // NOT FOR USE BY ADAPTOR WRITERS.
    // ***************************************************
    /**
     * @internal
     *
     * Allocate dynamic memory of the given size.
     *
     * This function is used for managing dynamic memory
     * allocations between the engine and adaptor interfaces.
     *
     * @param len: Memory allocation size.
     *
     * @return void*: Newly allocated dynamic memory.
     */
    IMAQ_ADAPTOR_EXPORT
        void* imaqmalloc(size_t len);

    /**
     * @internal
     *
     * Free a pointer to dynamic memory.
     *
     * This function is used for managing dynamic memory
     * allocations between the engine and adaptor interfaces.
     *
     * @param ptr: Pointer to allocated dynamic memory.
     */
    IMAQ_ADAPTOR_EXPORT
        void imaqfree(void* ptr);

    /**
     * @internal
     *
     * Create an adaptor manager interface.
     *
     * This function is used for managing communication between
     * the engine and adaptor interfaces.
     *
     * It is not intended to be directly used by adaptor writers.
     *
     * @param adaptor: Interface to the adaptor.
     * @param engine: Interface to the engine.
     *
     * @return imaqkit::IAdaptorManager*: Adaptor manager interface.
     */
    IMAQ_ADAPTOR_EXPORT
        imaqkit::IAdaptorManager* createAdaptorManager(imaqkit::IAdaptor* adaptor, imaqkit::IEngine* engine);
}

#endif
