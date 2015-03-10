/**
 * @file:       DemoSourceListener.h
 *
 * Purpose:     Class declaration for DemoSourceListener
 *
 *
 * $Authors:    JSH, CP, DT, KL $
 *
 * $Copyright 2001-2009 The MathWorks, Inc.$
 *
 *
 **/

#ifndef __DEMO_SOURCE_LISTENER_HEADER__
#define __DEMO_SOURCE_LISTENER_HEADER__

#include "mwadaptorimaq.h"
#include "DemoAdaptor.h"

/**
 * Class DemoSourceListener
 *
 * @brief:  Listens for changes in SelectedSource.
 *
 */
class DemoSourceListener : public imaqkit::IEnginePropPostSetListener
{

  public:

    //**************************************
    //* CONSTRUCTOR/DESTRUCTOR
    //**************************************
    /**
     * Constructor for DemoSourceListener class.
     *
     * @param parent: Handle to the instance of the IAdaptor class
     *                that is the parent of this object.
     */
  DemoSourceListener(DemoAdaptor* parent) : _parent(parent) {};

    // Destructor
    virtual ~DemoSourceListener(void) {};

    // *******************************************************************
    // METHODS FOR CONFIGURING AND UPDATING DEMO SOURCE INPUTS.
    // *******************************************************************
    /**
     * This is the method the engine calls when the value of the SelectedSource
     * property changes. notify() casts the new source value to the appropriate type
     * and then calls the DemoSourceListener::applyValue() method to configure the
     * new source. To set up a listener for other properties, use the DemoPropListener
     * object.
     *
     * @param propertyInfo: Property information object.
     * @param newValue: New source ID value.
     *
     * @return void:
     */
    virtual void notify(imaqkit::IEnginePropInfo* propertyInfo, void* newValue);

  private:

    /**
     * Update and configure the specified property.
     *
     * @return void:
     */
    virtual void applyValue(void);

    /// The instance of the parent class that created this listener.
    DemoAdaptor* _parent;

    /// The new source id requested by the user.
    int _source;
};

#endif
