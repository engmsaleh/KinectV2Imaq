/**
 * @file:       IEnginePropPostSetListener.h
 *
 * Purpose:     Interface for implementing a post-SET listener.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IENGINEPROPPOSTSETLISTENER__HEADER__
#define __IMAQADAPTOR__IENGINEPROPPOSTSETLISTENER__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    // Forward class declaration.
    class IEnginePropInfo;

    /**
     * Class IEnginePropPostSetListener
     *
     * @brief:  Interface used to implement a property change
     *          listener, invoked after a property has been configured.
     *
     */
    class IEnginePropPostSetListener : public IMAQInterface
    {

      public:
        /**
         * Implementation used to virtualize the destructor.
         */
        virtual ~IEnginePropPostSetListener(void) {};

        /**
         * Callback function invoked by imaqkit::IEngine when the
         * property associated with this listener is changed.
         *
         * @param propertyInfo: Information on the property whose value was changed.
         * @param newValue: Property's new value.
         */
        virtual void notify(imaqkit::IEnginePropInfo* propertyInfo, void* newValue) = 0;
    };
}

#endif
