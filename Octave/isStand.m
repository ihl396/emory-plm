% determine if pateint is standing or not at the time stamp using heading, pithc, roll
% 1 is standing, 0 is not standing.

function Stand = isStand(heading,pitch,roll)

Stand = [];

for i = 1:length(heading)
    % if the heading is greater than 65 degree than it is not standing.
    if (heading(i,1) >65) || (heading(i,1)<-65) 
      Stand = [Stand;0];
    else
      Stand = [Stand;1];
    endif
endfor


end
