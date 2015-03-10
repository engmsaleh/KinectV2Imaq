/**
 * @file:       mwdemoimaq.cpp
 *
 * Purpose:     Implements adaptor information functions.
 *
 *
 * $Authors:    JSH, CP, DT, KL $
 *
 * Copyright 2006-2013 The MathWorks, Inc.
 *
 *
 */

#include "mwdemoimaq.h"
#include "mwadaptorimaq.h"
#include "DemoAdaptor.h"
#include "DemoDeviceFormat.h"

// *******************************************************************
// EXPORTED FUNCTIONS
// *******************************************************************

/**
 * initializeAdaptor: Exported function to initialize the adaptor.
 * This function is called directly after the adaptor DLL is loaded into
 * memory and gives the adaptor a chance to perform initializations before
 * any adaptor object is created.
 */

void initializeAdaptor()
{

    // TODO Insert any initialization or one-time processing your adaptor requires.
}

/**
 * uninitializeAdaptor: Exported function to uninitialize the adaptor.
 * This function is called just before the adaptor DLL is unloaded when the
 * state of the toolbox is reset using IMAQRESET or when MATLAB exits.
 * This function gives the adaptor a chance to perform any clean-up tasks
 * such as deleting any dynamically allocated memory not covered in the
 * adaptor instance's destructor. This function will be called after the
 * destructor for all existing adaptor objects have been invoked.
 */

void uninitializeAdaptor()
{

    // TODO Insert any clean-up code required by your adaptor.
}

/**
 * getAvailHW: Exported function to enumerate all the hardware to which
 * the adaptor interfaces. The imaqkit::IEngine calls this function when the
 * IMAQHWINFO function is called on the MATLAB command line.
 *
 * Adaptors can query the device's SDK to find out what devices are available.
 * Adaptors can also query the SDK for information about the formats supported
 * by each device. If this format information is available in advance, an adaptor
 * writer can store it in an IMDF file.
 *
 * @param imaqkit:IHardwareInfo*: The imaqkit::IEngine passes a handle to a hardware
 *                                information container. Adaptors use this container
 *                                to communicate all the hardware supported by the adaptor.
 */

void getAvailHW(imaqkit::IHardwareInfo* hardwareContainer)
{

    // **************************************************************
    // ADD A DEVICE -- Color Device
    // **************************************************************
    // The following summarizes the steps required to add a device:
    //    1. Create an imaqkit::IDeviceInfo object to represent the device.
    //    2. Indicate whether the device supports device configuration files.
    //    3. Create an imaqkit::IDeviceFormat object for each video format
    //       supported by the device.
    //    4. Instantiate a DemoDeviceFormat object and store device-specific
    //       format information in it.
    //       Note: This step is required only because the demo adaptor defines
    //       this class. Your adaptor might choose another way to handle
    //       device-specific format information.
    //    5. Set the adaptor data in the imaqkit::IDeviceFormat object to hold the
    //       DemoDeviceFormat object.
    //    6. Add the imaqkit::IDeviceFormat object to the imaqkit::IDeviceInfo object
    //       - Repeat steps 3 through 6 for each format. When all formats for
    //         a device are done, go to step 7.
    //    7. Add the imaqkit::IDeviceInfo object to the imaqkit::IHardwareInfo object
    //       - Repeat steps 1 through 6 for each device
    //
    // Create an imaqkit::IDeviceInfo Object
    // ------------------------------------------
    //
    // Call the createDeviceInfo() method of the imaqkit:IHardwareInfo object,
    // specifying as arguments:
    //    - Device ID
    //    - Device Name
    // You determine what the name and device ID should be. By convention, because
    // MATLAB uses 1-based indexing, device IDs should typically start at 1. However,
    // if your device supports its own device IDs, you can use them instead.
    // Device IDs are visible to MATLAB users.
    imaqkit::IDeviceInfo* deviceInfo = hardwareContainer->createDeviceInfo(demo::RGB_DEVICE_ID, demo::COLOR_DEVICE_STR);

    // Indicate Device File Support
    // ------------------------------------------------------------------
    //
    // Call the setDeviceFileSupport() method of the imaqkit::IDeviceInfo object
    // specifying TRUE is the device supports device files and FALSE, otherwise.
    deviceInfo->setDeviceFileSupport(false);

    // Create an imaqkit::IDeviceFormat Object
    // ------------------------------------------
    //
    // Call the createDeviceFormat method of the imaqkit::IDeviceInfo object
    // created in the previous step, specifying as arguments:
    //    - Format ID
    //    - Format Name
    // Use any ID numbering convention you want to identify device formats.
    // They provide a convenient way to identify device formats but are not
    // visible to MATLAB users.
    imaqkit::IDeviceFormat* deviceFormat = deviceInfo->createDeviceFormat(demo::RGB_FORMAT_ID, demo::RGB_FORMAT_STR);

    // Create a DemoDeviceFormat Object (Demo Adaptor Specific)
    // ------------------------------------------------------------------------------
    // The demo adaptor defines a new format class, called DemoDeviceFormat, to store
    // information about device formats, such as width, height, and number of bands.
    // You must instantiate an object of this class.
    DemoDeviceFormat* rgbFormatInfo = new DemoDeviceFormat();

    // Use DemoDeviceFormat methods to store device-specific format information.
    rgbFormatInfo->setFormatWidth(demo::RGB_FORMAT_WIDTH);
    rgbFormatInfo->setFormatHeight(demo::RGB_FORMAT_HEIGHT);
    rgbFormatInfo->setFormatNumBands(demo::RGB_FORMAT_BANDS);
    rgbFormatInfo->setFormatFrameType(imaqkit::frametypes::RGB24_PACKED);

    // Set the imaqkit::IDeviceFormat Object Adaptor Data
    // -----------------------------------------------------------------------
    //
    // Set the value of imaqkit::IDeviceFormat object's adaptor data to
    // the DemoDeviceFormat about, using the setAdaptorData() method.
    deviceFormat->setAdaptorData(rgbFormatInfo);

    // Add the imaqkit::IDeviceFormat Object to the imaqkit::IDeviceInfo Object
    // ------------------------------------------------------------------------
    //
    // Use the addDeviceFormat() method of the imaqkit::IDeviceInfo object.
    // The second argument is a Boolean indicating if this format should be
    // the default format.
    deviceInfo->addDeviceFormat(deviceFormat, true);

    // Create another imaqkit::IDeviceFormat object.
    deviceFormat = deviceInfo->createDeviceFormat(demo::SVIDEO_FORMAT_ID, demo::SVIDEO_FORMAT_STR);

    // Create another DemoDeviceFormat object.
    DemoDeviceFormat* svideoFormatInfo = new DemoDeviceFormat();

    // Set the values of DemoDeviceFormat data fields.
    svideoFormatInfo->setFormatWidth(demo::SVIDEO_FORMAT_WIDTH);
    svideoFormatInfo->setFormatHeight(demo::SVIDEO_FORMAT_HEIGHT);
    svideoFormatInfo->setFormatNumBands(demo::SVIDEO_FORMAT_BANDS);
    svideoFormatInfo->setFormatFrameType(imaqkit::frametypes::RGB24_PACKED);

    // Add the DemoDeviceFormat object to the imaqkit::IDeviceFormat object.
    deviceFormat->setAdaptorData(svideoFormatInfo);

    // Add the imaqkit::IDeviceFormat object to the imaqkit::IDeviceInfo object.
    deviceInfo->addDeviceFormat(deviceFormat);

    // After creating all the format objects for this device, add the
    // imaqkit::IDeviceInfo object to the imaqkit::IHardwareInfo object.
    // Use the addDevice() method of the imaqkit::IHardwareInfo object.
    hardwareContainer->addDevice(deviceInfo);


    // ***************************************************************
    // ADD A SECOND DEVICE -- Monochrome Device
    // ***************************************************************
    // Create the imaqkit::IDeviceInfo object.
    deviceInfo = hardwareContainer->createDeviceInfo(demo::MONOCHROME_DEVICE_ID, demo::MONOCHROME_DEVICE_STR);

    // Indicate whether the device supports device configuration files.
    deviceInfo->setDeviceFileSupport(false);

    // Create the imaqkit::IDeviceFormat object.
    deviceFormat = deviceInfo->createDeviceFormat(demo::RS170_FORMAT_ID, demo::RS170_FORMAT_STR);

    // Create the DemoDeviceFormat object.
    DemoDeviceFormat* rs170FormatInfo = new DemoDeviceFormat();

    rs170FormatInfo->setFormatWidth(demo::RS170_FORMAT_WIDTH);
    rs170FormatInfo->setFormatHeight(demo::RS170_FORMAT_HEIGHT);
    rs170FormatInfo->setFormatNumBands(demo::RS170_FORMAT_BANDS);
    rs170FormatInfo->setFormatFrameType(imaqkit::frametypes::MONO8);

    // Add the DemoDeviceFormat object to the imaqkit::IDeviceFormat object.
    deviceFormat->setAdaptorData(rs170FormatInfo);

    // Add the imaqkit::IDeviceFormat object to the imaqkit::IDeviceInfo object.
    deviceInfo->addDeviceFormat(deviceFormat, true);

    // Repeat steps for another format.
    deviceFormat = deviceInfo->createDeviceFormat(demo::CCIR_FORMAT_ID, demo::CCIR_FORMAT_STR);

    DemoDeviceFormat* ccirFormatInfo = new DemoDeviceFormat();

    ccirFormatInfo->setFormatWidth(demo::CCIR_FORMAT_WIDTH);
    ccirFormatInfo->setFormatHeight(demo::CCIR_FORMAT_HEIGHT);
    ccirFormatInfo->setFormatNumBands(demo::CCIR_FORMAT_BANDS);
    ccirFormatInfo->setFormatFrameType(imaqkit::frametypes::MONO8);

    deviceFormat->setAdaptorData(ccirFormatInfo);

    deviceInfo->addDeviceFormat(deviceFormat);

    // Add the imaqkit::IDeviceInfo object to the imaqkit::IHardwareInfo object
    hardwareContainer->addDevice(deviceInfo);

    // ***************************************************************
    // ADD A THIRD DEVICE  -- Digital Hardware with configuration file
    // ***************************************************************
    // Create the imaqkit::IDeviceInfo object.
    deviceInfo = hardwareContainer->createDeviceInfo(demo::DIGITAL_FRAMEGRABBER_DEVICE_ID, demo::DIGITAL_HARDWARE_STR);

    // Digital video devices typically support camera configuration files.
    deviceInfo->setDeviceFileSupport(true);

    // Digital video devices typically don't support standard formats
    // so no need to create any.

    // Add the imaqkit::IDeviceInfo object to the imaqkit::IHardwareInfo object.
    hardwareContainer->addDevice(deviceInfo);
}

/**
 * getDeviceAttributes() -- Exported function used to dynamically add device-specific
 * properties. The imaqkit::IEngine calls this function when a user creates a
 * video input object by calling the VIDEOINPUT function at the MATLAB command line.
 *
 * Adaptors can query the device's SDK to determine these properties or, if the
 * information is available in advance, store it in an IMDF file and read the
 * information from the file.
 *
 * Adaptors create property objects and use methods of the imaqkit::IPropFactory object
 * to store the properties in the device-specific property container.
 *
 * @param deviceInfo: The imaqkit::IEngine passes a handle to an imaqkit::IDeviceInfo object
 *                    identifying the target device. The handle will be one of
 *                    the IDeviceInfo objects created in getAvailHW().
 *
 * @param formatName: The imaqkit::IEngine passes a text string that specifies either one
 *                    of the fixed format names specified for the device in getAvailHW() or
 *                    a filename.
 *                    If it's a file name, it is the name of a device configuration
 *                    file (also known as a camera file).
 *                    The imaqkit::IEngine performs no processing on device configuration files.
 *                    Your adaptor should just pass this file to your device.
 *
 * @param devicePropFact: The imaqkit::IEngine passes a handle to an imaqkit::IPropFactory object.
 *                        This object supports methods you use to create and add device-specific properties.
 *
 * @param sourceContainer: The imaqkit::IEngine passes a handle to an imaqkit::IVideoSourceInfo
 *                         object. You use this object to identify the device-specific
 *                         video sources.
 *
 *                         NOTE: To be able to create a videoinput object in MATLAB,
 *                               your adaptor must identify at least one video source.
 *
 * @param hwTriggerInfo: The imaqkit::IEngine passes a handle to an imaqkit::ITriggerInfo object.
 *                       You use this object to create and add valid hardware
 *                       trigger configurations. Manual and immediate trigger
 *                         configurations are handled by the IMAQ engine automatically.
 *
 */
void getDeviceAttributes(const imaqkit::IDeviceInfo* deviceInfo,
                         const char* formatName,
                         imaqkit::IPropFactory* devicePropFact,
                         imaqkit::IVideoSourceInfo* sourceContainer,
                         imaqkit::ITriggerInfo* hwTriggerInfo)
{

    void* hProp;  // Declare a handle to a property object.

    // Get the device ID from the imaqkit::IDeviceInfo object.
    int devID = deviceInfo->getDeviceID();

    // Create properties based on which device was selected.
    if (devID == demo::RGB_DEVICE_ID) {
        // ********************************************************
        // IDENTIFY THE VIDEO SOURCE
        // ********************************************************
        // Use the imaqkit::IVideoSourceInfo object's addAdaptorSource() method
        // to specify the video source. The addAdaptorSource method
        // accepts two arguments:
        //      - Source name (text string)
        //      - Numeric ID

        sourceContainer->addAdaptorSource(demo::SOURCE_INPUT_1_STR, demo::SOURCE_INPUT_1_ID);

        // ********************************************************
        // CREATE PROPERTIES USING CREATE/ADD METHODS
        // ********************************************************
        // To create device-specific properties, you must:
        //   1. Create the property using the imaqkit::IPropFactory object method
        //      appropriate for the data type.
        //   2. Add the property to the imaqkit::IEngine's device-specific property
        //      container using the imaqkit::IPropFactory's addProperty() method.
        //
        // The following section illustrate this procedure for each property data type.
        //
        // Properties with Enumerated Values
        // ---------------------------------
        // Create a property object for enumerated values by calling the createEnumProperty() method
        // of the imaqkit::IPropFactory object, specifying as arguments:
        //     - Name of the property
        //     - Default value of the property
        //     - Numeric ID associated with the value.
        // The method returns a handle to the new property.

        hProp = devicePropFact->createEnumProperty(demo::SYNC_INPUT_STR, demo::SYNC_INPUT_GREEN_STR, demo::SYNC_INPUT_GREEN_ID);

        // To add other enumerated values, call the addEnumValue() method of the imaqkit::IPropFactory
        // object, specifying as arguments:
        //     - Handle to the enumerated property object (created previously)
        //     - Value
        //     - Numeric ID associated with the value.
        devicePropFact->addEnumValue(hProp, demo::SYNC_INPUT_RED_STR, demo::SYNC_INPUT_RED_ID);
        devicePropFact->addEnumValue(hProp, demo::SYNC_INPUT_BLUE_STR, demo::SYNC_INPUT_BLUE_ID);
        devicePropFact->addEnumValue(hProp, demo::SYNC_INPUT_EXTERNAL_SYNC_STR, demo::SYNC_INPUT_EXTERNAL_SYNC_ID);        
        

        // Set the property to readonly while running.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::WHILE_RUNNING);
        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add the property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);
        
        hProp = devicePropFact->createEnumProperty(demo::FRAMERATE_INPUT_STR, demo::FRAMERATE_INPUT_1_STR, demo::FRAMERATE_INPUT_1_ID);

        // To add other enumerated values, call the addEnumValue() method of the imaqkit::IPropFactory
        // object, specifying as arguments:
        //     - Handle to the enumerated property object (created previously)
        //     - Value
        //     - Numeric ID associated with the value.
        devicePropFact->addEnumValue(hProp, demo::FRAMERATE_INPUT_2_STR, demo::FRAMERATE_INPUT_2_ID);
        devicePropFact->addEnumValue(hProp, demo::FRAMERATE_INPUT_3_STR, demo::FRAMERATE_INPUT_3_ID);
        devicePropFact->addEnumValue(hProp, demo::FRAMERATE_INPUT_4_STR, demo::FRAMERATE_INPUT_4_ID);
        devicePropFact->addEnumValue(hProp, demo::FRAMERATE_INPUT_5_STR, demo::FRAMERATE_INPUT_5_ID);

        // Make this property read-only while running, using the setPropReadOnly() method of
        // the imaqkit::IPropFactory object, specifying as arguments:
        //      - Handle to the property
        //      - One of these constants
        //           imaqkit::propreadonly::ALWAYS
        //           imaqkit::propreadonly::CURRENTLY
        //           imaqkit::propreadonly::NEVER
        //           imaqkit::propreadonly::NOT_CURRENTLY
        //           imaqkit::propreadonly::WHILE_RUNNING
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::WHILE_RUNNING);

        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);

        // Properties of type DOUBLE
        // -------------------------
        // Create an object for a property of class DOUBLE by calling the createDoubleProperty() method
        // of the imaqkit::IPropFactory object.
        hProp = devicePropFact->createDoubleProperty(demo::HUE_STR, demo::HUE_LOWER_LIMIT, demo::HUE_UPPER_LIMIT, demo::HUE_DEFAULT);
        // Set the property to read-only while running.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::WHILE_RUNNING);
        // Add the Property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);

        // Properties of type INT
        // -------------------------
        // Create an object for a property of class INT by calling the createIntProperty() method
        // of the imaqkit::IPropFactory object.
        hProp = devicePropFact->createIntProperty(demo::SATURATION_STR, demo::SATURATION_LOWER_LIMIT, demo::SATURATION_UPPER_LIMIT, demo::SATURATION_DEFAULT);
        // Set the property to read-only while running.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::WHILE_RUNNING);
        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add the property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);

        // Properties of type STRING
        // -------------------------
        // Create an object for a property of class STRING by calling the createStringProperty() method
        // of the imaqkit::IPropFactory object.
        hProp = devicePropFact->createStringProperty(demo::EXPERIMENT_SETUP_STR, demo::EXPERIMENT_DEFAULT_STR);
        // Set the property to readonly never.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::NEVER);
        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add the property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);

        // Properties with custom get functions attached.
        // -------------------------
        // These properties will have an imaqkit::IPropCustomGetFcn attached to them
        // when the videoinput object is created.  Since these properties are designed
        // to illustrate the use of the imaqkit::IPropCustomGetFcn, they will not
        // be settable.
        hProp = devicePropFact->createStringProperty(demo::TIMESTAMP_STRING_STR, "");
        // Set the property to read-only always.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::ALWAYS);
        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add the property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);

        hProp = devicePropFact->createIntProperty(demo::TIMESTAMP_INT_STR, 0);
        // Set the property to read-only always.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::ALWAYS);
        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add the property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);


        // TODO: make these properties be added without createPropFromIMDF which has been removed.

        // **********************************************************
        // CREATE PROPERTIES BY READING INFORMATION FROM AN IMDF FILE
        // **********************************************************
        // If you know the properties of a device in advance, you can store property information
        // in an IMDF file. An IMDF file is an XML file that defines object property information.
        // Use the includeXMLSection() method of the imaqkit::IPropFactory object to
        // read several properties from the file and create property objects.
        //
        // Note: You must place the IMDF file in the same directory as your
        // Adaptor DLL and it must have the same name as the adaptor, with
        // the .imdf extension. The toolbox checks for the existence of an IMDF
        // file when it searches for adaptors.
        //hProp = devicePropFact->createPropFromIMDF(demo::FRAMERATE_STR);
        //devicePropFact->addProperty(hProp);

    } else if (devID == demo::MONOCHROME_DEVICE_ID) {

        // **************************************************
        // IDENTIFY THE VIDEO SOURCE
        // **************************************************
        // Monochrome devices often support multiple input sources. Adaptors create a video
        // source for each source and let customers choose.
        sourceContainer->addAdaptorSource(demo::SOURCE_INPUT_1_STR, demo::SOURCE_INPUT_1_ID);
        sourceContainer->addAdaptorSource(demo::SOURCE_INPUT_2_STR, demo::SOURCE_INPUT_2_ID);
        sourceContainer->addAdaptorSource(demo::SOURCE_INPUT_3_STR, demo::SOURCE_INPUT_3_ID);
        sourceContainer->addAdaptorSource(demo::SOURCE_INPUT_4_STR, demo::SOURCE_INPUT_4_ID);
        sourceContainer->addAdaptorSource(demo::SOURCE_INPUT_5_STR, demo::SOURCE_INPUT_5_ID);
        sourceContainer->addAdaptorSource(demo::SOURCE_INPUT_6_STR, demo::SOURCE_INPUT_6_ID);

        // **************************************************
        // ADD HARDWARE TRIGGER CONFIGURATIONS
        //***************************************************
        hwTriggerInfo->addConfiguration(demo::RISING_EDGE_CONDITION_STR, demo::RISING_EDGE_ID, demo::TTL_SOURCE_STR, demo::TTL_SOURCE_ID);
        hwTriggerInfo->addConfiguration(demo::FALLING_EDGE_CONDITION_STR, demo::FALLING_EDGE_ID, demo::TTL_SOURCE_STR, demo::TTL_SOURCE_ID);
        hwTriggerInfo->addConfiguration(demo::RISING_EDGE_CONDITION_STR, demo::RISING_EDGE_ID, demo::OPTOTRIG_SOURCE_STR, demo::OPTOTRIG_SOURCE_ID);
        hwTriggerInfo->addConfiguration(demo::FALLING_EDGE_CONDITION_STR, demo::FALLING_EDGE_ID, demo::OPTOTRIG_SOURCE_STR, demo::OPTOTRIG_SOURCE_ID);


        // TODO: make these properties be added without createPropFromIMDF which has been removed.

	
        hProp = devicePropFact->createEnumProperty(demo::FRAMERATE_INPUT_STR, demo::FRAMERATE_INPUT_1_STR, demo::FRAMERATE_INPUT_1_ID);

        // To add other enumerated values, call the addEnumValue() method of the imaqkit::IPropFactory
        // object, specifying as arguments:
        //     - Handle to the enumerated property object (created previously)
        //     - Value
        //     - Numeric ID associated with the value.
        devicePropFact->addEnumValue(hProp, demo::FRAMERATE_INPUT_2_STR, demo::FRAMERATE_INPUT_2_ID);
        devicePropFact->addEnumValue(hProp, demo::FRAMERATE_INPUT_3_STR, demo::FRAMERATE_INPUT_3_ID);
        devicePropFact->addEnumValue(hProp, demo::FRAMERATE_INPUT_4_STR, demo::FRAMERATE_INPUT_4_ID);
        devicePropFact->addEnumValue(hProp, demo::FRAMERATE_INPUT_5_STR, demo::FRAMERATE_INPUT_5_ID);
        
        // Set the property to readonly while running.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::WHILE_RUNNING);
        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add the property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);

        // Create an object for a property of class INT by calling the createIntProperty() method
        // of the imaqkit::IAdaptorPropFactory object.
        hProp = devicePropFact->createIntProperty(demo::BRIGHTNESS_STR, demo::BRIGHTNESS_LOWER_LIMIT, demo::BRIGHTNESS_UPPER_LIMIT, demo::BRIGHTNESS_DEFAULT);
        // Set the property to read-only while running.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::WHILE_RUNNING);
        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add the property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);

        // Create an object for a property of class INT by calling the createIntProperty() method
        // of the imaqkit::IAdaptorPropFactory object.
        hProp = devicePropFact->createIntProperty(demo::CONTRAST_STR, demo::CONTRAST_LOWER_LIMIT, demo::CONTRAST_UPPER_LIMIT, demo::CONTRAST_DEFAULT);
        // Set the property to read-only while running.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::WHILE_RUNNING);
        // Add the property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add the property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);

        // Create an object for a property of class DOUBLE by calling the createDoubleProperty() method
        // of the imaqkit::IAdaptorPropFactory object.
        hProp = devicePropFact->createDoubleProperty(demo::SHARPNESS_STR, demo::SHARPNESS_LOWER_LIMIT, demo::SHARPNESS_UPPER_LIMIT, demo::SHARPNESS_DEFAULT);
        // Set the property to read-only while running.
        devicePropFact->setPropReadOnly(hProp, imaqkit::propreadonly::WHILE_RUNNING);
        // Add the Property to the device-specific property container.
        devicePropFact->addProperty(hProp);
        // Add property help text from the IMDF file.
        devicePropFact->addPropHelpFromIMDF(hProp);
        // **************************************************
        // CREATE PROPERTIES: The XML Method
        // **************************************************
        //
        // If you know the properties in advance, you can store
        // device-specific property information in XML format in
        // an IMDF file.
        //
        // Using methods of the imaqkit::IPropFactory class you can read
        // individual properties from the IMDF file or
        // entire sections that may contain multiple properties.
        //hProp = devicePropFact->createPropFromIMDF(demo::FRAMERATE_STR);
        //devicePropFact->addProperty(hProp);

        //hProp = devicePropFact->createPropFromIMDF(demo::BRIGHTNESS_STR);
        //devicePropFact->addProperty(hProp);

        //hProp = devicePropFact->createPropFromIMDF(demo::CONTRAST_STR);
        //devicePropFact->addProperty(hProp);

        //hProp = devicePropFact->createPropFromIMDF(demo::SHARPNESS_STR);
        //devicePropFact->addProperty(hProp);

    } else if (devID == demo::DIGITAL_FRAMEGRABBER_DEVICE_ID) {

        // ********************************************************
        // IDENTIFY THE VIDEO SOURCE
        // ********************************************************
        // Digital framegrabbers typically support a single input source.
        //
        sourceContainer->addAdaptorSource(demo::SOURCE_INPUT_1_STR, demo::SOURCE_INPUT_1_ID);

        // TODO: make these properties be added without createPropFromIMDF which has been removed.

        // ********************************************************
        // CREATE PROPERTIES: The XML Method
        // ********************************************************
        //

        // If you know the properties in advance, you can store
        // device-specific property information in XML format in
        // an IMDF file.
        //
        // Using methods of the imaqkit::IPropFactory class you can read
        // individual properties from the IMDF file or
        // entire sections that may contain multiple properties.

        //devicePropFact->includeIMDFSection(demo::DIGINPUT_STR);

    } else {
        //Throw an error in MATLAB.
        imaqkit::adaptorError(NULL, demo::ERRID_DEVICE_NOT_FOUND, demo::ERRMSG_DEVICE_NOT_FOUND);
    }
}

/**
 * createInstance() -- Exported function to return a new instance of an adaptor object.
 * The imaqkit::IEngine calls this function when a user attempts to create
 * a video input object by calling the VIDEOINPUT function at the MATLAB command line.
 *
 * @param engine: The imaqkit::IEngine passes a handle to an imaqkit::IEngine object to which the
 *                adaptor will interface.
 *
 * @param deviceInfo: The imaqkit::IEngine passes a handle to an imaqkit::IDeviceInfo object
 *                    identifying the target device. The handle will be one of
 *                    the IDeviceInfo objects created in getAvailHW().
 *
 * @param formatName: The imaqkit::IEngine passes a text string that specifies either one
 *                    of the fixed format names specified for the device in getAvailHW() or
 *                    a filename.
 *                    If it's a file name, it is the name of a device configuration
 *                    file (also known as a camera file).
 *                    The imaqkit::IEngine performs no processing on device configuration files.
 *                    Your adaptor should just pass this file to your device.
 *
 */

imaqkit::IAdaptor* createInstance(imaqkit::IEngine* engine,
                                  const imaqkit::IDeviceInfo* deviceInfo,
                                  const char* formatName)
{

    // Call your adaptor's constructor to create an instance, passing the
    // the same three arguments to the constructor.
    imaqkit::IAdaptor* adaptor = new DemoAdaptor(engine, deviceInfo, formatName);

    return adaptor;
}
