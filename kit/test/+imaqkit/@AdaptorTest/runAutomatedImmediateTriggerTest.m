function runAutomatedImmediateTriggerTest(obj)
%runAutomatedImmediateTriggerTest: This test checks acquiring images in
%  Immediate trigger mode. It checks the number of acquired frames for
%  acquisition with immediate trigger. This test is run using an object of
%  type imaqkit.AdaptorTest. 
%
%  Example:
%
%    obj.runAutomatedImmediateTriggerTest
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    % Entry message
    obj.printBanner('Testing immediate triggering');
    infoStr = sprintf('This test checks acquiring images in immediate trigger mode. It checks the number of acquired frames for  acquisition with immediate trigger.');
    obj.printTestDescription(infoStr);

    % SETUP
    vidObj = obj.setupTest;

    % Setup trigger parameters
    vidObj.TriggerFrameDelay = 3; 
    vidObj.TriggerRepeat = 2;
    vidObj.FrameGrabInterval = 2;
    vidObj.FramesPerTrigger = 5;
    waitTimeBuffer = 5;
    expNumberOfLoggedFrames = (vidObj.TriggerRepeat + 1) * vidObj.FramesPerTrigger;
    expNumberOfAcquiredFramesPerTrigger = vidObj.FramesPerTrigger * vidObj.FrameGrabInterval + vidObj.TriggerFrameDelay;
    expNumberOfAcquiredFramesTotal = (vidObj.TriggerRepeat + 1) * expNumberOfAcquiredFramesPerTrigger;
    
    % ==================== Test immediate trigger ========================%
    start(vidObj);
    waitTime = waitTimeBuffer * expNumberOfAcquiredFramesTotal/obj.EstimatedAcquisitionFrameRate;
    wait(vidObj, waitTime, 'running'); 
 
    % Verification
    testResult.Result = expNumberOfLoggedFrames == vidObj.FramesAcquired;
    testResult.FailureStr = sprintf('Number of frames acquired did not match with expected for immediate trigger mode.');
    
    % Publish results
    obj.printResult(testResult);
    
    % CLEANUP: 
    obj.cleanupTest;    
    
end

