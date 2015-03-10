function runAllAutomatedTests(obj)
%runAllAutomatedTests: This function runs all automated test methods for
%  object of type imaqkit.AdaptorTest.
%
%  Example:
%
%    obj.runAllAutomatedTests
% 
%  See also imaqhwinfo, imaqkit.AdaptorTest.createTest   

% Copyright 2011 The MathWorks, Inc.

    % Display general test information
    obj.disp;
    
    % Run all automated tests
    testList = methods(obj);
    automatedStr = 'runAutomated';
    for idx = 1:length(testList)
       if ~isempty(strfind(testList{idx}, automatedStr))
           obj.(testList{idx});
       end
    end
    
end

