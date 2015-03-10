function runAutomatedRepeatedAcquisitionTest(obj)
%runAutomatedRepeatedAcquisitionTest: This test checks that a videoinput
%  object can be used to repeatedly acquire data from a video device. This
%  test is run using an object of type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runAutomatedRepeatedAcquisitionTest
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    % Entry message
    obj.printBanner('Testing repeated start/stop of device');
    infoStr = sprintf('This test checks that a videoinput object can be used to repeatedly acquire data from a video device.');
    obj.printTestDescription(infoStr);

    % Set up acquisition parameters
    numIterations = 25;
    
    for idx = 1:numIterations
        
        % Create the video input object
        vidObj = videoinput(obj.AdaptorName, obj.DeviceId, obj.Format); %#ok<*TNMLP>
        % Acquire single frame
        getsnapshot(vidObj);
        % Delete object
        delete(vidObj);
        
    end

    % Verification
    % The purpose of this test is to check that the above operation can be
    % done without any error. This does not require any separate
    % verification
    testResult.Result = true;
    testResult.FailureStr = '';

    % Publish results
    obj.printResult(testResult);
    
end

