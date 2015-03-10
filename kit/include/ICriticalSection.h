/**
 * @file:           ICriticalSection.h
 *
 * Purpose:     Critical section object interface for use with imaqkit::IAutoCriticalSection.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2005 The MathWorks, Inc.$
 *
 *
 */

#ifndef __IMAQADAPTOR__ICRITICALSECTION__HEADER__
#define __IMAQADAPTOR__ICRITICALSECTION__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    /**
     * @class ICriticalSection
     *
     * @brief  Critical section object interface for use with imaqkit::IAutoCriticalSection.
     *
     * Critical section objects allow adaptors to protect resources
     * accessed from multiple threads.
     *
     * Using imaqkit::ICriticalSection and imaqkit::IAutoCriticalSection objects
     * together will prevent deadlocks in cases where an exception is thrown while
     * a thread is waiting to enter code sections or access resources that are being
     * protected.
     *
     * One imaqkit::ICriticalSection object should be instantiated for each
     * section of code you wish to protect.
     *
     * To instantiate an instance of this class use the function
     * imaqkit::createCriticalSection().
     *
     * Adaptors creating imaqkit::ICriticalSection objects must be sure to
     * destroy them when they are no longer needed by calling delete. For example:
     *
     * @code
     *
     * // To protect resources or a section of code from being accessed simultaneously
     * // across threads, create an imaqkit::ICriticalSection object. The
     * // imaqkit::ICriticalSection object can be used wherever a section of code
     * // needs to be protected. Be sure to destroy the imaqkit::ICriticalSection object
     * // when it is no longer needed.
     * class MyAdaptor{
     *
     * public:
     *    MyAdaptor(void){
     *        // This critical section will allow MyAdaptor methods to access
     *        // resources or sections of code in a thread safe manner.
     *        _section = imaqkit::createCriticalSection();
     *    }
     *
     *    ~MyAdaptor(void){
     *        // Destroy the critical section object.
     *        delete _section;
     *    }
     *
     * private:
     *    /// Critical section object.
     *    imaqkit::ICriticalSection* _section;
     * }
     *
     * @endcode
     *
     */
    class ICriticalSection : public IMAQInterface
    {

      public:
        /**
         * Enters (locks) a critical section.
         */
        virtual void enter(void) = 0;

        /**
         * Exits (unlocks) a critical section.
         */
        virtual void leave(void) = 0;
    };
}

#endif
