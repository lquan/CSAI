function [ So ] = changeSchedule( Si , choice)
%CHANGESCHED Changes the schedule Si, either a random move
%or the given choice.
%
% 5 types of moves: SwapHomes, SwapRounds, ...
%   IN
%       Si - input schedule
%       choice - integer between 1 and 5
%   OUT
%       So - the changed schedule

if nargin < 2, choice = randi(5); end
[m n] = size(Si); %m is nb of teams; n nb of rounds
        
%generate (unique) integers for the choice 
%and complete the change
switch choice
    case 1
        out = nRandomInt(2,m); 
        So = SwapHomes(Si,out(1),out(2));
    case 2
        out = nRandomInt(2,n);
        So = SwapRounds(Si,out(1),out(2));
    case 3
        out = nRandomInt(2,m);
        So = SwapTeams(Si,out(1),out(2));
    case 4
        t = randi(m);
        out = nRandomInt(2,n);
        So = PartialSwapRounds(Si,t,out(1),out(2)); %still a bug?
    case 5
        r = randi(n);
        out = nRandomInt(2,m);
        So = PartialSwapTeams(Si,out(1),out(2),r);
        %So=Si;
    otherwise, error('incorrect choice');
end

%  fprintf('****old schedule\n');
%  disp(Si);
%  fprintf('new schedule with move %d***\n', choice);
%  disp(So);

end



