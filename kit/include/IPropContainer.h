/**
 * @file:       IPropContainer.h
 *
 * Purpose:     Container interface for storing properties.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2013 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IPROPCONTAINER__HEADER__
#define __IMAQADAPTOR__IPROPCONTAINER__HEADER__

#include <stdint.h>
#include "IMAQInterface.h"

namespace imaqkit
{

    // Forward declarations.
    class IPropInfo;
    class IPropPostSetListener;
    class IPropCustomGetFcn;
    class IPropCommandFcn;

    /**
     * Class IPropContainer
     *
     * @brief:  Container interface for storing properties.
     *
     * Interface providing adaptors access to property configurations,
     * information, and change notifications.
     *
     */
    class IPropContainer : public imaqkit::IMAQInterface
    {

      public:
        //***********************************************************
        // PROPERTY VALUE MANAGEMENT.
        //***********************************************************
        /**
         * Configure the current value for the property specified.
         *
         * Note, the property container configures a property's value
         * by storing a copy of the value provided.
         *
         * The property name specified is case-sensitive.
         *
         * If no property exists with the given name, no operation is
         * performed.
         *
         * An optional flag can be used to indicate if the new property
         * value being provided should be checked against the property
         * constraints and data type specified when the property was
         * defined.
         *
         * If the new property value is determined to be invalid, an
         * exception is thrown and handled by the toolbox engine. Otherwise,
         * a copy of the value is stored in the container.
         *
         * By default, the property values provided are checked against the
         * property's definition.
         *
         * @param propertyName: Name of the property.
         * @param newValue: New value to store for the property.
         * @param doInternalCheck: Optional flag indicating if the new value should be checked.
         *
         */
        virtual void setPropValue(const char* propertyName, const void* newValue, bool doInternalCheck = true) = 0;

        /**
         * Check the validity of a given value for the property specified.
         *
         * The property name specified is case-sensitive.
         *
         * If no property exists with the given name, the function returns a false.
         *
         * If the property is an enumeration type, the given value must be
         * the ID for one of the property's enumeration values in order for it
         * to be considered valid.
         *
         * @param propertyName: Name of the property.
         * @param value: Value to check.
         *
         * @return bool: True if the value is valid for the given property.
         */
        virtual bool checkPropValue(const char* propertyName, const void* value) const = 0;

        /**
         * Return the current value being stored in the container
         * for the property specified.
         *
         * The property name specified is case-sensitive.
         *
         * The value returned is the internal copy stored by the toolbox
         * engine, not a new copy.
         *
         * If there is no property with the specified name, NULL is returned.
         *
         * @param propertyName: Name of the property.
         *
         * @return void* : Current property value, or NULL.
         */
        virtual void* getPropValue(const char* propertyName) const = 0;

        /**
         * Return as an integer the current value being stored in
         * the container for the property specified.
         *
         * If the actual value is greater than INT_MAX, INT_MAX is
         * returned.
         *
         * If the actual value is less than INT_MIN, INT_MIN is
         * returned.
         *
         * The property name specified is case-sensitive.
         *
         * @param propertyName: Name of the property.
         *
         * @return int: Current property value.
         */
        virtual int getPropValueAsInt(const char* propertyName) const = 0;

        /**
         * Return as a double the current value being stored in the
         * container for the property specified.
         *
         * The property name specified is case-sensitive.
         *
         * @param propertyName: Name of the property.
         *
         * @return double: Current property value
         */
        virtual double getPropValueAsDouble(const char* propertyName) const = 0;

        /**
         * Return the current value being stored in the property container
         * as a string.
         *
         * The property name provided is case sensitive.
         *
         * @param propertyName: Name of the property.
         *
         * @return const char* : Current property value
         */
        virtual const char* getPropValueAsString(const char* propertyName) const = 0;

        //***********************************************************
        // GENERAL PROPERTY INFORMATION.
        //***********************************************************

        /**
         * Return true if the given property is in the
         * property container, otherwise return FALSE.
         *
         * The property name specified is case-sensitive.
         *
         * @param propertyName: Name of the property.
         *
         * @return bool: True if property name matches a property in container.
         */
        virtual bool isPropertyAvailable(const char* propertyName) const = 0;

        /**
         * Return information about the property specified.
         *
         * The property name specified is case-sensitive.
         *
         * If the property does not exist, NULL is returned.
         *
         * @param propertyName: Name of the property.
         *
         * @return imaqkit::IPropInfo*: Property information interface, or NULL.
         */
        virtual imaqkit::IPropInfo* getIPropInfo(const char* propertyName) const = 0;

        /**
         * Return the number of properties stored in the container.
         *
         * @return int : Total number of properties in the container.
         */
        virtual int getNumberProps() const = 0;

        /**
         * Fill the array provided with names of all the properties
         * stored in the container. It is the caller's responsibility
         * to allocate an array big enough to hold all the names.
         *
         * @param list: Array to fill with property names.
         *
         */
        virtual void getPropNames(const char** list) const = 0;

        //***********************************************************
        // ENUMERATED PROPERTY INFORMATION.
        //***********************************************************

        /**
         * Return the current string value of the enumerated
         * property specified.
         *
         * The property name specified is case-sensitive.
         *
         * If the property is not an existing enumerated property, NULL
         * is returned.
         *
         * @param propertyName: Name of the enumerated property.
         *
         * @return const char*: The current enumerated string value, or NULL.
         */
        virtual const char* getEnumString(const char* propertyName) const = 0;

        /**
         * Return the string value corresponding to the
         * enumerated string identifier specified.
         *
         * The property name specified is case-sensitive.
         *
         * If the property is not an existing enumerated property, NULL
         * is returned.
         *
         * If a NULL enumerated string identifier is provided, the current
         * string value for the property is returned.
         *
         * @param propertyName: Name of the enumerated property.
         * @param enumStrID: Identifier for one of the enumerated property's string values (pointer to int or NULL).
         *
         * @return const char*: The enumerated string value, or NULL.
         */
        virtual const char* getEnumString(const char* propertyName, const int* const enumStrID) const = 0;

        //***********************************************************
        // COMMAND FUNCTIONS.
        //***********************************************************

        /**
         * Associate the specified command function object with the
         * command property specified.
         *
         * The command name specified is case-sensitive.
         *
         * If no command exists with the given command property name, the
         * function is not added and false is returned. If this occurs, it
         * is the responsibility of the caller to destroy the function.
         *
         * If a command property exists with the specified name, any existing
         * command function will be replaced with the function being passed
         * in to the function.
         *
         * If a command propert exists with the specified name, the listener
         * is added and true is returned. Upon destruction of the end user's
         * VIDEOINPUT object, the function is destroyed automatically.
         *
         * @param commandName: Name of the command property.
         * @param commandFcn: Pointer to a custom command function instance.
         *
         * @return bool: True if the function was added, false otherwise.
         */
        virtual bool setCommandFcn(const char* propertyName, imaqkit::IPropCommandFcn* commandFcn) = 0;

        //***********************************************************
        // PROPERTY LISTENER FUNCTIONS.
        //***********************************************************

        /**
         * Associate the specified property custom get function object with the
         * property specified.
         *
         * The property name specified is case-sensitive.
         *
         * If no property exists with the given property name, the listener
         * is not added and false is returned. If this occurs, it is the
         * responsibility of the caller to destroy the listener.
         *
         * If a property exists with the specified name, any existing custom get
         * function will be replaced with the function being passed in to the function.
         *
         * If a property exists with the specified name, the listener is added
         * and true is returned. Upon destruction of the end user's VIDEOINPUT
         * object, the listener is destroyed automatically.
         *
         * @param propertyName: Name of the property.
         * @param getFcn: Pointer to a custom get function instance.
         *
         * @return bool: True if the getter was added, false otherwise.
         */
        virtual bool setCustomGetFcn(const char* propertyName, imaqkit::IPropCustomGetFcn* getFcn) = 0;

        /**
         * Associate the specified property post-set listener object with the
         * property specified.
         *
         * The property name specified is case-sensitive.
         *
         * If no property exists with the given property name, the listener
         * is not added and false is returned. If this occurs, it is the
         * responsibility of the caller to destroy the listener.
         *
         * If a property exists with the specified name, the listener is added
         * and true is returned. Upon destruction of the end user's VIDEOINPUT
         * object, the listener is destroyed automatically.
         *
         * Post-set listeners are notified *after* the property value stored in
         * the container is updated, i.e. post-set. Listener's are invoked with
         * the new value provided by the user, which is the internal copy stored
         * in the container.
         *
         * @param propertyName: Name of the property.
         * @param setNotifier: Pointer to a listener instance.
         *
         * @return bool: True if the listener was added, false otherwise.
         */
        virtual bool addListener(const char* propertyName, imaqkit::IPropPostSetListener* setNotifier) = 0;

        /**
         * Request that all the properties in the container notify their
         * listeners of their current value.
         */
        virtual void notifyAllListeners(void) = 0;

        /**
         * Request that the property specified notify its
         * listeners of its current value.
         *
         * The property name specified is case-sensitive.
         *
         * Note, notifying the listeners of the SelectedSourceName
         * VIDEINPUT property will not only trigger the listeners
         * associated with SelectedSourceName property, but will
         * also trigger the listeners for each VIDEOSOURCE property
         * of the newly selected source.
         *
         * This is an intentional behavior because changing the
         * selected source requires all device (source) level
         * properties to be notified that the selected source has
         * changed.
         *
         * Thus, when you call the listeners of the SelectedSourceName
         * property, you are in essence also calling all the listeners
         * of the device-level properties.
         *
         * In this particular case, you do not need to call the listeners
         * of the device-specific properties. It would be sufficient to
         * just invoke the SelectedSourceName listener.
         *
         * @param propertyName: Property name.
         */
        virtual void notifyListeners(const char* propertyName) = 0;
    };
}

#endif
