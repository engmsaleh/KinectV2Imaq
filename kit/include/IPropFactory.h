/**
 * @file:       IPropFactory.h
 *
 * Purpose:     Factory for creating property information.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2013 The MathWorks, Inc.$
 *
 *
 */

#ifndef __IMAQADAPTOR__IPROPFACTORY__HEADER__
#define __IMAQADAPTOR__IPROPFACTORY__HEADER__

#include <stdint.h>
#include "IMAQInterface.h"

namespace imaqkit
{

    namespace propreadonly
    {
        /*
         * Property read-only option indicating a property is always read-only
         * (this is intended for properties that would not change their mutability).
         */
        const char* const ALWAYS = "always";

        /*
         * Property read-only option indicating a property is read-only at the
         * current time (this is intended for properties that might change their mutability).
         */
        const char* const CURRENTLY = "currently";

        /*
         * Property read-only option indicating a property is writable at the
         * current time (this is intended for properties that might change their mutability).
         */
        const char* const NOT_CURRENTLY = "notCurrently";

        /*
         * Property read-only option indicating a property is never read-only
         * (this is intended for properties that would not change their mutability).
         */
        const char* const NEVER = "never";

        /*
         * Property read-only option indicating a property is only
         * read-only when the Running property is 'on' (this is intended
         * for properties that would not change their mutability).
         */
        const char* const WHILE_RUNNING = "whileRunning";
    }

    namespace visibility
    {
        enum levels {BEGINNER, INTERMEDIATE, ADVANCED, INVISIBLE};
    }

    /**
     * Class IPropFactory
     *
     * @brief:  Mechanism by which properties can be defined and stored.
     *
     * This imaqkit::IPropFactory class enables adaptors to define and add
     * device specific properties to the imaqkit::IEngine when the
     * getDeviceAttributes function is invoked by the toolbox engine.
     *
     */
    class IPropFactory : public imaqkit::IMAQInterface
    {

      public:
        // *******************************************************************
        // PROPERTY CREATION.
        // *******************************************************************
        /**
         * Create a new property definition which is a vector
         * of doubles.  Each double must have a default value.
         *
         * @param propertyName: Property's name.
         * @param numElements: The number of elements in the array
         * @param defaultValues: The default values.
         */
        virtual void* createDoubleArrayProperty(const char* propertyName,
                                                size_t numElements, double* defaultValues) = 0;

        /**
         * Create a new property definition constrained to be a 1x2
         * array of doubles bounded by a minimum and maximum value.
         *
         * @param propertyName: Property's name.
         * @param lowerBound: Minimum value for this property.
         * @param upperBound: Maximum value for this property.
         * @param firstDefaultValue: Default value for the first value.
         * @param secondDefaultValue: Default value for the second value.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createDoublePairProperty(const char* propertyName, double lowerBound, double upperBound,
                                               double firstDefaultValue, double secondDefaultValue) = 0;

        /**
         * Create a double property with lower and upper bounds.
         *
         * @param propertyName: Name of the property.
         * @param lowerBound: Minimum valid value.
         * @param upperBound: Maximum valid value.
         * @param defaultValue: Default property value.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createDoubleProperty(const char* propertyName, double lowerBound, double upperBound, double defaultValue) = 0;

        /**
         * Create a double property with no lower or upper bounds.
         *
         * @param propertyName: Name of the property.
         * @param defaultValue: Default property value.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createDoubleProperty(const char* propertyName, double defaultValue) = 0;

        /**
         * Create a new property definition which is a vector
         * of ints.  Each int must have a default value.
         *
         * @param propertyName: Property's name.
         * @param numElements: The number of elements in the array
         * @param defaultValues: The default values.
         * @param increment: Default property increment.
         */
        virtual void* createIntArrayProperty(const char* propertyName,
                                             size_t numElements, int* defaultValues, int increment = 1) = 0;

        /**
         * Create a new property definition constrained to be a
         * 1x2 array of integers bounded by a minimum and maximum value.
         *
         * @param propertyName: Property's name.
         * @param lowerBound: Minimum value for this property.
         * @param upperBound: Maximum value for this property.
         * @param firstDefaultValue: Default value for the first value.
         * @param secondDefaultValue: Default value for the second value.
         * @param increment: Default property increment.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createIntPairProperty(const char* propertyName, int lowerBound, int upperBound,
                                            int firstDefaultValue, int secondDefaultValue, int increment = 1) = 0;

        /**
         * Create an integer property with lower and upper bounds.
         *
         * @param propertyName: Name of the property.
         * @param lowerBound: Minimum valid value.
         * @param upperBound: Maximum valid value.
         * @param defaultValue: Default property value.
         * @param increment: Default property increment.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createIntProperty(const char* propertyName, int lowerBound, int upperBound, int defaultValue, int increment = 1) = 0;

        /**
         * Create an integer property with no lower or upper bounds.
         *
         * @param propertyName: Name of the property.
         * @param defaultValue: Default property value.
         * @param increment: Default property increment.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createIntProperty(const char* propertyName, int defaultValue, int increment = 1) = 0;

        /**
         * Create a string property.
         *
         * @param propertyName: Name of the property.
         * @param defaultValue: Default property value.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createStringProperty(const char* propertyName, const char* defaultValue) = 0;

        /**
         * Create a command. Commands are added similar to properties, but
         * are callable on the videosource object by the user instead of
         * set with a value as other properties are.
         *
         * @param commandName: Command name.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createCommand(const char* commandName) = 0;

        /**
         * Create an enumerated string property.
         *
         * @param propertyName: Name of the property.
         * @param defaultEnumStr: Default enum string value.
         * @param defaultEnumID: Default unique enum ID. Each string should have a unique ID associated with it.
         *
         * @return void*: Handle to a property definition.
         */
        virtual void* createEnumProperty(const char* propertyName, const char* defaultEnumStr, int defaultEnumID) = 0;

        /**
         * Add a new enumerated value to an enumerated property that was defined.
         *
         * @param propHandle: Handle to a property definition.
         * @param value: New enum string value.
         * @param ID: Unique enum ID. Each string should have a unique ID associated with it.
         *
         */
        virtual void addEnumValue(void* propHandle, const char* value, int ID) = 0;

        // ***********************************************************
        // PROPERTY REGISTRATION.
        // ***********************************************************

        /**
         * Adds a property definition handle to the property container.
         *
         * @param propHandle: Handle to a property definition.
         */
        virtual void addProperty(void* propHandle) = 0;

        /**
         * Adds a property definition handle to the property container.
         *
         * In order for adaptors to easily identify a property, a
         * property identifier can be associated when the property
         * definition handle is added.
         *
         * This avoids adaptors from having to do string comparisons,
         * as well as leverage any hardware SDK identifiers that can
         * be used to uniquely identify a hardware device setting.
         *
         * @param propHandle: Handle to a property definition.
         * @param id: The property identifier.
         */
        virtual void addProperty(void* propHandle, int id) = 0;

        // ***********************************************************
        // PROPERTY CONFIGURATION.
        // ***********************************************************

        /**
         * Sets the default value for a integer property.
         *
         * @param propHandle: Handle to a property definition.
         * @param defaultValue: Double containing the default value.
         */
        virtual void setDefaultValue(void* propHandle, int defaultValue) = 0;

        /**
         * Sets the default value for a double property.
         *
         * @param propHandle: Handle to a property definition.
         * @param defaultValue: Double containing the default value.
         */
        virtual void setDefaultValue(void* propHandle, double defaultValue) = 0;

        /**
         * Sets the default value for a string property. This includes
         * enumerated properties as well as string properties.
         *
         * @param propHandle: Handle to a property definition.
         * @param defaultValue: Pointer to the character array containing the default value.
         */
        virtual void setDefaultValue(void* propHandle, char* defaultValue) = 0;

        /**
         * Configure the read-only state for the specified property
         * definition handle.
         *
         * @param propHandle: Handle to a property definition.
         * @param state: Read-only state name.
         */
        virtual void setPropReadOnly(void* propHandle, const char* state) = 0;

        /**
         * Configure the increment for an integer property.
         *
         * @param propHandle: Handle to a property definition.
         * @param increment: Increment.
         */
        virtual void setIntPropIncrement(void* propHandle, int increment) = 0;

        /**
         * Sets the property's accessibility.
         *
         * @param propHandle: Handle to a property definition.
         * @param accessible: Whether the property is currently accessible.
         */
        virtual void setAccessible(void* propHandle, bool accessible) = 0;

        /**
         * Configure the expertise level of a property. The default is beginner,
         * but if you wish to make a property less visible to the beginner you can
         * set the level higher.
         *
         * @param propHandle: Handle to a property definition.
         * @param level: Visibility.
         */
        virtual void setVisibility(void* propHandle, visibility::levels level) = 0;

        /**
         * Configures the property identifier to the given value. A
         * property identifier can be any integer value and does
         * not have to be unique with respect to other properties.
         *
         * This is provided mainly as a convenience to associate a
         * numerical ID with a property name to facilitate property
         * look-ups.
         *
         * @param propHandle: Handle to a property definition.
         * @param propID: Property identifier.
         */
        virtual void setIdentifier(void* propHandle, int propID) = 0;

        /**
         * Properties can be grouped by category. Use this method to add a category
         * to a property. To add a property to a subcategory too, call this
         * method first for the top level category, and then the subcategory. Any
         * number of subcategories can be added.
         *
         * @param propHandle: Handle to a property definition.
         * @param category: Category name.
         */
        virtual void addCategory(void* propHandle, const char* category) = 0;

        /**
         * Indicate if an attempt to change the property's value to its
         * current value should be aborted and result in a no-operation.
         *
         * By default, property value SETs will abort if the current value matches
         * the new configuration value.
         *
         * @param propHandle: Handle to a property definition.
         * @param abortSetAllowed: True if a property SET should be aborted.
         */
        virtual void setAbortSetAllowed(void* propHandle, bool abortSetAllowed) = 0;

        /**
         * Adds a line of text to the property help description.
         *
         * @param propHandle: Handle to a property definition.
         * @param helpLine: Line of property help text.
         */
        virtual void addPropHelpLine(void* propHandle, const char* helpLine) = 0;

        /**
         * Adds property help description from the IMDF file.
         *
         * If property help information is known a priori, it can be stored
         * in the device or toolbox section of an IMDF file, under the
         * &lt;propertyhelp&gt; element. This function can be used at
         * run-time in order to instruct the toolbox engine to load property
         * help information from the IMDF file.
         *
         * If there is additional help information adaptors wish to append to
         * the text provided by the IMDF file, it can be specified as well.
         *
         * @param propHandle: Handle to a property definition.
         * @param additionalHelp: Any additional help that is not in the IMDF file.
         */
        virtual void addPropHelpFromIMDF(void* propHandle, const char*
                                         additionalHelp = 0) = 0;

    };
}
#endif
