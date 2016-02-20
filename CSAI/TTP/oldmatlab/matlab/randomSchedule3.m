%RANDOMSCHEDULE generates a random double round robin tournament for n teams (n must be even)
%
% IN
%    n - nb of teams (must be even)
% OUT
%    schedule - a random double round robin schedule
function [ schedule ] = randomSchedule3( n )
weeks = 2 * n - 2;
sIn = zeros(n, weeks);
%create the set Q by the cartesian product of teams and weeks
Q = setProd( (1:n), (1:weeks) );
[bool, schedule] = generateSchedule( Q, sIn);
end


function [bool, sOut] = generateSchedule( Q , sIn)
sOut = sIn;
if isempty(Q), bool = 1; return; end;

%select (t,w) such that ...
%Qsorted = sortrows(Q);
selected = Q(1,:);
t = selected(1); w = selected(2);

%create the choices set
nTeams = size(sIn,1);
choices = [(1:t-1) (t+1:nTeams)];
choices = [choices -choices];
%now create a permutation order
permOrder = randperm(length(choices));
%shuffle the choices
choices = choices(permOrder);  
for o = choices
    %check if the opponent was already assigned
    %to the team previous or in this week
    isFreeOpponent = ~any(sIn(t,1:w) == o) && ~any(abs(sIn(:,w)) == abs(o));
    
    if isFreeOpponent
        sOut(t,w) = o;
	%correct the corresponding opponent of the opponent to this team
        if o > 0
            sOut(o,w) = -t;
        else
            sOut(-o,w) = t;
        end
        
        %the rows to remove
        %removeRows = ( ismember(Q, [ t w], 'rows') | ...
        %                ismember(Q, [ abs(o) w], 'rows') );
        Qnew = setdiff(Q,[ t w ; abs(o) w], 'rows');
        %Qnew = Q;
        %Qnew(removeRows,:) = []; %remove them
        
        %recursive call
        [bool2, sOut2] = generateSchedule( Qnew, sOut );
        
        if bool2
            sOut = sOut2;
            bool = 1;
            return;
        end
    end
end

%return false
sOut = sIn;
bool = 0;
return;

end



