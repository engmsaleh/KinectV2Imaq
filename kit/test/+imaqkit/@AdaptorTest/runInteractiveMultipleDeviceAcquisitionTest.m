function runInteractiveMultipleDeviceAcquisitionTest(obj, deviceId1, deviceFormat1, deviceId2, deviceFormat2)
%runInteractiveMultipleDeviceAcquisitionTest(obj, deviceId1, deviceFormat1, deviceId2, deviceFormat2):
%  This test checks simultaneous acquisition from two devices. Before
%  running this test, at least two devices should be connected and their
%  Device ID and Format Information obtained using IMAQHWINFO. This test is
%  run using an object of type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runInteractiveMultipleDeviceAcquisitionTest(obj, deviceId1, deviceFormat1, deviceId2, deviceFormat2)
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    narginchk(5, 5);

    % Entry message
    obj.printBanner('Testing simultaneous multi-device acquisition (interactive)');
    infoStr = sprintf('This test checks simultaneous acquisition from two devices. Before running this test, at least two devices should be connected and their Device Id and Format Information obtained using IMAQHWINFO.');
    obj.printTestDescription(infoStr);

    % SETUP
    vidObj1 = videoinput(obj.AdaptorName, deviceId1, deviceFormat1);
    vidObj2 = videoinput(obj.AdaptorName, deviceId2, deviceFormat2);
    
    % Preview both devices
    preview(vidObj1);
    preview(vidObj2);
    
    % Wait for user input to confirm that the previews are fine
    input('\nPress ENTER when you have verified that the two previews are working fine:');
    
    % CLEANUP: 
    closepreview(vidObj1);
    closepreview(vidObj2);
    obj.cleanupTest;
    
end

