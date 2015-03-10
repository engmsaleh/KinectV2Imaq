/**
 * @file:       DemoSourceListener.cpp
 *
 * Purpose:     Implements the methods of the DemoSourceListener class.
 *
 *
 * $Authors:    JSH, CP, DT, KL $
 *
 * $Copyright 2001-2013 The MathWorks, Inc.
 *
 *
 **/

#include "DemoSourceListener.h"

// TODO: delete:
#include <iostream>

void DemoSourceListener::notify(imaqkit::IEnginePropInfo* propertyInfo, void* newValue)
{

    if (newValue) {
        // Get the ID of the new source requested by the user.
        _source = *static_cast<const int*>(newValue);

        // Do not re-configure the property value unless the device is already
        // opened.
        if (_parent->isOpen()) {
            // Apply the value to the hardware.
            applyValue();
        }
    }
}

void DemoSourceListener::applyValue(void)
{

    // If device cannot be configured while acquiring stop the device,
    // configure the source input, then restart the device.
    bool wasAcquiring = _parent->isAcquiring();
    if (wasAcquiring) {
        _parent->stop();
    }

    // ************************************************
    // TODO Include code here to update the device to the
    // source specified by the value of _source.
    // ************************************************

    // Restart the device if it was momentarily stopped to update the source.
    if (wasAcquiring) {
        _parent->restart();
    }
}
