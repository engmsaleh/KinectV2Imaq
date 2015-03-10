classdef AdaptorTest
%ADAPTORTEST Create IMAQ Adaptor Test object and test Image Acquisition
%  Toolbox connectivity with cameras/framegrabbers. This class is not
%  instantiated directly. Call imaqkit.AdaptorTest.createTest to
%  instantiate
%
%  Properties:
%    
%    AdaptorName                         - Name of Image Acquisition Toolbox Adaptor
%    DeviceId                            - Device ID
%    Format                              - Video format used for acquisition or Camera file
%    DeviceName                          - Device name
%    VendorDriverDescription             - Device driver name
%    VendorDriverVersion                 - Device driver version
%    EstimatedAcquisitionFrameRate       - Estimated frame rate
%    ConciseLog                          - Verbosity of log (default false)
%  
%  Methods:
%
%    Create Test:
%
%      createTest                                  - create imaqkit.AdaptorTest object
%
%    Automated Tests:
%
%      runAllAutomatedTests                        - run all automated tests
%      runAutomatedObjectCreationAndPreviewTest    - run automated object creation and preview test
%      runAutomatedBasicAcquisitionTest            - run automated acquisition test
%      runAutomatedROITest                         - run automated region of interest test
%      runAutomatedRepeatedAcquisitionTest         - run automated repeated acquisition test
%      runAutomatedImmediateTriggerTest            - run automated trigger test for immediate triggering
%      runAutomatedManualTriggerTest               - run automated trigger test for manual triggering
%      runAutomatedHardwareTriggerTest             - run automated trigger test for hardware triggering
%
%    Interactive Tests:
%
%      runInteractiveDevicePropertiesTest          - run interactive device properties test
%      runInteractiveMultipleDeviceAcquisitionTest - run interactive multiple device acquisition test
%
%  Example:
%    % Get installed hardware information recognizable using 'winvideo'
%    adaptor
%    info = imaqhwinfo('winvideo');
%    % Get information about available formats
%    info.DeviceInfo.SupportedFormats
%    % Choose a format, for example 'MJPG_800x600', and create test object
%    testObj = imaqkit.AdaptorTest.createTest('winvideo', 1, 'MJPG_800x600', 15);
%    % Run individual test
%    testObj.runObjectCreationAndPreviewTest;
%    % Run all automated tests
%    testObj.runAllAutomatedTests;
%
% See also: imaqhwinfo, imaqkit.AdaptorTest.createTest

% Copyright 2011-2013 The MathWorks, Inc.
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Properties
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    properties (SetAccess = private, GetAccess = public)
        %AdaptorName: Adaptor name (string), e.g. 'winvideo', 'gige',
        %  provided by user
        AdaptorName; 
        %DeviceId: Device id (number), e.g. 1, provided by user
        DeviceId;          
        %Format: Format (string), e.g. 'MJPG_960x720', 'YUY2_1280x720',
        %  provided by user
        Format;            
        %DeviceName: Name of device, e.g. USB Video Device, obtained based
        % on AdaptorName, DeviceId and Format
        DeviceName;                   
        %VendorDriverDescription: Driver name, e.g. Windows WDM Compatible
        %  Driver, obtained based on AdaptorName, DeviceId and Format
        VendorDriverDescription;      
        %VendorDriverVersion: Driver version, e.g. DirectX 9.0, obtained
        %  based on AdaptorName, DeviceId and Format 
        VendorDriverVersion;          
        %EstimatedAcquisitionFrameRate: Estimated acquisition rate, e.g. 15
        %  frames per second, provided by user
        EstimatedAcquisitionFrameRate;
    end
            
    properties 
        ConciseLog = false;        % Flag for test log (boolean)
                                   % true - concise/non-verbose log
                                   % false - verbose log
    end
    
    properties (Hidden, Access = private)
        % Max length of display string in log, default 80, re-defined
        % during object creation
        DisplayStringLength = 80;       
        % Wait time for previewing
        PreviewWaitTime = 5;
        % Wait time for frame update
        FrameUpdateWaitTime = 3;
    end
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Constructor
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    methods(Access = private)
        function obj = AdaptorTest() 
            % Blank constructor to create an AdaptorTest object
        end
    end
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Tests
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    methods(Access = public)
        % Automated tests
        runAllAutomatedTests(obj);              
        runAutomatedVideoPreviewTest(obj);
        runAutomatedBasicAcquisitionTest(obj);
        runAutomatedROITest(obj);
        runAutomatedRepeatedAcquisitionTest(obj);
        runAutomatedImmediateTriggerTest(obj);
        runAutomatedManualTriggerTest(obj);
        runAutomatedHardwareTriggerTest(obj);
        % Interactive tests
        % These tests need to be run individually
        runInteractiveDevicePropertiesTest(obj);
        runInteractiveMultipleDeviceAcquisitionTest(obj, deviceId1, deviceFormat1, deviceId2, deviceFormat2);
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Setup & Cleanup Methods
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    methods(Access = private)
        
        function vidObj = setupTest(obj)
            % Call imaqreset at the beginning of each test to initialize
            % the adaptor states
            imaqreset;
            % Create the video input object (to be used in the test)
            vidObj = videoinput(obj.AdaptorName, obj.DeviceId, obj.Format);
        end
        
        function cleanupTest(~) 
            % Delete all video input objects
            delete(imaqfind);
            imaqreset;
        end
        
    end
            
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Static Methods
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    methods (Static, Access = public)
        
        function obj = createTest(adaptorName, deviceId, format, estimatedAcquisitionFrameRate)
            %imaqkit.AdaptorTest.createTest creates an IMAQ Adaptor Test
            %  object. It returns an imaqkit.AdaptorTest object that can be
            %  used to run individual or all test points. 
            %
            %  TESTOBJ = imaqkit.AdaptorTest.createTest(ADAPTORNAME, DEVICEID, FORMAT, ESTIMATEDACQUISITIONFRAMERATE)
            %  returns a test object to test a device with specified adaptor,
            %  ID and format. ADAPTORNAME is the name of the adaptor to be used
            %  to communicate with the device, e.g. 'winvideo', 'gige' etc.
            %  DEVICEID is the numeric id of the device. FORMAT is the video
            %  format to acquire images in. To know more about DEVICEID and
            %  available FORMATs, type imaqhwinfo()
            %
            %  Example:
            %
            %    % To identify a USB camera with the 'winvideo' adaptor,
            %    % get the installed hardware information:
            %    info = imaqhwinfo('winvideo')
            %
            %    % Identify device ID:
            %    info.DeviceIDs
            %
            %    % Get the supported format information for the USB camera
            %    % under test ("idx" refers to Device Id identified above
            %    % for the camera under test; if it is the first camera
            %    % then use idx = 1
            %    info.DeviceInfo(idx).SupportedFormats
            %
            %    % Choose a format, for example 'MJPG_800x600' and create
            %    % test object:
            %    testObj = imaqkit.AdaptorTest.createTest('winvideo', 1, 'MJPG_800x600', 15);
            % 
            %    % To run individual tests, call specific test methods by
            %    % typing 
            %    testObj.runObjectCreationAndPreviewTest;
            %    testObj.runInteractiveDevicePropertiesTest;
            %
            %    % By default, tests create verbose logs. To run tests with
            %    % concise logs set ConciseLog property to true and then
            %    % run tests
            %    testObj.ConciseLog = true;
            %    testObj.runObjectCreationAndPreviewTest;
            %
            %    % Get the list of tests that can be run
            %    methods(testObj)
            %
            %  See also imaqhwinfo, imaqkit.AdaptorTest
        
            % Check inputs
            narginchk(4, 4);
            
            % Validate inputs
            try
                vidObj = videoinput(adaptorName, deviceId, format);
                info = imaqhwinfo(vidObj);
                delete(vidObj);
                clear vidObj;
            catch  %#ok<CTCH>
                error('Adaptor: ''%s'' / Device Id: %d / Format: ''%s'' combination is invalid. Run IMAQHWINFO to find the correct device and to obtain a valid combination of adaptor name, device id and supported formats', ...
                                 adaptorName, deviceId, format);
            end
                
            % Create object and define properties
            obj = imaqkit.AdaptorTest();
            obj.AdaptorName = adaptorName;
            obj.DeviceId = deviceId;
            obj.Format = format;
            obj.DeviceName = info.DeviceName;
            obj.VendorDriverDescription = info.VendorDriverDescription;
            obj.VendorDriverVersion = info.VendorDriverVersion;
            obj.EstimatedAcquisitionFrameRate = estimatedAcquisitionFrameRate;
                        
            % Store the display string length based on the current command
            % window size
            windowSize = matlab.desktop.commandwindow.size;
            obj.DisplayStringLength = min(windowSize(1), obj.DisplayStringLength);
            
        end
        
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Hidden Methods
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    methods (Hidden)
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Print functions
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        function outStr = wrapDisplayString(obj, inStr)
            %  Wraps the display string to width specied in
            %  DisplayStringLength  
           
            strLength = obj.DisplayStringLength;   
            inStr = strtrim(inStr);
            exp = sprintf('(\\S\\S{%d,}|.{1,%d})(?:\\s+|$)', strLength, strLength);
            tokens = regexp(inStr, exp, 'tokens').';
            get_contents = @(f) strcat(f{1},'\n');
            outStrCell = cellfun(get_contents, tokens, 'UniformOutput', false);
            outStrCell = deblank(outStrCell);
            outStr = [outStrCell{:}];

        end
        
        function disp(obj)
            % Display method for test information
            % Example:
            %     Test Information: 
            %
            %                 Device Name: USB Video Device
            %                Adaptor Name: winvideo
            %                 Driver Name: Windows WDM Compatible Driver
            %              Driver Version: DirectX 9.0
            %           Format Under Test: MJPG_800x600
                       
            exp = sprintf('\\n%%%ds: %%s', floor(obj.DisplayStringLength / 4));
            fprintf(exp,'Test Information');
            fprintf('\n');
            exp = sprintf('\\n%%%ds: %%s', floor(obj.DisplayStringLength / 2));
            fprintf(exp, 'Device Name', obj.DeviceName); %#ok<*CTPCT>
            fprintf(exp, 'Adaptor Name', obj.AdaptorName);
            fprintf(exp, 'Driver Name', obj.VendorDriverDescription);
            fprintf(exp, 'Driver Version', obj.VendorDriverVersion);
            fprintf(exp, 'Format Under Test', obj.Format);
            fprintf('\n\n');
            
        end   
        
        function printBanner(obj, bannerStr)
            % Print Banner (only used for verbose mode)
            if obj.ConciseLog
                return;
            end
            fprintf('\n');
            testName = imaqkit.AdaptorTest.getTestName;
            printStr = sprintf('%s: %s', testName, bannerStr);
            printStr = sprintf('%s\n%s\n%s', repmat('=', 1, obj.DisplayStringLength), printStr, repmat('=', 1, obj.DisplayStringLength)); %#ok<NASGU>
            % Print log
            fprintf('%s\n', sprintf(obj.wrapDisplayString(printStr)));            
            
        end                
        
        function printTestDescription(obj, testDesc)
            % Print Test Description (only used for verbose mode)
            if obj.ConciseLog
                return;
            end
            % Print test Information that describes the test (only used for verbose mode)
            printStr = sprintf('TEST DESCRIPTION: %s', testDesc);
            % Print log
            fprintf('%s\n', sprintf(obj.wrapDisplayString(printStr)));            
            
        end                
        
        function printResult(obj, testResult)
            % Print Result statements
            if obj.ConciseLog
                fprintf('\n');
            end
            testName = imaqkit.AdaptorTest.getTestName;
            if all([testResult(:).Result])
                % All tests passed
                printStr = sprintf('%s: PASS.', testName);
            else
                % There was a failure
                printStr = sprintf('%s: FAIL.', testName);
                for idx = 1:length(testResult)
                    % Print individual failures
                    if ~testResult(idx).Result
                        printStr = sprintf('%s %s', printStr, testResult(idx).FailureStr);
                    end
                end
            end
            % Print log
            fprintf('%s\n', sprintf(obj.wrapDisplayString(printStr)));            
            
        end                
        
        function printGeneralInfo(obj, generalInfo)
            % Print General Description (only used for verbose mode)
            if obj.ConciseLog
                return;
            end
            % Print log
            printStr = generalInfo;
            fprintf('%s\n', sprintf(obj.wrapDisplayString(printStr)));            
            
        end                
        
        function printNote(obj, note)
            % Print Any Notes (only used for verbose mode)
            if obj.ConciseLog
                return;
            end
            % Print log
            printStr = sprintf('NOTE: %s', note);
            fprintf('%s\n', sprintf(obj.wrapDisplayString(printStr)));            
            
        end                
        
    end
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Hidden and Static Methods
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    methods (Static, Hidden)
        
        function testName = getTestName()
            % Get test name
            testName = '';
            st = dbstack;
            for idx = 1:length(st)
                if ~isempty(strfind(st(idx).file, 'runAutomated')) || ...
                        ~isempty(strfind(st(idx).file, 'runInteractive')) 
                    testName = st(idx).file;
                    break;
                end
            end
            
        end
            
    end
    
end

