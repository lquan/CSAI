%test the creation of a neighbouring schedule

%see p 3 - 6 for correct results
clc; clear;
% Correct schedule
S = load('paper_schedule.txt')


% SwapHomes
SwapHomes(S,2,4)

% SwapRounds
SwapRounds(S,3,5)

% SwapTeams
SwapTeams(S,2,5)

% PartialSwapRounds
%paper uses another test matrix
S2 = [6 -2 2 3 -5 -4 -3 5 4 -6;
5 1 -1 -5 4 3 6 -4 -6 -3;
-4 5 4 -1 6 -2 1 -6 -5 2;
3 6 -3 -6 -2 1 5 2 -1 -5;
-2 -3 6 2 1 -6 -4 -1 3 4;
-1 -4 -5 4 -3 5 -2 3 2 1];

PartialSwapRounds(S2,2,2,9)

% PartialSwapTeams
%paper uses another test matrix
S2 = [6 -2 4 3 -5 -4 -3 5 2 -6;
5 1 -3 -6 4 3 6 -4 -1 -5;
-4 5 2 -1 6 -2 1 -6 -5 4;
3 6 -1 -5 -2 1 5 2 -6 -3;
-2 -3 6 4 1 -6 -4 -1 3 2;
-1 -4 -5 2 -3 5 -2 3 4 1];

PartialSwapTeams(S2,2,4,9)



