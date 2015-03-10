function runAutomatedManualTriggerTest(obj)
%runAutomatedManualTriggerTest: This test checks acquiring images in
%  Manual trigger mode. It checks that frames are not acquired when
%  the videoinput object is waiting for a trigger as well as number of
%  acquired frames (once triggered). This test is run using an object of
%  type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runAutomatedManualTriggerTest
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    % Entry message
    obj.printBanner('Testing manual triggering');
    infoStr = sprintf('This test checks acquiring images in Manual trigger mode. It checks that frames are not acquired when the videoinput object is waiting for a trigger as well as number of acquired frames (once triggered).');
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
    
    % ======================= Test manual trigger ========================%
    triggerconfig(vidObj, 'manual');
    start(vidObj);
    
    % Check that FramesAcquired is not getting updated
    framesAcquiredBefore = vidObj.FramesAcquired;
    pause(max(obj.FrameUpdateWaitTime, 1/obj.EstimatedAcquisitionFrameRate));
    framesAcquiredAfter = vidObj.FramesAcquired;

    % Verification
    testResult.Result = framesAcquiredBefore == framesAcquiredAfter;
    testResult.FailureStr = sprintf('Acquistion started without any trigger for manual triggering mode.');
    
    for idx = 1:vidObj.TriggerRepeat+1
        % Trigger and acquire data
        trigger(vidObj);
        waitTime = waitTimeBuffer * expNumberOfAcquiredFramesPerTrigger/obj.EstimatedAcquisitionFrameRate;
        wait(vidObj, waitTime, 'logging'); 
        % Check that FramesAcquired is not getting updated
        framesAcquiredBefore = vidObj.FramesAcquired;
        pause(max(obj.FrameUpdateWaitTime, 1/obj.EstimatedAcquisitionFrameRate));
        framesAcquiredAfter = vidObj.FramesAcquired;
        % Verification
        testResult(end + 1).Result = framesAcquiredBefore == framesAcquiredAfter; %#ok<AGROW>
        testResult(end).FailureStr = sprintf('Acquisition continued between manual triggers after specified number of frames were acquired.');
    end
    
    % Verification
    testResult(end + 1).Result = expNumberOfLoggedFrames == vidObj.FramesAcquired;
    testResult(end).FailureStr = sprintf('Number of frames acquired did not match with expected for manual trigger mode.');

    % Publish results
    obj.printResult(testResult);
    
    % CLEANUP: 
    obj.cleanupTest;    
    
end

