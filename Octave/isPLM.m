% charactrize PLM

function [PLM, PI] = isPLM(LM)

PLM = [];
PLM_start = 5
PLM_end = 90

%determines if it is a PLM series with the specified parameters
if isempty(LM) == 1 || length(LM)<4
    return
else
    %creates the first value for the temp variable which is the first leg movement
    temp = [LM(1,:)]; 
end

PI = 0;
total_interval = 0;

for i = 2:length(LM)
    next = 0;
    
    %this gets the interval between the start of one LM and beginning of the next LM
    interval = etime(date(LM(i,1),:), date(temp(end,1),:)); 
    
    total_interval = total_interval+1; % count the interval for calculating periodic index
    
    if (10<=interval) && (interval <= 90)
      PI = PI+1; % count the interval that is between 10 to 90 second
    end
    
    if (PLM_start <= interval) && (interval <= PLM_end) %determines if it fits a PLM
      temp = [temp; LM(i,:)];
    else
      next = 1;
      
    end
    
    if i ==length(LM) || next == 1
      [row, col] = size(temp);
      if row >= 4 %record the data if it it a PLM
        PLM = [PLM; temp(1:1) temp(end,2)];
      end
      if next == 1
        temp = [LM(i,:)]; %gets next value
      end
    end
    
end
PI = PI/total_interval; % calculate the Perodic index
end
