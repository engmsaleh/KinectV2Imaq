/* Copyright 2004-2013 The MathWorks, Inc. */
/**
 * @file:       IPropInfo.h
 *
 * Purpose:     Property information interface.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IPROPINFO__HEADER__
#define __IMAQADAPTOR__IPROPINFO__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    namespace propertytypes
    {
        /**
         * Native property data types supported by the toolbox engine.
         *
         * The "Other" data type is used for native MATLAB arrays that
         * are not described by any of the other data types. It is also
         * a reserved data type for internal engine properties. It is
         * not intended to be used by adaptors directly.
         *
         */
        enum DATATYPE
        {
            OTHER              = 0,
            STRING             = 1,
            DOUBLE             = 2,
            DOUBLE_ARRAY       = 3,
            INT                = 4,
            INT_ARRAY          = 5,
            COMMAND            = 6
        };

        /**
         * Native data type when property value holds
         * a 1xN array of doubles.
         *
         * For example, properties defined as a DOUBLE_ARRAY
         * use this data type to store a 1x2 array of doubles.
         *
         * @param ndoubles: Indicates how many elements are in the array.
         * @param doubles: The array of doubles.
         */
        typedef struct NDoubles
        {
            size_t  ndoubles;
            double* doubles;
        } NDoubles;

        /**
         * Native data type when property value holds
         * a 1xN array of integers.
         *
         * For example, properties defined as a INT_ARRAY
         * use this data type to store a 1x2 array of integers.
         *
         * @param nints: Indicates how many elements are in the array.
         * @param ints: The array of integers.
         */
        typedef struct NInts
        {
            size_t nints;
            int*   ints;
        } NInts;
    }

    /**
     * Class IPropInfo
     *
     * @brief:  Property information interface
     *
     * Provides methods for determining property information such
     * as default value, name, and native data type.
     *
     */
    class IPropInfo : public imaqkit::IMAQInterface
    {

      public:
        /**
         * Return the property's name.
         *
         * @return const char*: The property's name.
         */
        virtual const char* getPropertyName(void) const = 0;

        /**
         * Return the property's default value.
         *
         * @return void*: The property's default value.
         */
        virtual void* getPropertyDefault(void)  = 0;

        /**
         * Set the property's default value.
         *
         * @param value: The property's default value.
         */
        virtual void setPropertyDefault(void* value) = 0;

        /**
         * Return the property's internal storage type.
         *
         * @return imaqkit::propertytypes::DATATYPE: The property's internal storage type.
         */
        virtual imaqkit::propertytypes::DATATYPE getPropertyStorageType(void) const = 0;

        /**
         * Return the property's identifier.
         *
         * @return int: The property's identifier.
         */
        virtual int getPropertyIdentifier(void) const = 0;

        /**
         * Flag indicating if the property is device specific.
         *
         * @return bool: True if the property is device specific.
         */
        virtual bool isPropertyDeviceSpecific(void) const = 0;

        /**
         * Flag indicating if the property is an enumerated property.
         *
         * @return bool: True if the property's values are enumerated.
         */
        virtual bool isPropertyEnumerated(void) const = 0;

        /**
         * Returns whether the property is currently accessible.
         *
         * @param none
         *
         * @return bool: Whether the property is currently accessible.
         */
        virtual bool isAccessible() const = 0;

        /**
         * Set the property's accessibility.
         *
         * @param accessible: Whether the property is currently accessible.
         *
         * @return none
         */
        virtual void setAccessible(bool accessible) = 0;

        /**
         * Returns whether the property is read-only.
         *
         * @param none
         *
         * @return const char*:  Whether the property is read-only.
         */
        virtual const char* getReadOnly() const  = 0;

        /**
         * Sets whether the property is read-only.
         *
         * @param readOnly: whether the property is read-only
         *
         * @return none
         */
        virtual void setReadOnly(const char* readOnly) = 0;

        /**
         * Change the lower limit of a numeric property.
         *
         * @param lowerLimit: The lower limit.
         */
        virtual void changeLowerLimit(const void* lowerLimit) = 0;

        /**
         * Change the upper limit of a numeric property.
         *
         * @param upperLimit: The upper limit.
         */
        virtual void changeUpperLimit(const void* upperLimit) = 0;
    };
}

#endif
