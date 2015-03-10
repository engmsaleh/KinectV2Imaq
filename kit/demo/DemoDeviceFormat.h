/**
 * @file:       DemoDeviceFormat.h
 *
 * Purpose:     Class declaration for DemoDeviceFormat
 *
 *
 * $Authors:    JSH, CP, DT, KL $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */

#ifndef __DEMO_DEVICEFORMAT_HEADER__
#define __DEMO_DEVICEFORMAT_HEADER__

#include "mwadaptorimaq.h"

/**
 * Class DemoDeviceFormat
 *
 * @brief: Keeps all format-related data together, including format name,
 *         frame type, height, width, and number of bands.
 *         Inherits from the imaqkit::IMAQInterface class.
 *         Objects of this class are instantiated and populated in the
 *         getAvailHW() call.
 */

class DemoDeviceFormat : public imaqkit::IMAQInterface
{

  public:

    // *******************************************************************
    // CONSTRUCTOR/DESTRUCTOR
    // *******************************************************************
    DemoDeviceFormat(void);
    virtual ~DemoDeviceFormat(void);

    // *******************************************************************
    // METHODS FOR ACCESSING VIDEO FORMAT INFORMATION.
    // *******************************************************************
    /// Retrieve height.
    int getFormatHeight() const;

    /// Retrieve width.
    int getFormatWidth() const;

    /// Retrieve number of bands.
    int getFormatNumBands() const;

    /// Retrieve frame type.
    imaqkit::frametypes::FRAMETYPE getFormatFrameType() const;


    // *******************************************************************
    // METHODS FOR SAVING VIDEO INFORMATION.
    // *******************************************************************
    /// Save video format height.
    void setFormatHeight(int value);

    /// Save video format width.
    void setFormatWidth(int value);

    /// Save number of bands.
    void setFormatNumBands(int value);

    /// Save frame type.
    void setFormatFrameType(imaqkit::frametypes::FRAMETYPE value);

  private:
    /// The height of the frame in pixels
    int _formatHeight;

    /// The width of the frame in pixels
    int _formatWidth;

    /// The number of bands of data returned
    int _formatNumBands;

    /// The frame type
    imaqkit::frametypes::FRAMETYPE _formatFrameType;
};

#endif
