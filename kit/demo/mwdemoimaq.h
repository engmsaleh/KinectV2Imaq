/**
 * @file:       mwdemoimaq.h
 *
 * Purpose:     Demo adaptor namespace for storing adaptor-specific information.
 *
 *
 * $Authors:    JSH, CP, DT, KL $
 *
 * Copyright 2006-2013 The MathWorks, Inc.
 *
 *
 */

#ifndef __MWDEMOIMAQ_HEADER__
#define __MWDEMOIMAQ_HEADER__

#include "mwadaptorimaq.h"
#ifdef _WIN32
#include <windows.h>
#else
#endif

namespace demo
{

    // ********** Demo Adaptor Information **********
    /// Return string for DemoAdaptor::getDriverDescription().
    const char* const DRIVER_DESCRIPTION_STR = "Demo Device Driver";

    /// Return string for DemoAdaptor::getDriverVersion().
    const char* const DRIVER_VERSION_STR = "Version 1.0 (Beta 1)";

    // ********** Demo Device Information **********
    const char* const COLOR_DEVICE_STR = "Color Device";
    const char* const MONOCHROME_DEVICE_STR = "Monochrome Device";
    const char* const DIGITAL_HARDWARE_STR = "Digital Device";

    enum
    {
        RGB_DEVICE_ID = 1,
        MONOCHROME_DEVICE_ID = 2,
        DIGITAL_FRAMEGRABBER_DEVICE_ID = 3
    };

    /// Default width if no image format is found.
    const int DEMO_DEFAULT_WIDTH = 640;
    const int DEMO_DEFAULT_HEIGHT = 480;
    const int DEMO_DEFAULT_NUMBER_OF_BANDS = 3;

    // ********** Color Device Information **********
    /// RGB Format Information
    const char* const RGB_FORMAT_STR = "RGB_NTSC";
    const int RGB_FORMAT_ID = 0;
    const int RGB_FORMAT_WIDTH = 640;
    const int RGB_FORMAT_HEIGHT = 480;
    const int RGB_FORMAT_BANDS = 3;

    /// RGB SyncInput Enum Property.
    const char* const SYNC_INPUT_STR = "SyncInput";
    const char* const SYNC_INPUT_GREEN_STR = "green";
    const char* const SYNC_INPUT_RED_STR = "red";
    const char* const SYNC_INPUT_BLUE_STR = "blue";
    const char* const SYNC_INPUT_EXTERNAL_SYNC_STR = "externalSync";

    enum
    {
        SYNC_INPUT_GREEN_ID = 1,
        SYNC_INPUT_RED_ID = 2,
        SYNC_INPUT_BLUE_ID = 3,
        SYNC_INPUT_EXTERNAL_SYNC_ID = 4
    };

    /// FrameRate Enum Property
    const char* const FRAMERATE_INPUT_STR = "FrameRate";
    
    const char* const FRAMERATE_INPUT_1_STR = "30";
    const char* const FRAMERATE_INPUT_2_STR = "15";
    const char* const FRAMERATE_INPUT_3_STR = "7.5";
    const char* const FRAMERATE_INPUT_4_STR = "3.75";
    const char* const FRAMERATE_INPUT_5_STR = "1.75";
    
    enum
    {
        FRAMERATE_INPUT_1_ID = 1,
        FRAMERATE_INPUT_2_ID = 2,
        FRAMERATE_INPUT_3_ID = 3,
        FRAMERATE_INPUT_4_ID = 4,
        FRAMERATE_INPUT_5_ID = 5
    };    
    
    /// RGB Hue Double Property.
    const char* const HUE_STR = "Hue";
    const double HUE_LOWER_LIMIT = 0.0;
    const double HUE_UPPER_LIMIT = 1.0;
    const double HUE_DEFAULT = .50;

    /// RGB Saturation Int Property.
    const char* const SATURATION_STR = "Saturation";
    const int64_t SATURATION_LOWER_LIMIT = 0;
    const int64_t SATURATION_UPPER_LIMIT = 100;
    const int64_t SATURATION_DEFAULT = 50;

    /// RGB ExperimentSetup String Property.
    const char* const EXPERIMENT_SETUP_STR = "ExperimentSetup";
    const char* const EXPERIMENT_DEFAULT_STR = "Default Lab Setup";

    /// SVideo Format
    const char* const SVIDEO_FORMAT_STR = "S-Video";
    const int SVIDEO_FORMAT_ID = 1;
    const int SVIDEO_FORMAT_WIDTH = 160;
    const int SVIDEO_FORMAT_HEIGHT = 120;
    const int SVIDEO_FORMAT_BANDS = 3;

    /// Properties from XML
    const char* const FRAMERATE_STR = "FrameRate";

    /// Properties with custom get functions
    const char* const TIMESTAMP_STRING_STR = "TimestampString";
    const char* const TIMESTAMP_INT_STR = "TimestampInteger";

    // ********** Monochrome Device Information **********
    /// RS170 Format Information
    const char* const RS170_FORMAT_STR = "RS170";
    const int RS170_FORMAT_ID = 0;
    const int RS170_FORMAT_WIDTH = 640;
    const int RS170_FORMAT_HEIGHT = 480;
    const int RS170_FORMAT_BANDS = 1;

    /// CCIR Format Information
    const char* const CCIR_FORMAT_STR = "CCIR";
    const int CCIR_FORMAT_ID = 1;
    const int CCIR_FORMAT_WIDTH = 768;
    const int CCIR_FORMAT_HEIGHT = 576;
    const int CCIR_FORMAT_BANDS = 1;

    /// Monochrome Device Source Information
    const char* const SOURCE_INPUT_1_STR = "input1";
    const char* const SOURCE_INPUT_2_STR = "input2";
    const char* const SOURCE_INPUT_3_STR = "input3";
    const char* const SOURCE_INPUT_4_STR = "input4";
    const char* const SOURCE_INPUT_5_STR = "input5";
    const char* const SOURCE_INPUT_6_STR = "input6";

    enum
    {
        SOURCE_INPUT_1_ID = 1,
        SOURCE_INPUT_2_ID = 2,
        SOURCE_INPUT_3_ID = 3,
        SOURCE_INPUT_4_ID = 4,
        SOURCE_INPUT_5_ID = 5,
        SOURCE_INPUT_6_ID = 6
    };

    /// Monochrome Device Trigger Information
    const char* const TTL_SOURCE_STR = "TTL";
    const char* const OPTOTRIG_SOURCE_STR = "OptoTrig";

    enum
    {
        TTL_SOURCE_ID = 1,
        OPTOTRIG_SOURCE_ID = 2
    };

    const char* const FALLING_EDGE_CONDITION_STR = "fallingEdge";
    const char* const RISING_EDGE_CONDITION_STR = "risingEdge";

    enum
    {
        FALLING_EDGE_ID = 1,
        RISING_EDGE_ID = 2
    };

    /// Properties from XML
    const char* const BRIGHTNESS_STR = "Brightness";
	 const int64_t BRIGHTNESS_LOWER_LIMIT = 0;
    const int64_t BRIGHTNESS_UPPER_LIMIT = 255;
    const int64_t BRIGHTNESS_DEFAULT = 128;

    const char* const CONTRAST_STR = "Contrast";
     const int64_t CONTRAST_LOWER_LIMIT = 0;
    const int64_t CONTRAST_UPPER_LIMIT = 255;
    const int64_t CONTRAST_DEFAULT = 128;
	
	const char* const SHARPNESS_STR = "Sharpness";
	const double SHARPNESS_LOWER_LIMIT = 0.0;
    const double SHARPNESS_UPPER_LIMIT = 1.0;
    const double SHARPNESS_DEFAULT = .50;

    // ********** Digital Hardware Information **********
    /// Property to be added from XML section.
    const char* const DIGINPUT_STR = "digInput";

    // ********** Other information **********
    /// Generated image data offset value.
    /// The higher the number the faster the shifting from right to left looks.
    const int IMAGE_DATA_OFFSET = 2;

    /// This is the value in milliseconds that the image generator pauses to
    /// make the frame rate more realistic.
    const int IMAGE_FRAME_PAUSE_TIME = 30;

#ifdef _WIN32
    /// Time, in milliseconds, given for an object to finish.
    /// Used when calling WaitForSingleObject() in DemoAdaptor::closeDevice().
    const DWORD SINGLE_OBJECT_WAIT_TIME = 10000;
#endif

    // ********** ERROR IDs and MESSAGES **********
    /// Error ID and Message when the device is not found in getDeviceAttributes().
    const char* const ERRID_DEVICE_NOT_FOUND = "imaq:demo:devicenotfound";
    const char* const ERRMSG_DEVICE_NOT_FOUND = "Unable to find the image acquisition device.";

    /// To be removed when a routine for displaying non-warning messages in MATLAB is implemented.
    const char* const WARNID_CONFIGURING_PROPERTY = "imaq:demo:configuringproperty";
};

#endif
