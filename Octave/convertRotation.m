%calculate heading,pitch,roll from acceleroemter value

function [heading,pitch,roll] = convertRotation (AccX, AccY, AccZ)

Acc_magx = sqrt(AccX.^2);
Acc_magy = sqrt(AccY.^2);
Acc_magz = sqrt(AccZ.^2);

roll = [];
pitch =[];
heading = [];


for i = 1:length(AccX)
  roll = [roll;atan2(AccY(i,1), AccZ(i,1))];
  pitch = [pitch;atan2(-AccX(i,1), sqrt(AccY(i,1)^2 + AccZ(i,1)^2))];
  
  
  if (Acc_magy(i,1) == 0)
    if (Acc_magx(i,1) < 0)
      heading = [heading; pi];
    else
      heading = [heading; 0];
    endif
  else
    r = atan2(Acc_magx(i,1), Acc_magy(i,1));
    if r>pi
      heading = [heading;(r-2*pi)];
    elseif r< -pi
      heading = [heading;(r+2*pi)];
    elseif r<0
      heading = [heading;(r+2*pi)];
    else
      heading = [heading;r];
    endif
  endif
  
end

% change heading,pitch,roll to be in unit of degree
heading = heading.*180.0./pi;
pitch = pitch.*180.0./pi;
roll = roll.*180.0./pi;

endfunction
