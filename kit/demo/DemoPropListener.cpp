/* Copyright 2006-2013 The MathWorks, Inc. */
/**
 * @file:       DemoPropListener.cpp
 *
 * Purpose:     Implements the methods of the DemoPropListener class.
 *
 *
 * $Authors:    JSH, CP, DT, KL $
 *
 * $Copyright: 2001-2010 The MathWorks, Inc.$
 *
 *
 */

#include "assert.h"

// TODO: delete
#include <string>

#include "DemoPropListener.h"

// TODO: delete
#include <iostream>

void DemoPropListener::notify(imaqkit::IPropInfo* propertyInfo, void* newValue)
{

    if (newValue) {
        // Store a handle to the imaqkit::IPropInfo object passed in.
        _propInfo = propertyInfo;

        // Cast newValue to its appropriate type by checking the property type.
        switch (_propInfo->getPropertyStorageType()) {

            // _lastDoubleValue contains the value for double properties.
          case imaqkit::propertytypes::DOUBLE:
            _lastDoubleValue = *reinterpret_cast< double*>(newValue);
            break;

            // _lastIntValue contains value for integer properties.
            // For enumerated properties, _lastIntValue returns the ID number
            // associated with the property value.
          case imaqkit::propertytypes::INT:
                _lastIntValue = *reinterpret_cast< int64_t*>(newValue);
                break;
            
            // _lastStrValue contains value for string properties.
          case imaqkit::propertytypes::STRING:
            _lastStrValue = reinterpret_cast< char*>(newValue);
            break;

            // Since this demo adaptor only uses double, integer, or string
            // value properties, anything else should cause an assertion error.
          default:
            assert(false && "Unhandled property data type. Need to add a new data type case.");
        }

        // Do not re-configure the property value unless the device is already
        // opened.
        if (_parent->isOpen()) {
            // Apply the value to the hardware.
            applyValue();
        }
    }
}

void DemoPropListener::applyValue()
{

    // If device cannot be configured while acquiring data, stop the device,
    // configure the feature, then restart the device.
    bool wasAcquiring = _parent->isAcquiring();
    if (wasAcquiring) {
        // Note: calling stop() will change the acquiring flag to false.
        // When the device tries to restart it invokes
        // DemoAdaptor::startCapture() which triggers notification for all
        // property listeners. Since the device is not acquiring data during
        // this second notification, the device will not stop and restart
        // again.
        _parent->stop();
    }


    // Get the property name.
    const char* propName = _propInfo->getPropertyName();

    // ************************************************
    // TODO Add code here to configure the property to its new value.
    // propName contains the name of the property to update.
    // The new value of that property is either stored in
    // _lastDoubleValue, _lastIntValue, or _lastStrValue depending on the
    // property type.
    // ************************************************

    // Restart the device if it was momentarily stopped to update the feature.
    if (wasAcquiring) {
        // Restart the device. This invokes DemoAdaptor::startCapture() which
        // invoke all property listeners.
        _parent->restart();
    }
}
