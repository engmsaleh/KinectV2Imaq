/**
 * @file:       IAdaptorPropCommandFcn.h
 *
 * Purpose:     Interface for implementing a command function for device specific properties.
 *
 * $Authors:    mjones $
 *
 * $Copyright: 2012 The MathWorks, Inc.$
 *
 */
#ifndef __IMAQADAPTOR__IPROPCOMMANDFCN__HEADER__
#define __IMAQADAPTOR__IPROPCOMMANDFCN__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    // Forward class declaration.
    class IPropInfo;

    /**
     * Class IAdaptorPropCommandFcn
     *
     * @brief:  Interface used to implement a function that is invoked
     *          whenever a property's command is invoked.
     *
     */
    class IPropCommandFcn : public IMAQInterface
    {

      public:
        /**
         * Implementation used to virtualize the destructor.
         */
        virtual ~IPropCommandFcn(void) {};

        /**
         * Callback function invoked when the property's command is invoked.
         *
         * @param propertyInfo: Information on the property whose value was queried.
         */
        virtual void performCommand(const imaqkit::IPropInfo* propertyInfo) = 0;
    };
}

#endif
