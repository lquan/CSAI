                 %  Delivery Robot in Prolog
% Declare nature's choices.
choice(giveCoffee(P),C) :- C = giveCoffeeS(P) ; C = giveCoffeeF(P).
choice(go(L),C) :- C = endUpAt(L) ; C = getLost(L).
choice(puMail,C) :- C = puMail.
choice(giveMail(P),C) :- C = giveMail(P).

% Action precondition and successor state axioms.

poss(puMail,S) :- loc(mr,S), mailPresent(P,S).
poss(giveMail(P),S) :- carryingMail(P,S), loc(office(P),S).
poss(giveCoffeeS(P),S) :- coffeeRequested(P,S), loc(office(P),S).
poss(giveCoffeeF(P),S) :- coffeeRequested(P,S), loc(office(P),S).
poss(endUpAt(L),S) :- not L = blackHole, loc(L1,S), not L1 = blackHole,
                      not L1 = L.
poss(getLost(L),S) :- not L = blackHole, loc(L1,S), not L1 = blackHole,
                      not L1 = L.

mailPresent(P,do(A,S)) :- not A = puMail, mailPresent(P,S).
coffeeRequested(P,do(A,S)) :- coffeeRequested(P,S), not A = giveCoffeeS(P).
carryingMail(P,do(A,S)) :- A = puMail, mailPresent(P,S) ;
                           carryingMail(P,S), not A = giveMail(P).
loc(L,do(A,S)) :- A = endUpAt(L) ; A = getLost(L1), L = blackHole ;
                  loc(blackHole,S), L = blackHole ;
                  loc(L,S), not L = blackHole, not A = getLost(L1),
                  not (A = endUpAt(L1), not L = L1).

% Probabilities.

prob0(giveCoffeeS(P),giveCoffee(P),S,Pr) :- Pr = 0.95 .
prob0(giveCoffeeF(P),giveCoffee(P),S,Pr) :- Pr = 0.05 .
prob0(giveMail(P),giveMail(P),S,Pr) :- Pr = 1.0 .
prob0(puMail,puMail,S,Pr) :- Pr = 1.0 .
prob0(endUpAt(L),go(L),S,Pr) :- loc(L0,S), dist(L0,L,D),
                                Pr is 1000 / (1000 + D).
prob0(getLost(L),go(L),S,Pr) :- loc(L0,S), dist(L0,L,D),
                                Pr is D / (1000 + D).
% Initial database.

loc(mr,s0).
carryingMail(P,s0) :- P = pat ; P = sue ; P = alf.
coffeeRequested(P,s0) :- P = sue ; P = alf.

% The offices are strung out along a single line. mr is on the left.
% office(pat) is to its immediate right at a distance of 10. office(sue)
% is to the immediate right of office(pat) at a distance of 10. Etc.

distances([mr,10,office(pat),10,office(sue),10,office(ann),10,
           office(bob),10,office(sam),10,office(alf)]).

dist(X,Y,D) :- distances(A), (dist0(X,Y,A,D), ! ; dist0(Y,X,A,D)).

dist0(X,X,A,0).
dist0(X,Y,A,D) :- tail([X,DX | [Z | L]],A),
                  dist0(Z,Y,[Z | L],DR), D is DX + DR.

tail(L,L).
tail(L,[X | Xs]) :- tail(L,Xs).

restoreSitArg(coffeeRequested(P),S,coffeeRequested(P,S)).
restoreSitArg(mailPresent(P),S,mailPresent(P,S)).
restoreSitArg(loc(L),S,loc(L,S)).
restoreSitArg(carryingMail(P),S,carryingMail(P,S)).


