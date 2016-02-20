% Declare nature's choices.
choice(researchTopic(T),C) :- C = researchTopicS(T) ; C = researchTopicF(T).
choice(solveTopic(T),C) :- C = solveTopicS(T) ; C = solveTopicF(T).
%choice(sendSolution(T),C) :- C = sendSolutionS(T) ; C = sendSolutionF(T).

% Action precondition and successor state axioms.
poss(researchTopicS(T),S) :- taskGiven(T,S), not researchDone(T,S).
poss(researchTopicF(T),S) :- taskGiven(T,S), not researchDone(T,S).
poss(solveTopicS(T),S) :- taskGiven(T,S), researchDone(T,S).
poss(solveTopicF(T),S) :- taskGiven(T,S), researchDone(T,S). 
%poss(sendSolutionS(T),S) :- taskSolved(T,S), researchDone(T,S), taskGiven(T,S).
%poss(sendSolutionF(T),S) :- taskSolved(T,S), researchDone(T,S), taskGiven(T,S).

taskGiven(T,do(A,S)) :- taskGiven(T,S), not A = sendSolutionS(T).
researchDone(T,do(A,S)) :- researchDone(T,S); A = researchTopicS(T). 
%taskSolved(T,do(A,S)) :- taskSolved(T,S) ; A = solveTopicS(T).
%taskDelivered(T,do(A,S)) :- taskDelivered(T,S) ; A = sendSolutionS(T), not taskDelivered(T,S) .

% Probabilities.
prob0(researchTopicS(T),researchTopic(T),S,0.8).
prob0(researchTopicF(T),researchTopic(T),S,0.2).
prob0(solveTopicS(T),solveTopic(T),S,0.8).
prob0(solveTopicF(T),solveTopic(T),S,0.2).
%prob0(sendSolutionS(T),sendSolution(T),S,0.8).
%prob0(sendSolutionF(T),sendSolution(T),S,0.2).

% Initial database.
taskGiven(T,s0) :- T = csai ; T = cvision ; T = aplai.
%loc(mr,s0).
%carryingMail(P,s0) :- P = pat ; P = sue ; P = alf.
%coffeeRequested(P,s0) :- P = sue ; P = alf.


restoreSitArg(taskGiven(T),S,taskGiven(T,S)).
restoreSitArg(researchDone(T),S,researchDone(T,S)).
%restoreSitArg(taskSolved(T),S,taskSolved(T,S)).
%restoreSitArg(taskDelivered(T),S,taskDelivered(T,S)).

