/**
 * @file:       DemoTimestampGetFcn.cpp
 *
 * Purpose:     Implements the methods of the DemoTimestampGetFcn class.
 *
 *
 * $Authors:    DT$
 *
 * $Copyright  2009-2012 The MathWorks, Inc.$
 *
 *
 */

#include "DemoTimestampGetFcn.h"
#include <ctime>
#include <cstring>
#include <assert.h>

void DemoTimestampGetFcn::getValue(imaqkit::IPropInfo* propertyInfo, void* value)
{

    time_t intTime;
#ifndef _WIN32
    char* strTime;
#endif
    size_t strTimeLen;
    char** returnStr;
    const int ctimeMaxLength = 26;  // 26 as described in documentation for ctime
    char buffer[ctimeMaxLength];

    switch (propertyInfo->getPropertyStorageType()) {
      case imaqkit::propertytypes::INT:

        // Determine the current value of the property and then assign
        // it to pointer that was passed in to the method.
        intTime = std::time(NULL);
        *(reinterpret_cast<int64_t*>(value)) = static_cast<int64_t>(intTime);
        break;

      case imaqkit::propertytypes::STRING:

        // String values and array properties require the method to allocate
        // enough memory to hold the current value.  The engine is
        // responsible for freeing the memory once it is done with it.

        // Get the time as a string.
        intTime = std::time(NULL);

#ifdef _WIN32
        if (ctime_s(buffer, ctimeMaxLength, &intTime) != 0) {
            returnStr = reinterpret_cast<char**>(value);
            *returnStr = static_cast<char*>(imaqkit::imaqmalloc(sizeof(char) * 1));
            (*returnStr)[0] = '\0';
            break;
        }

        // The buffer given by ctime has a newline and then a null character.
        // Remove the newline.
        buffer[ctimeMaxLength - 2] = '\0';

        // The buffer that we have filled in is static and cannot be freed
        // so the method must make a copy with memory that has been allocated.
        strTimeLen = strlen(buffer);
        returnStr = reinterpret_cast<char**>(value);
        *returnStr = static_cast<char*>(imaqkit::imaqmalloc(sizeof(char) * (strTimeLen + 1)));
        strcpy_s(*returnStr, strTimeLen + 1, buffer);
#else
        strTime = std::ctime(&intTime);
        if (strTime == NULL) {
            returnStr = reinterpret_cast<char**>(value);
            *returnStr = static_cast<char*>(imaqkit::imaqmalloc(sizeof(char) * 1));
            (*returnStr)[0] = '\0';
            break;
        }

        // The pointer returned by std::ctime() is static and cannot be freed
        // so the method must make a copy with memory that has been allocated.
        strTimeLen = strlen(strTime);
        returnStr = reinterpret_cast<char**>(value);
        *returnStr = static_cast<char*>(imaqkit::imaqmalloc(sizeof(char) * (strTimeLen + 1)));
        strncpy(*returnStr, strTime, strTimeLen);
        // The pointer returned by ctime has a newline and then a null character.
        // Remove the newline
        (*returnStr)[strTimeLen - 1] = '\0';
#endif
        break;

      default:
        assert(false && "Unhandled property data type. Need to add a new data type case.");
    }
}
