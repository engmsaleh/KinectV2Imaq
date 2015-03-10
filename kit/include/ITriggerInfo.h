/**
 * @file:       ITriggerInfo.h
 *
 * Purpose:     Interface used to add hardware trigger configurations.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__ITRIGGERINFO__HEADER__
#define __IMAQADAPTOR__ITRIGGERINFO__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    /**
     * Class ITriggerInfo
     *
     * @brief:  Interface used to add hardware trigger configurations
     *
     * This class is used by adaptors to inform the toolbox engine what
     * valid hardware trigger configurations a hardware device supports.
     *
     * A hardware trigger configuration consists of a trigger condition
     * and a trigger source.
     *
     */
    class ITriggerInfo : public IMAQInterface
    {

      public:
        // *******************************************************************
        // HARDWARE TRIGGER CONFIGURATIONS.
        // *******************************************************************
        /**
         * Add a valid hardware trigger configuration.
         *
         * The trigger condition and source names are used by the TRIGGERINFO
         * and TRIGGERCONFIG functions. Each trigger condition and source uniquely
         * identifies a hardware trigger configuration.
         *
         * Duplicate trigger configurations are ignored.
         *
         * Trigger condition and source names are case-sensitive.
         *
         * Trigger condition and source identifiers are not exposed to the
         * end user. They are provided to facilitate adaptors with
         * identifying a particular trigger condition or source. Identifiers
         * can be configured to any integer value. For example, numerical trigger
         * condition or source identifiers defined by the hardware SDK can be
         * used.
         *
         * Duplicate trigger condition or source identifiers are permitted.
         *
         * @param conditionName: Name of the trigger condition.
         * @param conditionID: Trigger condition identifier.
         * @param sourceName: Name of the trigger source.
         * @param sourceID: Trigger source identifier.
         */
        virtual void addConfiguration(const char* conditionName, int conditionID,
                                      const char* sourceName, int sourceID) = 0;

        /**
         * Includes the trigger information section from the associated IMDF file.
         *
         * If hardware trigger information is known a priori, it can be stored
         * in the device or toolbox section of an IMDF file, under its own element name.
         * This element name can then be provided to this function at run-time
         * in order to instruct the toolbox engine to load hardware trigger
         * information from the IMDF file.
         *
         * An element name is the "name" attribute of an &lt;include&gt; section.
         *
         * By default, hardware trigger information is assumed to exist in
         * the device section of the IMDF file. If it is located in the
         * toolbox section of the IMDF file, it can be indicated with a value
         * of false provided to this function.
         *
         * @param elementName: Element name in the IMDF file.
         * @param deviceSection: True if trigger information is in the device section of an IMDF file.
         */
        virtual void includeIMDFSection(const char* elementName, bool deviceSection = true) = 0;

      protected:
        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        ITriggerInfo(void) {};
        virtual ~ITriggerInfo(void) {};
    };
}

#endif
