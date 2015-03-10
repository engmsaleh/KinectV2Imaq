/* Copyright 2004-2009 The MathWorks, Inc. */
/**
 * @file:       imaqexportdef.h
 *
 * Purpose:     Internal Windows export declarations for imaqkit functions.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2005 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IMAQEXPORTDEF__HEADER__
#define __IMAQADAPTOR__IMAQEXPORTDEF__HEADER__

#ifdef _MSC_VER
#define DLL_EXPORT_SYM __declspec(dllexport)
#define DLL_EXPORT_TEMPLATE
#define DLL_IMPORT_SYM __declspec(dllimport)
#define ATTR_WARN_UNUSED_RESULT
#define SUPPORTS_PRAGMA_ONCE
#elif __GNUC__ >= 4
/*
 * Note:  All thowable classes (types thrown across DSO (Dynamic Shared
 * Object)) boundaries must have "default" visibility.
 *    See:  http://gcc.gnu.org/wiki/Visibility for more info on this topic
 */
#define DLL_EXPORT_SYM __attribute__ ((visibility("default")))
#define DLL_EXPORT_TEMPLATE __attribute__ ((visibility("default")))
#define DLL_IMPORT_SYM __attribute__ ((visibility("default")))
#define ATTR_WARN_UNUSED_RESULT __attribute__ ((warn_unused_result))
#define SUPPORTS_PRAGMA_ONCE
#else
#define DLL_EXPORT_SYM
#define DLL_EXPORT_TEMPLATE
#define DLL_IMPORT_SYM
#define ATTR_WARN_UNUSED_RESULT
#endif

#if defined(IMAQMEX_EXPORTS)
/// Used to indicate that the class is to be exported.
#define IMAQ_ADAPTOR_EXPORT DLL_EXPORT_SYM
#define IMAQ_ADAPTOR_IMPORT DLL_IMPORT_SYM
#else
/// Used to indicate that the class is to be imported (i.e. for users of imaqkit).
#define IMAQ_ADAPTOR_EXPORT DLL_IMPORT_SYM
#define IMAQ_ADAPTOR_IMPORT DLL_EXPORT_SYM
#endif

#endif
