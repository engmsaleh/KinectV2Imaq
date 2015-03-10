/**
 * @file:       IMAQInterface.h
 *
 * Purpose:     Base class for image acquisition adaptor interfaces.
 *
 * $Authors:    Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IMAQINTERFACE__HEADER__
#define __IMAQADAPTOR__IMAQINTERFACE__HEADER__

#include "imaqfcnexports.h"

namespace imaqkit
{
    /**
     * Class IMAQInterface
     *
     * @brief:  Ensures all memory (de)allocations for Image Acquisition
     *          Adaptor Kit classes are routed through the Image Acquisition
     *          Toolbox engine.
     *
     */
    class IMAQInterface
    {

      public:
        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        IMAQInterface(void) {};
        virtual ~IMAQInterface(void) {};

        // *******************************************************************
        // MEMORY (DE)ALLOCATORS.
        // *******************************************************************
        inline static void* operator new(size_t len)
        {
            return imaqkit::imaqmalloc(len);
        };
        inline static void operator delete(void* ptr)
        {
            imaqkit::imaqfree(ptr);
        };

        inline static void* operator new[](size_t len)
        {
            return imaqkit::imaqmalloc(len);
        };
        inline static void operator delete[](void* ptr)
        {
            imaqkit::imaqfree(ptr);
        };

        inline static void* operator new(size_t len, void* ptr)
        {
            return ptr;
        };
        inline static void operator delete(void* ptr1, void* ptr2) { };

        inline static void* operator new[](size_t len, void* ptr)
        {
            return ptr;
        };
        inline static void operator delete[](void* ptr1, void* ptr2) { };
    };
}

#endif
