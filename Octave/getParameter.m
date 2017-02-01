% read in parameter file in the filepath that is given

function [onset,decay,LM_start,LM_end,PLM_start,PLM_end]=getParameter (filepath)

fileID = fopen(filepath,'r'); % open the paramter file
A =  dlmread (fileID,','); % read in each element on the file

% assign each element to the variable
onset = A(1);
decay = A(2);
LM_start = A(3);
LM_end = A(4);
PLM_start = A(5);
PLM_end = A(6);

fclose(fileID);
endfunction
