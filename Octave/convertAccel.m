% converting accelerometer value from raw data to unit in g

function [AccX,AccY,AccZ] = convertAccel(rawx,rawy,rawz)

% has to change based on acceleromter
AccX = rawx/3000;
AccY = rawy/3000;
AccZ = rawz/3000;

endfunction
