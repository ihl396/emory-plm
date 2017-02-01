% get raw data from the filepath that is given

function [startT,rawdata,endT] = getRawdata(filepath)

fileID = fopen(filepath,'r'); # open the raw data file

% record the start time
line=fgets(fileID);
startT = line;

% record the first line of data
line=fgets(fileID);
rawdata = textscan(line,'%f %f %f %f %f %f %f %f %f %f','Delimiter', ',');


while ~feof(fileID)% check if we have reached the end of file
  line=fgets(fileID); % continue reading data from file
  if ~feof(fileID)  % check if we have reached the end of file
    % continue recording raw data
    line =textscan(line,'%f %f %f %f %f %f %f %f %f %f','Delimiter', ',');
    rawdata = [rawdata;line];
  else
    % record the end time
    endT = line;
  end
end


milis = str2num(startT(end-4:end));
startT = datevec(startT(1:end-6),'yyyy-mm-dd HH:MM:SS');
startT= addtodate(datenum(startT), milis, 'millisecond');

rawdata = cell2mat(rawdata);

milis = str2num(endT(end-2:end));
endT = datevec(endT(1:end-4),'yyyy-mm-dd HH:MM:SS');
endT= addtodate(datenum(endT), milis, 'millisecond');

fclose(fileID);
endfunction
