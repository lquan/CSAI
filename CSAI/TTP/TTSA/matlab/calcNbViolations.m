function [n, n1, n2 ] = calcNbViolations( S )
%CALCNBVIOLATIONS calculates the nb of atmost and norepeat violations of S
%   IN
%      S  - the schedule
%   OUT
%      n  - total nb of violations
%      n1 - nb of atmost violations
%      n2 - nb of norepeat violations

n1 = calcNbAtMostViolations(S);
n2 = calcNbNoRepeatViolations(S);

n = n1 + n2;

end


%calculates atmost violations
function nb = calcNbAtMostViolations( S )
% Atmost constraints
[m n] = size(S);

SS = double(S>=0).'; % S>=0
SS(end+1,:) = 2; % barrier to avoid overlapping detection
SS = reshape(SS, 1, []);
% pattern to search
fouraway = [0 0 0 0];
fourhome = [1 1 1 1];
i4away = strfind(SS, fouraway);
i4home = strfind(SS, fourhome);
i4 = union(i4away,i4home);

%the results
[game team] = ind2sub([n+1 m], i4);

nb = numel(team);
% Display
% if ~isempty(team)
%     fprintf('Atmost violation\n')
%     for k=1:nb
%        fprintf('\tteam %d, games %d-%d\n', team(k), game(k), game(k)+3);
%     end
% end
end

%calculates norepeat violations
function nb = calcNbNoRepeatViolations( S )
% No repeat constraint
SS = S(:,1:end-1) + S(:,2:end);
% detect two succesive opposite numbers
[team game] = find(SS==0);

nb = numel(team);
% Display
% if ~isempty(team)
%     fprintf('Repeat game violation\n')
%     for k=1:nb
%        fprintf('\tteam %d, games %d/%d\n', team(k), game(k), game(k)+1);
%     end
% end
end

