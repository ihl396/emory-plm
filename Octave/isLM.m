% check is the leg movement could be consider into PLM

function LM = isLM()
LM = [];
onset = 1;
decay = 0.7;
LM_start = 0.5;
LM_end = 10;
PLM_start = 5;
PLM_end = 90;
Acc_mag = dlmread( 'log_magnitude.txt' ,',');
times = dlmread('log_magnitude_times.txt',',');

%determines what indices are at and above the onset that would be
%characterized as a leg movement
onset_mov = find(Acc_mag >= onset);

%determines what indices are at and below the decay that would be
%charactereized as NOT a leg movement
decay_mov = find(Acc_mag <= decay);

onset_i = 1; %this will be 1 because this is the very first time that a LM >= onset appears


%if isempty(onset_mov) == 1 || isempty(decay_mov) % there is no leg movement
%    decay_i = -1;
%else
    % find the first indices after the onset_is that is a decay
    % meaning find the first leg movement
%    onset_i = find(onset_mov < decay_mov(1), end);  
%end

decay_index = 1;
onset_possible = find(onset_mov < decay_mov(decay_index));
if (length(onset_possible) > 0)
      for y = 1:1:length(onset_possible)
        onset_index = y;
        duration = (times(decay_mov(decay_index)) - times(onset_mov(onset_possible(onset_index))))/1000;
        if (LM_start <= duration) && (duration <= LM_end)
            LM = [LM; onset_mov(onset_possible(onset_index)), decay_mov(decay_index), times(onset_mov(onset_possible(onset_index)))/1000,times(decay_mov(decay_index))/1000, duration];
            break;
        endif
      endfor
endif

for x = 2:length(decay_mov)
    decay_index = x;
    onset_possible = find((onset_mov < decay_mov(decay_index)) & (onset_mov > decay_mov(decay_index-1)));
    if (length(onset_possible) > 0)
      for y = 1:1:length(onset_possible)
        onset_index = y;
        duration = (times(decay_mov(decay_index)) - times(onset_mov(onset_possible(onset_index))))/1000;
        if (LM_start <= duration) && (duration <= LM_end)
            LM = [LM; onset_mov(onset_possible(onset_index)), decay_mov(decay_index), times(onset_mov(onset_possible(onset_index)))/1000, times(decay_mov(decay_index))/1000, duration];
            break;
        endif
      endfor
    endif
          
endfor

% continue to characterize for LM until it is over
%while(1) 
%    if decay_i == -1 % no leg movement, break out the loop
%        break;
%    end
%    %gets the time difference
%    duration = (times(decay_mov(decay_i)) - times(onset_mov(onset_i)))/1000;
%    %duration = etime(date(decay_mov(decay_i),:), date(onset_mov(onset_i),:)); 
%    %characterization of a leg movement with duration
%    if (LM_start <= duration) && (duration <= LM_end)
%        % if it is a leg movement, put it into the legmovement array
%        LM = [LM; Acc_mag(onset_mov(onset_i)), Acc_mag(decay_mov(decay_i)), duration];
%    end
%    
%     % updates which indices to look at
%     % find the next start time of leg movement
%    onset_i = find(onset_mov > decay_mov(decay_i), 1);
%    
%    % if you are at the end of the indices, then you break out of the loop
%    if isempty(onset_i) == 1 
%        break;
%    end
%    
%    % update the decay indices to the next indices
%    % find the next leg movement end time
%    decay_i = find(decay_mov > onset_mov(onset_i), 1);
%    
%    % if the next indices is empty, then you reached the end, so break out
%    % of the loop
%    if isempty(decay_i) == 1
%        break;
%    end
%end

end
