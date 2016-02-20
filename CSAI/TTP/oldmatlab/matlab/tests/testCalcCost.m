%test script for the cost calculation

% Generate a dummy matrix of distances between cities
n = 6;
D = rand(6,6);
D = 0.5*(D+D.');
D(1:m+1:end) = 0;


% Correct schedule
S1 = [6 -2 4 3 -5 -4 -3 5 2 -6;
    5 1 -3 -6 4 3 6 -4 -1 -5;
    -4 5 2 -1 6 -2 1 -6 -5 4;
    3 6 -1 -5 -2 1 5 2 -6 -3;
    -2 -3 6 4 1 -6 -4 -1 3 2;
    -1 -4 -5 2 -3 5 -2 3 4 1 ];
% Wrong schedule
S2 = [6 -2 4 3 -5 -4 -3 5 2 -6;
    5 1 -3 -6 4 3 6 -4 -1 -5;
    -4 5 2 -2 6 -1 1 -6 -5 4;
    3 6 -1 -5 -2 1 5 2 -6 -3;
    -2 -3 6 4 1 6 -4 -1 3 2;
    -1 -4 -5 -6 -3 5 -2 3 4 1 ];

%distance calculation and verification
[total1, distance1] = calcDistance(S1, D)
[total2, distance2] = calcDistance(S2, D)

distanceTeam1 = distance1(1)
distanceTeam1Alt = D(2,1) + D(2,1) + D(1,5) + D(5,4) + D(4,3) + D(3,1) + D(1,6) + D(6,1)

%violation detection
[nbAtMostV1 nbNoRepeatV1] = calcNbViolations(S1)
[nbAtMostV2 nbNoRepeatV2] = calcNbViolations(S2)


% the final cost calculation
omega = 1;
[ C1 ] = calcCost( S1, D, omega)
[ C2 ] = calcCost( S2, D, omega)

















% S = [6 -2 4 3 -5 -4 -3 5 2 -6;
%     5 1 -3 -6 4 3 6 -4 -1 -5;
%     -4 5 2 -2 6 -1 1 -6 -5 4;
%     3 6 -1 -5 -2 1 5 2 -6 -3;
%     -2 -3 6 4 1 6 -4 -1 3 2;
%     -1 -4 -5 2 -3 5 -2 3 4 1 ];

% % Generate matrix of distances between cities
% m = 6;
% d = rand(6,6);
% d = 0.5*(d+d.');
% d(1:m+1:end) = 0;
% % 
% % Traveling cost
% [m n] = size(S);
% t = (1:m)'; % team
% T = repmat(t,1,n+2); % change here
% SS = [t S t]; % change here, start from home and flight home end of tournament
% ishome = SS>=0;
% SS(ishome) = T(ishome);
% SS = abs(SS);
% departure = SS(:,1:end-1);
% arrival = SS(:,2:end);
% flightdistance = d(sub2ind(size(d),departure,arrival));
% totalmileage = sum(flightdistance,2)
% 
% % Atmost constraint
% SS = double(S>=0).'; % S>=0
% SS(end+1,:) = 2; % barrier to avoid overlapping detection
% SS = reshape(SS, 1, []);
% % we don't want any sequense of these
% fouraway = [0 0 0 0];
% fourhome = [1 1 1 1];
% i4away = strfind(SS, fouraway);
% i4home = strfind(SS, fourhome);
% i4 = union(i4away,i4home);
% [game team] = ind2sub([n+1 m], i4);
% % Display
% if ~isempty(team)
%     fprintf('Atmost violation\n')
%     for k=1:numel(team)
%        fprintf('\tteam %d, games %d-%d\n', team(k), game(k), game(k)+3);
%     end
% end
% 
% % No repeat constraint
% SS = S(:,1:end-1)+ S(:,2:end);
% % detect two succesive opposite numbers
% [team game] = find(SS==0);
% % Display
% if ~isempty(team)
%     fprintf('Repeat game violation\n')
%     for k=1:numel(team)
%        fprintf('\tteam %d, games %d/%d\n', team(k), game(k), game(k)+1);
%     end
% end
