% charactrize PLM

function PLM = isPLM(LM)

PLM = [];
PLM_start = 5;
PLM_end = 90;
count = 0;

%determines if it is a PLM series with the specified parameters
if isempty(LM) == 1 || length(LM)<4
    return
else
    %creates the first value for the temp variable which is the first leg movement
    legMovement_1 = [LM(1,:)]; 
end

for i = 2:length(LM)
    legMovement_2 = [LM(i,:)];
    
    %this gets the interval between the start of one LM and beginning of the next LM
    interval = legMovement_2(3) - legMovement_1(3);
    
    if (PLM_start <= interval) && (interval <= PLM_end) %determines if it fits a PLM
      temp = [temp; legMovement_1];
      count = count + 1;
    else
      if (count >= 4)
        PLM = [PLM, temp];
      end
      temp = [];
      count = 0;
    end
    
    legMovement_1 = legMovement_2
    
end

end
