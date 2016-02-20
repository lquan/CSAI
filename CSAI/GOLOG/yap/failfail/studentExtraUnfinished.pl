% Declare nature's choices.
choice(researchTopic(T),C) :- C = researchTopicS(T) ; C = researchTopicF(T).
choice(solveTask(T),C) :- C = solveTaskS(T) ; C = solveTaskF(T).
choice(sendTask(T),C) :- C = sendTaskS(T); C = sendTaskF(T).
% Extra
choice(gradeTask(T),C) :- C = passTask(T); C = failTask(T).


% Action precondition and successor state axioms.
poss(researchTopicS(T),S) :- not topicResearched(T,S).
poss(researchTopicF(T),S) :- not topicResearched(T,S).
poss(solveTaskS(T),S) :- not taskSolved(T,S), taskGiven(T,S).
poss(solveTaskF(T),S) :- not taskSolved(T,S), taskGiven(T,S).
poss(sendTaskS(T),S) :- taskSolved(T,S), taskGiven(T,S).
poss(sendTaskF(T),S) :- taskSolved(T,S), taskGiven(T,S).
% Extra
poss(passTask(T),S) :- not taskSucceeded(T,S)

topicResearched(T,do(A,S)) :- not A = researchTopicS(T), topicResearched(T,S); A = researchTopicS(T).
taskSolved(T,do(A,S)) :- not A = solveTaskS(T), taskSolved(T,S); A = solveTaskS(T).
taskGiven(T,do(A,S)) :- taskGiven(T,S), not A = sendTaskS(T).
% Extra
taskSucceeded(T,do(A,S)) :- taskSucceeded(T,S), not A = passTask(T); A = passTask(T).


% Probabilities.
prob0(researchTopicS(T),researchTopic(T),S,0.8).
prob0(researchTopicF(T),researchTopic(T),S,0.2).
prob0(solveTaskS(T),solveTask(T),S,0.75).
prob0(solveTaskF(T),solveTask(T),S,0.25).
prob0(sendTaskS(T),sendTask(T),S,0.9).
prob0(sendTaskF(T),sendTask(T),S,0.1).
%prob0(sendSolutionS(T),sendSolution(T),S,0.8).
%prob0(sendSolutionF(T),sendSolution(T),S,0.2).

% Initial database.
taskGiven(T,s0) :- T = csai.% ; T = cvision ; T = aplai.
topicResearched(T, s0) :- T = aplai.


restoreSitArg(topicResearched(T),S,topicResearched(T,S)).
restoreSitArg(taskSolved(T),S,taskSolved(T,S)).
restoreSitArg(taskGiven(T),S,taskGiven(T,S)).


