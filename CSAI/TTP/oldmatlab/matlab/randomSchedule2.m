%RANDOMSCHEDULE generates a random double round robin tournament for n teams (n must be even)
%
% IN
%    n - nb of teams (must be even)
% OUT
%    schedule - a random double round robin schedule
function [ schedule ] = randomSchedule2( n )
weeks = 2 * n - 2;
sIn = zeros(n, weeks);


[schedule, bool] = generateSchedule(1,sIn,n);
if (~bool), disp('error on creation of initial schedule!'); end
end


function [sOut,bool] = generateSchedule(t,sIn,n)

sOut = sIn;
bool =1;
decidedInd = sOut ~= 0;


if (all(decidedInd)), return; end;
w = find(sOut(t,:)==0,1); %first unfilled round for team t

if (isempty(w)) %recursive call
        [sOut2,bool2] = generateSchedule(t+1,sOut,n);
        if bool2
            sOut = sOut2;
        else   
            bool = 0;
        end
        return;
end
% 
% if (all(decidedInd(t,:))) %t is completely assigned, next team
%     if (t+1 < 2*n-2)
%         [sOut2,bool2] = generateSchedule(t+1,sOut,n);
%         if bool2
%             sOut = sOut2;
%         else
%             sOut = sIn;
%             bool = 0;
%             %disp('backtrack')
%         end
%     end
%     return;
% end



%create the choices set
choices = [(1:t-1) (t+1:n) -(1:t-1) -(t+1:n)];
%eliminate the impossibilities
%toEliminate = union(sIn(t,:), sIn(:,w));
%choices = setdiff(choices,toEliminate);
%shuffle the choices
choices = choices(randperm(length(choices)));
for o = choices
    isFreeOpponent = ~any(abs(sOut(:,w)) == abs(o));% && ~any(sOut(t,:) == o)  ;
    if isFreeOpponent
        %assign
        sOut([t; abs(o)],w) = [o; -sign(o) * t];

        %recursive call
        [sOut2,bool2] = generateSchedule(t,sOut,n);
        if bool2
            bool = bool2;
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

