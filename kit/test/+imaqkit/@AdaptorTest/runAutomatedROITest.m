function runAutomatedROITest(obj)
%runAutomatedROITest: This test checks setting the Region of Interest to a
%  value different from the default value and then acquiring data. It also
%  checks setting ROI values using X and Y offsets. This test is run using
%  an object of type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runAutomatedROITest
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.


    % Entry message
    obj.printBanner('Testing image acquisition with different Region of Interest');
    infoStr = sprintf('This test checks setting the Region of Interest to a value different from the default value and then acquiring data. It also checks setting ROI values using X and Y offsets.');
    obj.printTestDescription(infoStr);
    noteStr = sprintf('Since sometimes cameras do not allow all ROI settings, you may see a warning message indicating the same.');
    obj.printNote(noteStr);
    
    % SETUP
    vidObj = obj.setupTest;
    testResult.FailureStr = '';
    
    % Obtain current ROI information and calculate sweep settings
    origROI = vidObj.ROIPosition;
    imageWidth = origROI(3);
    imageHeight = origROI(4);
    numWidthSweeps = 2;
    numHeightSweeps = 2;
    stepWidth = floor(imageWidth / numWidthSweeps);
    stepHeight = floor(imageHeight / numHeightSweeps);

    sweepIterations = [];
    for widthIdx = 1:numWidthSweeps
        for heightIdx = 1:numHeightSweeps
            sweepIterations(end+1).XOffset = (widthIdx - 1) * stepWidth;
            sweepIterations(end).XOffset = floor(sweepIterations(end).XOffset/8)*8; % Adjust X offset to a multiple of 8
            sweepIterations(end).YOffset = (heightIdx - 1) * stepHeight;
            sweepIterations(end).YOffset = floor(sweepIterations(end).YOffset/8)*8; % Adjust X offset to a multiple of 8
            sweepIterations(end).Width = stepWidth;
            sweepIterations(end).Height = stepHeight;
        end
    end
    

    % Sweep and preview at different ROI settings
    numIterations = length(sweepIterations);
    testPassed = false(numHeightSweeps*numWidthSweeps, 2);
    
    for iterIdx = 1:numIterations
        expectedROI = [sweepIterations(iterIdx).XOffset, ...
                       sweepIterations(iterIdx).YOffset, ...
                       sweepIterations(iterIdx).Width, ...
                       sweepIterations(iterIdx).Height];
                   
        % Set the ROI and start preview
        vidObj.ROIPosition = expectedROI;
        h = preview(vidObj);
        
        % Obtain the image information
        [displayedImageHeight displayedImageWidth ~]  = size(get(h,'CData'));
        
        % Verification
        newROI = vidObj.ROIPosition;
        
        % Check width and height
        if (displayedImageHeight == newROI(4))&& ...            % Height
                (displayedImageWidth == newROI(3))              % Width
            testPassed(iterIdx, 1) = true;
        else
            testResult.FailureStr = sprintf('%sROI Iteration %d: Width and Height could not be properly set, Expected: [%d %d], Actual: [%d %d]. ', ...
                                            testResult.FailureStr, ...
                                            iterIdx, ...
                                            [newROI(3) newROI(4)], ...
                                            [displayedImageWidth displayedImageHeight]);
        end
        
        % Check x and y offset
        if (newROI(1) == expectedROI(1))&& ...            % X Offset
                (newROI(2) == expectedROI(2))             % Y Offset
            testPassed(iterIdx, 2) = true;
        else
            testResult.FailureStr = sprintf('%sROI Iteration %d: X and Y Offset could not be properly set, Expected: [%d %d], Actual: [%d %d]. ', ...
                                            testResult.FailureStr, ...
                                            iterIdx, ...
                                            [expectedROI(1) expectedROI(2)], ...
                                            [newROI(1) newROI(2)]);
        end
        pause(obj.PreviewWaitTime);
        closepreview
    end
    
    % Verification
    testResult.Result = all(testPassed(:));
    
    % Publish results
    obj.printResult(testResult);
    
    % CLEANUP: 
    obj.cleanupTest;    
    
end

