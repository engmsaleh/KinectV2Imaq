/* Copyright 2004-2009 The MathWorks, Inc. */
/**
 * @file:       IEnginePropInfo.h
 *
 * Purpose:     Property information interface.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IENGINEPROPINFO__HEADER__
#define __IMAQADAPTOR__IENGINEPROPINFO__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    namespace enginepropertytypes
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
            INT_ARRAY          = 5
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
            int     ndoubles;
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
            int     nints;
            int*    ints;
        } NInts;
    }

    /**
     * Class IEnginePropInfo
     *
     * @brief:  Property information interface
     *
     * Provides methods for determining property information such
     * as default value, name, and native data type.
     *
     */
    class IEnginePropInfo : public imaqkit::IMAQInterface
    {

      public:
        /**
         * Return the property's name.
         *
         * @return const char*: The property's name.
         */
        virtual const char* getPropertyName(void) = 0;

        /**
         * Return the property's default value.
         *
         * @return void*: The property's default value.
         */
        virtual void* getPropertyDefault(void) = 0;

        /**
         * Return the property's internal storage type.
         *
         * @return imaqkit::enginepropertytypes::DATATYPE: The property's internal storage type.
         */
        virtual imaqkit::enginepropertytypes::DATATYPE getPropertyStorageType(void) = 0;

        /**
         * Return the property's identifier.
         *
         * @return int: The property's identifier.
         */
        virtual int getPropertyIdentifier(void) = 0;

        /**
         * Flag indicating if the property is device specific.
         *
         * @return bool: True if the property is device specific.
         */
        virtual bool isPropertyDeviceSpecific(void) = 0;

        /**
         * Flag indicating if the property is an enumerated property.
         *
         * @return bool: True if the property's values are enumerated.
         */
        virtual bool isPropertyEnumerated(void) = 0;

    };
}

#endif
