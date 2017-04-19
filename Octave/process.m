% To run the program, type in the command line process('filepath')
% filepath is where the rawddata.csv and parameter.csv atan
% example: process('G:/Leon/Georgia Tech/Fall 2016/ECE 4012/PLM new octave')

function [retval] = process (filepath)

%% Get parameter file under the filepath
%%parameterpath = strcat(filepath,'/parameter.csv'); %%complete parameter file path
%%[onset,decay,LM_start,LM_end,PLM_start,PLM_end]=getParameter (parameterpath);

onset = 1
decay = 0.7
LM_start = 0.5
LM_end = 10
PLM_start = 5
PLM_end = 90

%% Get raw data file under the filepath
%rawdatapath = strcat(filepath,'/rawdata.csv'); %%complete raw data file path
%[startTime,rawdata,endTime] = getRawdata(rawdatapath);

%% create all the time stamp for raw data based on 10 Hz
%[row,columns] = size(rawdata);
%[convertTime,off] = convertTime(startTime,endTime,row);

%% convert raw acceleroemter date to unit in g
#rawAccx = rawdata(:,2); rawAccy = rawdata(:,3); rawAccz = rawdata(:,4);
#[AccX,AccY,AccZ] = convertAccel(rawAccx,rawAccy,rawAccz);

%calculates the magnitude of the accelerometer values
#Acc_mag = sqrt(AccX.^2 + AccY.^2 + AccZ.^2);

% calls the is_LM function to determine if the individual events can be
% considered a leg movement. If it is, then it will be placed in the
% LM array (start indices, end indices, duration)
LM = isLM(LM_start, LM_end, Acc_mag, convertTime, onset, decay);

% calls the isPLM function to determine if the LM_series contains any
% periodic leg movements (start indicies, end indicies, Periodic Index)
PLM = isPLM( LM, PLM_start, PLM_end, convertTime);

%% calls the convertRotation function to compute the actual rotation of leg
[heading,pitch,roll] = convertRotation(AccX, AccY, AccZ);

% calls the isStand function to determine if pateint is standing or not
% 1 for standing, 0 for not standing
Stand = isStand(heading,pitch,roll);

% calls the LMandPLM to represent the leg movement and PLM in 1 or 0
% 1 is standing, 0 is not standing
% 1 is PLM, 0 is not PLM
[LM_i, PLM_i] = LMandPLM(LM,PLM,Acc_mag);

% create a PLM summary file for GUI
% it contains start time of PLM, end time of PLM, and Periodic Index of the PLM
%Header = 'Start Time,End Time,Periodic Index';
fileID = fopen('PLM Summary.csv', 'w');
%fprintf(fileID,'%s\r\n',Header);
[row,col] = size(PLM);
for i = 1:row
  startPLM = datestr(convertTime(PLM(i,1),:));
  endPLM = datestr(convertTime(PLM(i,2),:));
  fprintf(fileID, '%s,%s\n', startPLM, endPLM);
end
fclose(fileID);

% create a Output file for documentation of the data
% it contains timestamp
% rawAccx, rawAccy, rawAccz
% magnitude of Acceleration, Leg movemnt or not (1/0), PLM or not(1/0),
% rawdata for gyroscope
% rawdata for magetnometer
% calculates rotation angel (heading,pitch,roll)
% standing or not (1/0)

fileID = fopen('Output.csv', 'w');
[row,col] = size(convertTime);
for i = 1:row
  fprintf(fileID, '%s,',datestr(convertTime(i,:)));
  fprintf(fileID, '%f,%f,%f,', rawdata(i,2),rawdata(i,3),rawdata(i,4));
  fprintf(fileID, '%f,%f,%f,', Acc_mag(i,1), LM_i(i,1),PLM_i(i,1));
  fprintf(fileID, '%f,%f,%f,', rawdata(i,5),rawdata(i,6),rawdata(i,7));
  fprintf(fileID, '%f,%f,%f,', rawdata(i,8),rawdata(i,9),rawdata(i,10));
  fprintf(fileID, '%f,%f,%f,',heading(i,1),pitch(i,1),roll(i,1));
  fprintf(fileID,'%f\r\n',Stand(i,1));
end
fclose(fileID);

endfunction
