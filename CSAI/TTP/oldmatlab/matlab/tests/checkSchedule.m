function [bool ] = checkSchedule( schedule )
%CHECKSCHEDULE Summary of this function goes here
%   Detailed explanation goes here

[teams weeks] = size(schedule);
weeks2 = 1:weeks;
t = 1:teams;

dimCheck = all([teams weeks] == size(schedule));
allDifferent = all(sum(abs(schedule)) == sum(t));
sumHorizontal = all(sum(schedule,2) == 0);
twoPosCheck = all(sum(schedule > 0) == teams/2);
% sortCheck = all(all(sort(abs(schedule)) == repmat(t,1,weeks2)));
% sort2check = all(~any(sort(abs(schedule),2) == repmat(t,1,weeks2)));

if  dimCheck && allDifferent && twoPosCheck && sumHorizontal %&& sortCheck && sort2check 
    
    bool = 1;
    disp('generation of random schedule succeeded');
else
    disp('generation of random schedule FAILED');
    bool = 0;
end

end

