% convert time stamp using start time and end time

function [convertT,off] = convertTime(startT,endT,r)

convertT = [startT];
temp = startT;
off = 1; % variable to determine if the microcontroller's clock is off

for i = 1:(r-1)
  temp = addtodate(temp, 100, 'millisecond'); % add 100 millisecond to the time
  convertT=[convertT;temp]; % put the time to a vector called "convertT"
end

% check the end time and our calculated time if they are the same
if etime(datevec(convertT(end,1)),datevec(endT)) == 0
  off = 0;
end
% convert conertT to in type of date vector
convertT=datevec(convertT);

endfunction
