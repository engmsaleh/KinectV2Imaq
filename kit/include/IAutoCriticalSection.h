/**
 * @file:    IAutoCriticalSection.h
 *
 * Purpose:  Used to automatically unlock imaqkit::ICriticalSection objects.
 *
 * $Authors: Chris P., Dave T. $
 *
 * $Copyright: 2001-2014 The MathWorks, Inc.$
 *
 *
 */

#ifndef __IMAQADAPTOR__IAUTOCRITICALSECTION__HEADER__
#define __IMAQADAPTOR__IAUTOCRITICALSECTION__HEADER__

#include "IMAQInterface.h"

namespace imaqkit
{

    /**
     * @class IAutoCriticalSection
     *
     * @brief  Used to automatically unlock imaqkit::ICriticalSection objects.
     *
     * To create a new imaqkit::IAutoCriticalSection use imaqkit::createAutoCriticalSection().
     *
     * Auto critical section objects can be used to wrap imaqkit::ICriticalSection
     * objects in a way that guarantees the section will be released
     * upon going out of scope, or if an exception occurs.
     *
     * The critical section can be entered and left an arbitrary number of
     * times within the lifetime of a single imaqkit::IAutoCriticalSection.
     *
     * Using imaqkit::ICriticalSection and imaqkit::IAutoCriticalSection objects
     * together will prevent deadlocks in cases where an exception is thrown while
     * a thread is waiting to enter code sections or access resources that are being
     * protected.
     *
     * In order to properly manage these critical section objects, the use of
     * a smart pointer that retains sole ownership of an object is recommended.
     * For example, the following paradigm is suggested:
     *
     * @code
     *
     * // To protect resources or a section of code from being accessed simultaneously
     * // across threads, create an imaqkit::IAutoCriticalSection object, which:
     * //    1) Automatically enters (locks) the imaqkit::ICriticalSection object provided; and
     * //    2) Automatically leaves (releases) it when the imaqkit::IAutoCriticalSection object is destroyed.
     * //
     * // Auto destroy the imaqkit::IAutoCriticalSection pointer by using a smart pointer
     * // like std::auto_ptr<> object.
     * imaqkit::IAutoCriticalSection* autoSection = imaqkit::createAutoCriticalSection(_section);
     * std::auto_ptr<imaqkit::IAutoCriticalSection> section(autoSection);
     * ...
     *
     * // Access resources or sections of code in a thread safe manner.
     * // When the auto_ptr object goes out of scope, i.e. when the method returns
     * // or if an exception occurs, everything will be released and destroyed correctly.
     * ...
     *
     * @endcode
     *
     */
    class IAutoCriticalSection  : public IMAQInterface
    {

      public:
        /**
         * Enter the critical section.
         *
         * If the critical section has not been entered (locked) then enter it and lock
         * the section.  If it has already been entered, do nothing.
         */
        virtual void enter(void) = 0;

        /**
         * Leave the critical section.
         *
         * If the critical section has been entered (locked) then leave
         * (unlock) the critical section.  Otherwise, do nothing.
         */
        virtual void leave(void) = 0;

        /**
         * Return a boolean indicating if the critical section has been entered.
         *
         * @return bool: True if the critical section has been entered. False otherwise.
         */
        virtual bool getState(void) = 0;
    };
}

#endif
