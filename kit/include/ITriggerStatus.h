/**
 * @file:       ITriggerStatus.h
 *
 * Purpose:     Used to determine the current trigger configuration.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2005 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__ITRIGGERSTATUS__HEADER__
#define __IMAQADAPTOR__ITRIGGERSTATUS__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    namespace triggertypes
    {
        /**
         * Trigger type identifiers.
         *
         * The trigger type identifiers supported by the
         * toolbox engine.
         *
         */
        enum TYPE
        {
            IMMEDIATE   = 0,
            MANUAL      = 1,
            HARDWARE    = 2,
        };
    }

    /**
     * Class ITriggerStatus
     *
     * @brief:  Used to determine the current trigger configuration.
     *
     * When the imaqkit::IEngine is queried for the current trigger
     * configuration, an instance of this class is provided, allowing
     * adaptors to determine the current trigger type, condition,
     * and source configuration.
     *
     */
    class ITriggerStatus : public IMAQInterface
    {

      public:
        /**
         * Return the identifier for the current trigger type.
         *
         * @return imaqkit::triggertypes::TYPE: The current trigger type identifier.
         */
        virtual imaqkit::triggertypes::TYPE getTriggerType(void) = 0;

        /**
         * Return the identifier for the current trigger condition.
         *
         * If the current trigger configuration is not hardware specific,
         * 0 is returned.
         *
         * @return int: The current trigger condition identifier.
         */
        virtual int getTriggerCondition(void) = 0;

        /**
         * Return the identifier for the current trigger source.
         *
         * If the current trigger configuration is not hardware specific,
         * 0 is returned.
         *
         * @return int: The current trigger source identifier.
         */
        virtual int getTriggerSource(void) = 0;

      protected:
        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        ITriggerStatus(void) {};
        virtual ~ITriggerStatus(void) {};

      private:
        // ***********************************************************
        // DISABLE DEFAULT METHODS.
        // ***********************************************************
        ITriggerStatus& operator=(const ITriggerStatus&);
        ITriggerStatus(const ITriggerStatus&);
    };
}

#endif
