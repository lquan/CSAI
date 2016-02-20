:- use_module(library(problog)).

%choice(researchTopic(T),C) :- C = researchTopicS(T) ; C = researchTopicF(T).
%choice(solveTask(T),C) :- C = solveTaskS(T) ; C = solveTaskF(T).
%choice(sendTask(T),C) :- C = sendTaskS(T); C = sendTaskF(T).
%(getTaskGrade(T),C) :- C = passTask(T); C = failTask(T).

%0.85 :: researchTopicS(T);  0.15 :: researchTopicF(T) <-- true.%topic(T).
%0.75 :: solveTaskS(T,S); 0.25 :: solveTaskF(T,S) <-- true.  
%0.99 :: sendTaskS(T,S) ; 0.01 :: sendTaskF(T,S) <-- true.
0.85 :: researchTopic(T).
%0.75 :: solveTask(T).

poss(researchTopic(T),S) :-  not topicResearched(T,S).
%poss(solveTaskS(T),S) :- taskGiven(T,S), not taskSolved(T,S).
%poss(solveTaskF(T),S) :- taskGiven(T,S), not taskSolved(T,S).
%poss(sendTaskS(T),S) :- taskGiven(T,S), taskSolved(T,S). 
%poss(sendTaskF(T),S) :- taskGiven(T,S), taskSolved(T,S).

topicResearched(T,SS) :- A = researchTopic(T), do(A,S,SS) ; topicResearched(T,S), SS = s(S).
%taskSolved(T,SS) :- A = solveTask(T), do(A,S,SS) ; taskSolved(T,S), SS = s(S).
%taskGiven(T,do(A,S)) :- not A = sendTaskS(T), taskGiven(T,S).
%taskGraded(T,do(A,S)) :- not A = passTask(T), not A = failTask(T), taskGraded(T,S) ; A = passTask(T) ; A = failTask(T).

do(A,S,s(S)) :- poss(A,S),A.

% Initial database.
taskGiven(T,s0) :- T = csai ; T = cvision ; T = aplai.
topicResearched(T, s0) :- T = aplai.


