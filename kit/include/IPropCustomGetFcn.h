/**
 * @file:       IPropCustomGetFcn.h
 *
 * Purpose:     Interface for implementing a custom get function for device specific properties.
 *
 * $Authors:    Dave T. $
 *
 * $Copyright: 2009-2013 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IPROPCUSTOMGETFCN__HEADER__
#define __IMAQADAPTOR__IPROPCUSTOMGETFCN__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    // Forward class declaration.
    class IPropInfo;

    /**
     * Class IPropCustomGetFcn
     *
     * @brief:  Interface used to implement a function that is invoked
     *          whenever a property's value is queried.
     *
     */
    class IPropCustomGetFcn : public IMAQInterface
    {

      public:
        /**
         * Implementation used to virtualize the destructor.
         */
        virtual ~IPropCustomGetFcn(void) {};

        /**
         * Callback function invoked when the property value is queried.
         *
         * For scalar data types, ints and doubles, value is a pointer to
         * a variable of the corresponding data type.  In this case, the new
         * value can be assigned directly to the location pointed to by the
         * value pointer.
         *
         * For non-scalar data types, strings, double arrays, and integer arrays,
         * it is the responsibility of the implementing class to allocate sufficient
         * memory for the current property value using the new[] operator.  The engine
         * is responsible for calling delete[] once it is done with the memory.  An
         * example using a string property is:
         * <code>
         * char** returnStr = reinterpret_cast<char**>(value);
         * *retStr = new char[stringLength];
         * strcpy(*returnStr, currentPropetyValueString);
         * </code>
         *
         * This function will be called whenever the property value is accessed from
         * MATLAB.  For example, whenever the user uses the GET command to get the
         * value of the property this function will be executed.  However, this
         * function can be executed without explicit action from the user as well.
         * Therefore, if querying the function is expensive or time-consuming it
         * is advisable to use some sort of caching mechanism so that getting
         * property values does not incur excessive overhead.
         *
         * @param propertyInfo: Information on the property whose value was queried.
         * @param value: The property's current value.
         */
        virtual void getValue(imaqkit::IPropInfo* propertyInfo, void* value) = 0;
    };
}

#endif
