function [ total, distances ] = calcDistance( schedule, D )
%CALCDISTANCE Calculates the distance (total and/or per team) 
%given a schedule and the distance matrix D

%  IN
%    schedule - a valid schedule of the form teams * rounds
%    D - a square (usually symmetric) distance matrix (n = teams)
%  OUT
%    total - the complete distance travelled (the sum of each team)
%    distances - a vector containing the distance of each team

[m n] = size(schedule);
t = (1:m)'; % teams
T = repmat(t,1,n+2);
SS = [t schedule t]; % home at beginning and end

isHome = SS>=0;
SS(isHome) = T(isHome);
SS = abs(SS);

departure = SS(:,1:end-1);
arrival = SS(:,2:end);

flightdistance = D(sub2ind(size(D),departure,arrival));
distances = sum(flightdistance,2);

total = sum(distances);
end
