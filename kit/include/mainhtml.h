/**
 * @file:       mainhtml.h
 *
 * Purpose:     Main HTML page for code documentation.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 */

/**
 * @mainpage
 *
 * <HR SIZE="1">
 *
 * The Image Acquisition Toolbox Adaptor Kit is a C++ framework that enables third-parties
 * to develop custom hardware interfaces for the Image Acquisition Toolbox. The adaptor kit
 * helps you meet your image acquisition needs by allowing you to access unsupported video
 * capture cameras and frame grabbers directly from the toolbox.
 *
 * The Image Acquisition Toolbox Adaptor Kit defines an Application Program Interface (API) for
 * implementing an Image Acquisition Toolbox adaptor. An adaptor is a dynamic link library (DLL)
 * that implements the connection between the Image Acquisition Toolbox engine and a device driver
 * via a hardware vendor's Software Development Kit (SDK) API.
 *
 * By developing an adaptor for the Image Acquisition Toolbox, you are able to:
 *
 * <ul>
 * <li> Expose image acquisition hardware information to MATLAB.</li>
 * <li> Communicate with an image acquisition hardware device and acquire data from it.</li>
 * <li> Configure device specific settings and hardware triggers.</li>
 * <li> Select different acquisition sources.</li>
 * </ul>
 *
 * @section doc Documentation
 *
 * The documentation for the Image Acquisition Toolbox Adaptor Kit is provided in two
 * parts:
 *
 * <ul>
 * <li> User's Guide - Provides detailed setup and tutorial information. This is availaible as part of the Image Acquisition Toolbox documention.</li>
 * <li> <a href="#kitref">API Reference</a> - API specification for adaptor kit classes and functions. </li>
 * </ul>
 *
 * It is recommended you begin with the adaptor kit User's Guide and refer
 * to the <a href="#kitref">API Reference</a> as a supplemental resource.
 *
 * @section audience Audience
 *
 * The Image Acquisition Toolbox Adaptor Kit documentation is intended for developers using
 * the C/C++ programming language in a Microsoft Windows&reg; environment.
 *
 * @section kitref API Reference
 *
 * The Image Acquisition Toolbox Adaptor Kit API uses an abstract, hardware-independent, class
 * hierarchy that can be derived from in order to implement hardware specific functionality.
 *
 * There are several types of C++ classes in the adaptor kit, all of which are provided as part of
 * the <b>imaqkit</b> namespace. The adaptor kit <a href="./hierarchy.html">Class Hierarchy</a>
 * illustrates the tree of classes available for developing an adaptor.
 *
 * Also contained in the <b>imaqkit</b> namespace is a collection of
 * <a href="./namespacemembers_func.html">C utility functions</a> exported by the Image Acquisition Toolbox
 * engine that help facilitate adaptor development.
 *
 * The Image Acquisition Toolbox Adaptor Kit is packaged and provided as a Microsoft Visual C++ .NET
 * project file (imaqadaptorkit.vcproj), available in the following directory:
 *
 * <center><code>
 * $MATLAB\\toolbox\\imaq\\imaqadaptors\\kit\   \
 * </code></center>
 *
 * where <code>$MATLAB</code> represents your MATLAB installation directory.
 *
 * @section demo Demo Adaptor
 *
 * In order to assist you with the adaptor development process, a demo adaptor is provided with the
 * Image Acquisition Toolbox Adaptor Kit. The Demo adaptor is a fully functional adaptor that does not
 * require any hardware. It illustrates how the adaptor kit classes and functions can be used.
 *
 * The Demo adaptor is one example of how to design and develop an adaptor. However, the adaptor kit
 * allows you to structure your adaptor as you see fit or as your hardware requires.
 *
 * The Demo adaptor project is available in the following directory:
 *
 * <center><code>
 * $MATLAB\\toolbox\\imaq\\imaqadaptors\\kit\\demo\     \
 * </code></center>
 *
 * where <code>$MATLAB</code> represents your MATLAB installation directory. The Demo adaptor project is provided
 * as part of a Microsoft Visual C++ .NET solution file (mwdemoimaq.sln).
 *
 * @subsection demousing Using the Demo Adaptor
 *
 * Before building the Demo adaptor project, a MATLAB environment variable is required. Search
 * for the "Using Environment Variables" section in the
 * User's Guide for details on defining this environment variable.
 *
 * Once the Demo adaptor project is compiled and built, the resulting adaptor DLL must be registered
 * with the toolbox using <code>IMAQREGISTER</code>. Search for the "Registering an Adaptor with the Toolbox"
 * section in the
 * User's Guide
 * for details on registering an adaptor.
 *
 * @section related Related Topics
 *
 * Image Acquisition Toolbox adaptor development involves conventional C/C++ programming techniques.
 * However, there are several aspects of C/C++ programming that may be unfamiliar to some developers.
 * The following provides a brief online tutorial of the C/C++ language and the features it has to
 * offer, many of which are used by the Image Acquisition Toolbox Adaptor Kit:
 *
 * <ul>
 * <li> <a href="http://www.cplusplus.com/doc/tutorial/" target="_blank">C++ Language Tutorial</a></li>
 * </ul>
 *
 * Additional material related to the Image Acquisition Toolbox Adaptor Kit includes:
 *
 * <ul>
 * <li> <a href="http://www.mathworks.com/" target="_blank">MathWorks Web Site</a></li>
 * <li> <a href="http://www.mathworks.com/products/imaq/" target="_blank">Image Acquisition Toolbox Product Page</a></li>
 * <li>
 * Image Acquisition Toolbox User's Guide</a></li>
 * </ul>
 *
 */
