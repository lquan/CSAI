%RANDOMSCHEDULE generates a random double round robin tournament for n teams (n must be even)
%
% IN
%    n - nb of teams (must be even)
% OUT
%    schedule - a random double round robin schedule
function [ schedule ] = randomSchedule( n )

weeks = 2 * n - 2;
sIn = zeros(weeks, n);
Q = 1:numel(sIn);
[schedule, bool] = generateSchedule(Q,sIn,n);
if (~bool), disp('error on creation of initial schedule!'); end
end


function [sOut,bool] = generateSchedule(Q, sIn,n)
sOut = sIn;
bool = 1;

if isempty(Q), sOut = sOut'; return; end
[weeks teams] = ind2sub(size(sOut),Q);
w = weeks(1);
t = teams(1);
%create the choices set
choices = [(1:t-1) (t+1:n) -(1:t-1) -(t+1:n)];
%shuffle the choices
choices = choices(randperm(numel(choices)));
for o = choices
    isFreeOpponent = ~ any(abs(sOut(w,:)) == abs(o)) && ~any(sOut(:,t) == o);
    %~ismember( [weeks; teams]', [w o], 'rows');
    if isFreeOpponent
        %assign
        sOut(w, [abs(o); t]) = [-sign(o) * t; o];

        Qmin = sub2ind(size(sOut), [w w], [t abs(o)]);
        Qnew = setdiff(Q,Qmin);
        %recursive call
        [sOut2,bool2] = generateSchedule(Qnew,sOut,n);
        if bool2
            bool = 1;
            sOut = sOut2; 
            return;
        end
    end
    
end
sOut = sIn;
bool = 0;
%disp('backtrack')
return;

    
end



