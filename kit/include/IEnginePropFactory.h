///*  */
///**
// * @file:       IEnginePropFactory.h
// *
// * Purpose:     Factory for creating property information.
// *
// * $Authors:    Chris P., Dave T. $
// *
// * $Copyright: 2001-2012 The MathWorks, Inc.$
// *
// * 
// *
// */
//
//#ifndef __IMAQADAPTOR__IENGINEPROPFACTORY__HEADER__
//#define __IMAQADAPTOR__IENGINEPROPFACTORY__HEADER__
//
//#include "IMAQInterface.h"
//
//namespace imaqkit
//{
//
//    namespace enginepropreadonly
//    {
//        /// Property read-only option indicating a property is always read-only.
//        const char* const ALWAYS = "always";
//
//        /// Property read-only option indicating a property is never read-only.
//        const char* const NEVER = "never";
//
//        /**
//         * Property read-only option indicating a property is only
//         * read-only when the Running property is 'on'.
//         */
//        const char* const WHILE_RUNNING ="whileRunning";
//    }
//
//    /**
//     * Class IEnginePropFactory
//     *
//     * @brief:  Mechanism by which properties can be defined and stored.
//     *
//     * This imaqkit::IEnginePropFactory class enables adaptors to define and add
//     * device specific properties to the imaqkit::IEngine when the
//     * getDeviceAttributes function is invoked by the toolbox engine.
//     *
//     */
//    class IEnginePropFactory : public imaqkit::IMAQInterface
//    {
//
//      public:
//        // *******************************************************************
//        // PROPERTY CREATION.
//        // *******************************************************************
//        /**
//         * Create a new property definition which is a vector
//         * of doubles.  Each double must have a default value.
//         *
//         * @param propertyName: Property's name.
//         * @param numElements: The number of elements in the array
//         * @param defaultValues: The default values.
//         */
//        virtual void* createDoubleArrayProperty(const char* propertyName,
//                                                int numElements, double* defaultValues) = 0;
//
//        /**
//         * Create a new property definition constrained to be a 1x2
//         * array of doubles bounded by a minimum and maximum value.
//         *
//         * @param propertyName: Property's name.
//         * @param lowerBound: Minimum value for this property.
//         * @param upperBound: Maximum value for this property.
//         * @param firstDefaultValue: Default value for the first value.
//         * @param secondDefaultValue: Default value for the second value.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createDoublePairProperty(const char* propertyName, double lowerBound, double upperBound,
//                                               double firstDefaultValue, double secondDefaultValue) = 0;
//
//        /**
//         * Create a double property with lower and upper bounds.
//         *
//         * @param propertyName: Name of the property.
//         * @param lowerBound: Minimum valid value.
//         * @param upperBound: Maximum valid value.
//         * @param defaultValue: Default property value.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createDoubleProperty(const char* propertyName, double lowerBound, double upperBound, double defaultValue) = 0;
//
//        /**
//         * Create a double property with no lower or upper bounds.
//         *
//         * @param propertyName: Name of the property.
//         * @param defaultValue: Default property value.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createDoubleProperty(const char* propertyName, double defaultValue) = 0;
//
//        /**
//         * Create a new property definition which is a vector
//         * of ints.  Each int must have a default value.
//         *
//         * @param propertyName: Property's name.
//         * @param numElements: The number of elements in the array
//         * @param defaultValues: The default values.
//         */
//        virtual void* createIntArrayProperty(const char* propertyName,
//                                             int numElements, int* defaultValues) = 0;
//
//        /**
//         * Create a new property definition constrained to be a
//         * 1x2 array of integers bounded by a minimum and maximum value.
//         *
//         * @param propertyName: Property's name.
//         * @param lowerBound: Minimum value for this property.
//         * @param upperBound: Maximum value for this property.
//         * @param firstDefaultValue: Default value for the first value.
//         * @param secondDefaultValue: Default value for the second value.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createIntPairProperty(const char* propertyName, int lowerBound, int upperBound,
//                                            int firstDefaultValue, int secondDefaultValue) = 0;
//
//        /**
//         * Create an integer property with lower and upper bounds.
//         *
//         * @param propertyName: Name of the property.
//         * @param lowerBound: Minimum valid value.
//         * @param upperBound: Maximum valid value.
//         * @param defaultValue: Default property value.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createIntProperty(const char* propertyName, int lowerBound, int upperBound, int defaultValue) = 0;
//
//        /**
//         * Create an integer property with no lower or upper bounds.
//         *
//         * @param propertyName: Name of the property.
//         * @param defaultValue: Default property value.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createIntProperty(const char* propertyName, int defaultValue) = 0;
//
//        /**
//         * Create a string property.
//         *
//         * @param propertyName: Name of the property.
//         * @param defaultValue: Default property value.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createStringProperty(const char* propertyName, const char* defaultValue) = 0;
//
//        /**
//         * Create an enumerated string property.
//         *
//         * @param propertyName: Name of the property.
//         * @param defaultEnumStr: Default enum string.
//         * @param defaultEnumID: Default enum ID.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createEnumProperty(const char* propertyName, const char* defaultEnumStr, int defaultEnumID) = 0;
//
//        /**
//         * Create a property from the associated IMDF file.
//         *
//         * @param propertyName: Name of the property.
//         *
//         * @return void*: Handle to a property definition.
//         */
//        virtual void* createPropFromIMDF(const char* propertyName) = 0;
//
//        /**
//         * Add a new enumerated value to an enumerated property that was defined.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param value: New enum string value.
//         * @param ID: Enum string identifier.
//         *
//         */
//        virtual void addEnumValue(void* propHandle, const char* value, int ID) = 0;
//
//        // ***********************************************************
//        // PROPERTY REGISTRATION.
//        // ***********************************************************
//        /**
//         * Adds a property definition handle to the property container.
//         *
//         * @param propHandle: Handle to a property definition.
//         */
//        virtual void addProperty(void* propHandle) = 0;
//
//        /**
//         * Adds a property definition handle to the property container.
//         *
//         * In order for adaptors to easily identify a property, a
//         * property identifier can be associated when the property
//         * definition handle is added.
//         *
//         * This avoids adaptors from having to do string comparisons,
//         * as well as leverage any hardware SDK identifiers that can
//         * be used to uniquely identify a hardware device setting.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param id: The property identifier.
//         */
//        virtual void addProperty(void* propHandle, int id) = 0;
//
//        // ***********************************************************
//        // PROPERTY CONFIGURATION.
//        // ***********************************************************
//        /**
//         * Sets the default value for a double or integer property.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param defaultValue: Double containing the default value.
//         */
//        virtual void setDefaultValue(void* propHandle, double defaultValue) = 0;
//
//        /**
//         * Sets the default value for a string property. This includes
//         * enumerated properties as well as string properties.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param defaultValue: Pointer to the character array containing the default value.
//         */
//        virtual void setDefaultValue(void* propHandle, const char* defaultValue) = 0;
//
//        /**
//         * Configure the read-only state for the specified property
//         * definition handle.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param state: Read-only state name.
//         */
//        virtual void setPropReadOnly(void* propHandle, const char* state) = 0;
//
//        /**
//         * Configures the property identifier to the given value. A
//         * property idenitifier can be any integer value and does
//         * not have to be unique with respect to other properties.
//         *
//         * This is provided mainly as a convenience to associate a
//         * numerical ID with a property name to facilitate property
//         * look-ups.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param propID: Property identifier.
//         */
//        virtual void setIdentifier(void* propHandle, int propID) = 0;
//
//        /**
//         * Indicate if the property should be initialized upon
//         * being created for a VIDEOINPUT object instance.
//         *
//         * By default, all properties are initialized after creation.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param init: True if property is to be initialized after creation, false otherwise.
//         */
//        virtual void setInitAfterCreate(void* propHandle, bool init) = 0;
//
//        /**
//         * Indicate if an attempt to change the property's value to its
//         * current value should be aborted and result in a no-operation.
//         *
//         * By default, property value SETs will abort if the current value matches
//         * the new configuration value.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param abortSetAllowed: True if a property SET should be aborted.
//         */
//        virtual void setAbortSetAllowed(void* propHandle, bool abortSetAllowed) = 0;
//
//        /**
//         * Adds a line of text to the property help description.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param helpLine: Line of property help text.
//         */
//        virtual void addPropHelpLine(void* propHandle, const char* helpLine) = 0;
//
//        /**
//         * Adds property help description from the IMDF file.
//         *
//         * If property help information is known a priori, it can be stored
//         * in the device or toolbox section of an IMDF file, under the
//         * &lt;propertyhelp&gt; element. This function can be used at
//         * run-time in order to instruct the toolbox engine to load property
//         * help information from the IMDF file.
//         *
//         * If there is additional help information adaptors wish to append to
//         * the text provided by the IMDF file, it can be specified as well.
//         *
//         * @param propHandle: Handle to a property definition.
//         * @param additionalHelp: Any additional help that is not in the IMDF file.
//         */
//        virtual void addPropHelpFromIMDF(void* propHandle, const char*
//                                         additionalHelp=0) = 0;
//
//        /**
//         * Read an element section off the device section in the IMDF file.
//         *
//         * If property help information is known a priori, it can be stored
//         * in the device or toolbox section of an IMDF file, under its own element name.
//         * This element name can then be provided to this function at run-time
//         * in order to instruct the toolbox engine to load property help information
//         * from the IMDF file.
//         *
//         * An element name is the "name" attribute of an &lt;include&gt; section.
//         *
//         * @param elementName: Element name in the IMDF fle.
//         */
//        virtual void includeIMDFSection(const char* elementName) = 0;
//    };
//}
//#endif
