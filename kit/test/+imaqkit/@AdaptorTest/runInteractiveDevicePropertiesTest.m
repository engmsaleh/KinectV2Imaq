function runInteractiveDevicePropertiesTest(obj)
%runInteractiveDevicePropertiesTest: This test checks device properties
%  interactively. When run, this test will bring up a running preview
%  window and a property inspector. Users can modify the properties from
%  the property inspector and observe the changes in the preview window.
%  This test is run using an object of type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runInteractiveDevicePropertiesTest
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    % Entry message
    obj.printBanner('Testing device properties (interactive)');
    infoStr = sprintf('This test checks device properties interactively. When run, this test will bring up a running preview window and a property inspector. Users can modify the properties from the property inspector and observe the changes in the preview window.');
    obj.printTestDescription(infoStr);

    % SETUP
    vidObj = obj.setupTest;
    
    % Preview the video and bring up the inspector for the source 
    preview(vidObj);
    inspect(vidObj.Source);
    
    % Wait for user input that video properties test is complete
    obj.printGeneralInfo('Use the Property Inspector to modify device property values. Observe the results in the preview window.');
    input('\nPress ENTER when the interactive device properties test is complete:');
    
    % CLEANUP: 
    obj.cleanupTest;   
    
end

