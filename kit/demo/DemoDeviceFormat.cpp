/**
 * @file:       DemoDeviceFormat.cpp
 *
 * Purpose:     Implements the methods of the DemoDeviceFormat class.
 *
 *
 * $Authors:    JSH, CP, DT, KL $
 *
 * $Copyright 2001-2012 The MathWorks, Inc.$
 *
 *
 */

#include "DemoDeviceFormat.h"

//******************************************
//  CONSTRUCTOR/DESTRUCTOR
//******************************************
// Initialize the data members of the class.
DemoDeviceFormat::DemoDeviceFormat(void) :
    _formatHeight(0), _formatWidth(0), _formatNumBands(0) {}

DemoDeviceFormat::~DemoDeviceFormat() {}

// Get/set frame height.
void DemoDeviceFormat::setFormatHeight(int value)
{
    _formatHeight = value;
}

int DemoDeviceFormat::getFormatHeight() const
{
    return _formatHeight;
}

// Get/set frame width.
void DemoDeviceFormat::setFormatWidth(int value)
{
    _formatWidth = value;
}

int DemoDeviceFormat::getFormatWidth() const
{
    return _formatWidth;
}

// Get/set number of bands.
void DemoDeviceFormat::setFormatNumBands(int value)
{
    _formatNumBands = value;
}

int DemoDeviceFormat::getFormatNumBands() const
{
    return _formatNumBands;
}

// Get/set frame type.
void DemoDeviceFormat::setFormatFrameType(imaqkit::frametypes::FRAMETYPE value)
{
    _formatFrameType = value;
}

imaqkit::frametypes::FRAMETYPE DemoDeviceFormat::getFormatFrameType() const
{
    return _formatFrameType;
}
