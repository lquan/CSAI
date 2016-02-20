%RANDOMSCHEDULE generates a random double round robin tournament for n teams (n must be even)
%
% IN
%    nb - nb of teams (must be even)
% OUT
%    schedule - a random double round robin schedule
function [ schedule ] = randomSchedule( nb )
if (mod(nb,2)~=0), error('n must be even!'); end
global n;
n = nb;
weeks = 2 * n - 2;
sIn = zeros(weeks, n);
schedule = generateSchedule(sIn);
end

function [sOut,bool] = generateSchedule(sIn)
global n;
undecided = (sIn == 0);
if (all(~undecided)), bool = 1; sOut = sIn'; return; end %complete solution

[w t] = find(undecided, 1); %find the first undecided
%create the choices set, this are the other teams, home or away
choices = [(1:t-1) (t+1:n) -(1:t-1) -(t+1:n)];
%eliminate teams to which t already plays
choices = setdiff(choices, sIn(:,t));
%shuffle the choices
choices = choices(randperm(numel(choices)));
for opp = choices
    sOut = sIn;
    %check whether the opponent is free that week
    isFreeOpponent = ~any(abs(sOut(w,:)) == abs(opp));
    %~ismember(abs(opp), abs(sOut(w,:)));
    if isFreeOpponent
        %assign
        sOut(w, [t abs(opp)]) = [opp -sign(opp)*t];

        %recursive call
        [sOut2,bool2] = generateSchedule(sOut);
        if bool2
            bool = 1;
            sOut = sOut2; 
            return;
        else
            %sOut = sIn;
            %disp('backtrack to other opponent')
        end
    end
end
sOut = sIn;
bool = 0;
%fprintf('backtrack to higher level\n')
return;

    
end
