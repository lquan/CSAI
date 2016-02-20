% Modify expression to add input arguments.
% Example:
%   a = [1 2 3; 4 5 6]; 
%   foo(a);
S = randomSchedule(4)
while(checkSchedule(S))
    m = ceil(5*rand)
    S = changeSched(S,m)
end