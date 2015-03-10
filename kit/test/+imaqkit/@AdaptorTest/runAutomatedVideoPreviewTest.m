function runAutomatedVideoPreviewTest(obj)
%runAutomatedVideoPreviewTest: This test creates a videoinput
%  object with the specified parameters and then previews it. It also
%  checks that the preview can be stopped and then closed. This test is run
%  using an object of type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runAutomatedObjectCreationAndPreviewTest
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    % Entry message
    obj.printBanner('Testing basic videoinput object creation and preview');
    infoStr = sprintf('This test creates a videoinput object with the specified parameters and then previews it. It also checks that the preview can be stopped and then closed.');
    obj.printTestDescription(infoStr);

    % SETUP
    vidObj = obj.setupTest;
    
    % Preview the videoinput object for 5 seconds
    h = preview(vidObj);
    pause(obj.PreviewWaitTime);
    
    % Stop preview and make sure that preview is not getting updated
    stoppreview(vidObj);
    imageAfterStop = (get(h, 'CData'));
    pause(max(obj.FrameUpdateWaitTime, 1 / obj.EstimatedAcquisitionFrameRate));   % Wait for some time to check if frames are getting acquired
    imageThreeSecAfterStop = (get(h, 'CData'));
    
    % Verification
    testResult.Result = all(imageAfterStop(:) == imageThreeSecAfterStop(:));
    testResult.FailureStr = sprintf('Preview did not stop after STOPPREVIEW.');
        
    % Close the preview window, this should clear the figure handle
    closepreview;
    
    % Verification
    testResult(end + 1).Result = ~ishandle(h);
    testResult(end).FailureStr = sprintf('Preview window did not close after CLOSEPREVIEW.');

    % Publish results
    obj.printResult(testResult);
    
    % CLEANUP: 
    obj.cleanupTest;   
    
end

