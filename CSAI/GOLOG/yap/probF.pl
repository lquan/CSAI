
    %   Probabilities for stGolog Programs

probF(F,Prog,Prob) :- findall(P,
                              S^(stDo(Prog : nil,P,s0,S), once(holds(F,S))),
                              PS),
                      addNumbers(PS,Prob).
addNumbers([],0.0).
addNumbers([N | Ns],Sum) :- addNumbers(Ns,Sum1), Sum is Sum1 + N.

