/**
 * @file:       DemoPropListener.h
 *
 * Purpose:     Class declaration for DemoPropListener.
 *
 *
 * $Authors:    JSH, CP, DT, KL $
 *
 * $Copyright 2001-2009 The MathWorks, Inc.$
 *
 *
 */
#ifndef __DEMO_PROP_LISTENER_HEADER__
#define __DEMO_PROP_LISTENER_HEADER__

#include <string>
#include "mwadaptorimaq.h"
#include "DemoAdaptor.h"
#include "mwdemoimaq.h"

/**
 * Class DemoPropListener
 *
 * @brief:  Listens for changes in device-specific properties.
 *
 */
class DemoPropListener : public imaqkit::IPropPostSetListener
{

  public:

    // **************************************
    // CONSTRUCTOR/DESTRUCTOR
    // **************************************
    /**
     * Constructor for DemoPropListener class.
     *
     * @param parent: Handle to the instance of the IAdaptor class
     *                that is the parent of this object.
     */
  DemoPropListener(DemoAdaptor* parent): _parent(parent) {}
    virtual ~DemoPropListener() {};

    // *******************************************************************
    // METHODS FOR CONFIGURING AND UPDATING DEMO FEATURE PROPERTY VALUES.
    // *******************************************************************
    /**
     * This is the method the engine calls when a property value
     * changes. notify() casts the new property value to the appropriate
     * type and then calls the DemoPropListener::applyValue() method to
     * configure the property.
     *
     * @param propertyInfo: The property information object.
     * @param newValue: The new value of the property.
     *
     * @return void:
     */
    virtual void notify(imaqkit::IPropInfo* propertyInfo, void* newValue);

  private:

    /**
     * applyValue: Find the property to update and configure it.
     *
     * @return void:
     */
    virtual void applyValue(void);

    /// The instance of the parent class that created this listener.
    DemoAdaptor* _parent;

    /// Property Information object.
    imaqkit::IPropInfo* _propInfo;

    /// The new value for integer properties.
    int64_t _lastIntValue;

    /// The new value for double properties.
    double _lastDoubleValue;

    /// The new value for string properties.
    std::string _lastStrValue;
};

#endif
