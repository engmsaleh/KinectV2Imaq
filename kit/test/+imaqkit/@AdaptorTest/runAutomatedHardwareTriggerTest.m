function runAutomatedHardwareTriggerTest(obj)
%runAutomatedHardwareTriggerTest: This test checks videoinput object in
%  hardware trigger mode. It checks that frames are not acquired when the 
%  videoinput object is waiting for a trigger. To test triggering using
%  hardware trigger, refer to Image Acquisition Toolbox documentation. This
%  test is run using an object of type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runAutomatedHardwareTriggerTest
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    % Entry message
    obj.printBanner('Testing hardware triggering');
    infoStr = sprintf('This test checks videoinput object in hardware trigger mode. It checks that frames are not acquired when the  videoinput object is waiting for a trigger. To test triggering using hardware trigger, refer to Image Acquisition Toolbox documentation.');
    obj.printTestDescription(infoStr);

    % SETUP
    vidObj = obj.setupTest;

    % ===================== Test hardware trigger ========================%
    % First check if device supports hardware triggering
    info = triggerinfo(vidObj);
    [supportsHWTrigger hwTriggerIdx] = ismember('hardware', {info.TriggerType});
    
    if supportsHWTrigger
        try 
            triggerconfig(vidObj, 'hardware', info(hwTriggerIdx).TriggerCondition, info(hwTriggerIdx).TriggerSource);
            
            if strcmp(vidObj.TriggerSource, 'DeviceSpecific') && ...
                    strcmp(vidObj.TriggerCondition, 'DeviceSpecific')
               % If hardware triggering is DeviceSpecific, then the
               % acquisition will still continue because the device
               % specific property has not been set.
                obj.printGeneralInfo('Unable to test Hardware trigger mode because this device requires hardware triggering to be set in a device specific property. For more information refer Image Acquisition Toolbox documentation.');
                testResult.Result = true;
                testResult.FailureStr = sprintf('');
                
            else
                start(vidObj);
                pause(max(obj.FrameUpdateWaitTime, 1/obj.EstimatedAcquisitionFrameRate));
                framesAcquiredAfter = vidObj.FramesAcquired;
                % Verification
                testResult.Result = framesAcquiredAfter == 0;
                testResult.FailureStr = sprintf('Acquistion started without any trigger for hardware triggering mode.');
                stop(vidObj);
            end
        catch exception
            testResult.Result = false;
            testResult.FailureStr = sprintf('Unable to test Hardware trigger mode because of the following error: %s', exception.message);
            obj.printGeneralInfo(sprintf('Unable to test Hardware trigger mode because of the following error: %s', exception.message));
            obj.printGeneralInfo(sprintf('\nTo run this test manually, perform the following operations:'));
            obj.printGeneralInfo(sprintf('1. Create a VIDEOINPUT object: vidObj = videoinput(''%s'', %d, ''%s'')', obj.AdaptorName, obj.DeviceId, obj.Format));
            obj.printGeneralInfo(sprintf('2. Set Hardware trigger parameters: videoinput(vidObj, ''hardware'', ''%s'', ''%s'')', info(hwTriggerIdx).TriggerCondition, info(hwTriggerIdx).TriggerSource));
            obj.printGeneralInfo('3. Start object: start(vidObj)');
            obj.printGeneralInfo('4. If the above error gets thrown for any of the above steps, correct the error and rerun. For more information refer Image Acquisition Toolbox documentation.');
            obj.printGeneralInfo('5. Check Number of Frames Acquired: vidObj.FramesAcquired');
            obj.printGeneralInfo('6. Wait for a few seconds and check Number of Frames Acquired again: vidObj.FramesAcquired');
            obj.printGeneralInfo('7. The two values should be the same, this indicates that the object is waiting for a Hardware trigger to acquire frames');
            obj.printGeneralInfo('8. To acquire frames, trigger using external resources');
            obj.printGeneralInfo('9. To stop, run: stop(vidObj); delete(vidObj); clear vidObj;');
        end
        
    else
            testResult.Result = true;
            testResult.FailureStr = sprintf('"%s" device does not support Hardware trigger mode.', obj.DeviceName);
    end
    
    % Publish results
    obj.printResult(testResult);
    
    % CLEANUP: 
    obj.cleanupTest;    
    
end

