% purduce two vector that will show leg movement and 

function [LM_i, PLM_i] = LMandPLM(LM,PLM,Acc_mag)

LM_i = [];
PLM_i = [];

[row,col] = size(Acc_mag);
[rowl,coll] = size(LM);
[rowp,colp] = size(PLM);
j=1; k=1;


for i = 1:row
  
  % give it a 1 is it is consider to be a leg movement at that index, 0 otherwise
  if ~isempty(LM(j,1)) && LM(j,1)<=i && i<=LM(j,2)
    LM_i = [LM_i;1];
    if LM(j,2) ==i && j!=rowl
      j = j+1;
    end
  else
    LM_i = [LM_i;0];
  end
  
  % give it a 1 is it is consider to be a PLM at that index, 0 otherwise
  if ~isempty(PLM(k,1)) && PLM(k,1)<=i && i<=PLM(k,2)
    PLM_i = [PLM_i;1];
    if PLM(k,2) ==i && k!=rowp
      k = k+1;
    end
  else
    PLM_i = [PLM_i;0];
  end
    
end



endfunction
