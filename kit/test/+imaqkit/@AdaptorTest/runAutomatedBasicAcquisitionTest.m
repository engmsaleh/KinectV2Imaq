function runAutomatedBasicAcquisitionTest(obj)
%runAutomatedBasicAcquisitionTest: This test first checks image
%  acquisition for specified number of frames. It next checks that
%  continuous image acquisition can be stopped. This test is run using an
%  object of type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runAutomatedBasicAcquisitionTest
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    % Entry message
    obj.printBanner('Testing image acquisition')
    infoStr = sprintf('This test first checks image acquisition for specified number of frames. It then checks that continuous image acquisition can be stopped.');
    obj.printTestDescription(infoStr);

    % SETUP
    vidObj = obj.setupTest;
    expNumberOfAcquiredFramesPerTrigger = vidObj.FramesPerTrigger * vidObj.FrameGrabInterval + vidObj.TriggerFrameDelay;
    expNumberOfAcquiredFramesTotal = (vidObj.TriggerRepeat + 1) * expNumberOfAcquiredFramesPerTrigger;
    waitTimeBuffer = 5;   % Wait for an extra 5 seconds
    loggingWaitTime = waitTimeBuffer + expNumberOfAcquiredFramesTotal / obj.EstimatedAcquisitionFrameRate;
    
    %============== Basic acquisition with implicit stop =================%
    
    % Acquire and IMAQMONTAGE data
    start(vidObj);
    wait(vidObj, loggingWaitTime, 'running');
    framesAvailable = vidObj.FramesAvailable;
    framesAcquired = vidObj.FramesAcquired;
    imageData = getdata(vidObj);
    figure('Name','Montage of Acquired Images');
    h = imaqmontage(imageData);
    title(sprintf('Displaying %d frames acquired with %s format', vidObj.FramesPerTrigger, strrep(obj.Format, '_', '\_')));
    pause(obj.PreviewWaitTime);   % Wait some time to allow users to see data
    close(get(get(h, 'Parent'), 'Parent'));  % Close the imaqmontage window
    
    % Verification
    testResult.Result = (framesAvailable == vidObj.FramesPerTrigger) && ...
                        (framesAcquired == vidObj.FramesPerTrigger);
    testResult.FailureStr = sprintf('FramesAvailable/FramesAcquired does not match with expected number of frames for limited acquisition.');
    
    %============== Basic acquisition with explicit stop =================%
    
    % Set up acquisition parameters
    vidObj.FramesPerTrigger = inf;
    % Start object and stop after few seconds
    start(vidObj);
    % Wait for at least 11 frames to be acquired, one more than the default
    % value of 10 to make sure that the acquisition is free running
    while(vidObj.FramesAvailable < 11)
        pause(0.01);
    end
    stop(vidObj);
    wait(vidObj, loggingWaitTime, 'running');   % The logging time does not really apply here, just re-using from previous calculation
    % Check that FramesAcquired is not getting updated
    framesAcquiredBefore = vidObj.FramesAcquired;
    pause(max(obj.FrameUpdateWaitTime, 1 / obj.EstimatedAcquisitionFrameRate));    % Wait for some time
    framesAcquiredAfter = vidObj.FramesAcquired;
    
    % Verification
    testResult(end + 1).Result = framesAcquiredBefore == framesAcquiredAfter;
    testResult(end).FailureStr = sprintf('Acquisition continued even after running STOP.');
    
    % Publish results
    obj.printResult(testResult);
    
    % CLEANUP: 
    obj.cleanupTest;    
    
end

