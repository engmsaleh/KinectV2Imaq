/**
 * @file:       IEngine.h
 *
 * Purpose:     Interface to the Image Acquisition Toolbox engine.
 *
 * $Authors:    Robert D., Chris P., Dave T. $
 *
 * $Copyright: 2001-2012 The MathWorks, Inc.$
 *
 *
 */
#ifndef __IMAQADAPTOR__IENGINE__HEADER__
#define __IMAQADAPTOR__IENGINE__HEADER__

#include "IPropContainer.h"
#include "IEnginePropContainer.h"
#include "IAdaptorFrame.h"

namespace imaqkit
{

    // Forward class declaration.
    class ITriggerStatus;

    /**
     * Class IEngine
     *
     * @brief:  Interface to the Image Acquisition Toolbox engine.
     *
     *          This interface enables imaqkit::IAdaptor objects to
     *          communicate information to the engine, or query it for
     *          information.
     *
     */
    class IEngine : public imaqkit::IMAQInterface
    {

      public:
        // *******************************************************************
        // METHODS FOR USE BY ADAPTORS.
        // *******************************************************************
        /**
         * Create an imaqkit::IAdaptorFrame object.
         *
         * Returns a handle to an imaqkit::IAdaptorFrame object that can be passed to the
         * imaqkit::IEngine::receiveFrame() function.
         *
         * An imaqkit::IAdaptorFrame object provides adaptors a way to transfer
         * image data to the toolbox engine.
         *
         * The imaqkit::IAdaptor object should use the imaqkit::IAdaptorFrame::setImage()
         * function before passing it to imaqkit::IEngine::receiveFrame().
         *
         * If a NULL frame handle is returned, the frame object could
         * not be created, which is usually an indication that memory
         * allocation failed.
         *
         * The specified width and height dimensions should be the desired ROI
         * width and height of the image data that will be stored in the
         * imaqkit::IAdaptorFrame object, i.e. the image data that will be returned
         * to MATLAB.
         *
         * @param frameType: Indicates the type image imaqkit::IAdaptorFrame to create.
         * @param roiWidth: Desired image frame ROI width.
         * @param roiHeight: Desired image frame ROI height.
         *
         * @return imaqkit::IAdaptorFrame*: imaqkit::IAdaptorFrame object handle.
         *
         */
        virtual imaqkit::IAdaptorFrame* makeFrame(imaqkit::frametypes::FRAMETYPE frameType, int roiWidth, int roiHeight) = 0;

        /**
         * Transfer an imaqkit::IAdaptorFrame object to the engine.
         *
         * Passes the imaqkit::IAdaptorFrame object to the engine. A NULL frame handle
         * signifies a skipped/dropped frame.
         *
         * @param frame: Handle to a frame object.
         */
        virtual void receiveFrame(imaqkit::IAdaptorFrame* frame) const = 0;

        /**
         * Query the engine for its running state.
         *
         * True indicates the engine is in a running state, i.e.
         * the Running property is set to 'on'.
         *
         * @return bool: Running state.
         */
        virtual bool isRunning(void) const = 0;

        /**
         * Query the engine for its previewing state.
         *
         * True indicates the engine is in a previewing state, i.e.
         * the Previewing property is set to 'on'.
         *
         * @return bool: Previewing state.
         */
        virtual bool isPreviewing(void) const = 0;

        /**
         * Query the engine for the property container containing the
         * general toolbox properties.
         *
         * Returns a handle to the property container the engine uses
         * to store all of the properties of a MATLAB VIDEOINPUT object.
         *
         * MATLAB VIDEOINPUT objects contain properties common across all
         * adaptor. This includes general acquisition parameters, trigger
         * settings, and general status information. These properties are
         * automatically managed and owned by the imaqkit::IEngine.
         *
         * The engine stores adaptor-specific properties in a separate
         * property container. See imaqkit::IEngine:getAdaptorPropContainer().
         *
         * @return imaqkit::IEnginePropContainer: Engine property container.
         */
        virtual imaqkit::IEnginePropContainer* getEnginePropContainer(void) const = 0;

        /**
         * Query the engine for the property container containing adaptor-specific
         * properties for the current acquisition source.
         *
         * Returns a handle to the property container the engine uses
         * to store all of the properties of a MATLAB VIDEOSOURCE object.
         *
         * MATLAB VIDEOSOURCE objects contain properties that are defined by
         * an adaptor, and specific to a hardware device. In addition to these,
         * MATLAB VIDESOURCE objects also contain a few general properties like
         * Parent, Tag, and Type.
         *
         * Adaptors iterating through this property container can filter thee
         * general properties by using imaqkit::IPropInfo::isPropertyDeviceSpecific()
         * to determine if a property is device-specific (i.e. adaptor-specific)
         * or not.
         *
         * NOTE: This function returns the property container for the currently
         * selected acquisition source. Do NOT cache the return value expecting
         * it to update when the user selects a different acquisition source from
         * MATLAB. Adaptors should always query imaqkit::IEngine when the container is
         * needed.
         *
         * @return imaqkit::IPropContainer: Adaptor property container for the current acquisition source.
         */
        virtual imaqkit::IPropContainer* getAdaptorPropContainer(void) const = 0;

        /**
         * Return information about the current trigger configuration.
         *
         * @return imaqkit::ITriggerStatus*: Interface for accessing the current trigger status.
         */
        virtual imaqkit::ITriggerStatus* getTriggerStatus(void) const = 0;

      protected:
        // *******************************************************************
        // CONSTRUCTOR/DESTRUCTOR.
        // *******************************************************************
        /** Disable default constructor.
         *
         * Must remain protected in order for inheritance to work properly.
         *
         */
        IEngine()
        {
        }

        /** Disable default destructor.
         *
         * Must remain protected in order for inheritance to work properly.
         *
         */
        virtual ~IEngine()
        {
        }

      private:
        // ***********************************************************
        // DISABLE DEFAULT METHODS.
        // ***********************************************************
        IEngine& operator=(const IEngine&);
        IEngine(const IEngine&);
    };
}

#endif
