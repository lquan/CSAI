% Declare nature's choices.
choice(researchTopic(T),C) :- C = researchTopicS(T) ; C = researchTopicF(T).
choice(solveTask(T),C) :- C = solveTaskS(T) ; C = solveTaskF(T).
choice(sendTask(T),C) :- C = sendTask(T).

% Action precondition and successor state axioms.
poss(researchTopicS(T),S) :- not topicResearched(T,S).
poss(researchTopicF(T),S) :- not topicResearched(T,S).
poss(solveTaskS(T),S) :- not taskSolved(T,S).
poss(solveTaskF(T),S) :- not taskSolved(T,S).
poss(sendTask(T),S) :- taskGiven(T,S).
%poss(sendTaskF(T),S) :- taskGiven(T,S).

topicResearched(T,do(A,S)) :- not A = researchTopicS(T), topicResearched(T,S); A = researchTopicS(T).
taskSolved(T,do(A,S)) :- not A = solveTaskS(T,S), taskSolved(T,S); A = solveTaskS(T,S).
taskGiven(T,do(A,S)) :- taskGiven(T,S), not A = sendTask(T).



% Probabilities.
prob0(researchTopicS(T),researchTopic(T),S,0.8).
prob0(researchTopicF(T),researchTopic(T),S,0.2).
prob0(solveTaskS(T),solveTask(T),S,0.75).
prob0(solveTaskF(T),solveTask(T),S,0.25).
prob(sendTask(T),sendTask(T),S,1).
%prob0(sendSolutionS(T),sendSolution(T),S,0.8).
%prob0(sendSolutionF(T),sendSolution(T),S,0.2).

% Initial database.
taskGiven(T,s0) :- T = csai ; T = cvision ; T = aplai.
topicResearched(T, s0) :- T = aplai.


restoreSitArg(topicResearched(T),S,topicResearched(T,S)).
restoreSitArg(taskSolved(T),S,taskSolved(T,S)).
restoreSitArg(taskGiven(T),S,taskGiven(T,S)).


