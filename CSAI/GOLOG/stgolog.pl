   %    An stGolog Interpreter

:- set_flag(print_depth,100).
:- nodbgcomp.
:- dynamic(proc/2).            % Compiler directives. Be sure   
:- set_flag(all_dynamic, on).  % that you load this file first! 

:- op(800, xfy, [&]).   % Conjunction 
:- op(850, xfy, [v]).   % Disjunction 
:- op(870, xfy, [=>]).  % Implication 
:- op(880,xfy, [<=>]).  % Equivalence 
:- op(950, xfy, [:]).   % Action sequence 

stDo(nil,1,S,S).
stDo(A : B,P,S1,S2) :- stochastic(A),
   (not (choice(A,C), poss(C,S1)), !,  % Program can't continue.
    S2 = S1, P = 1 ;                   % Create a leaf.
  % once is an Eclipse Prolog built-in. once(G) succeeds the first time
  % G succeeds, and never tries again under backtracking. We use it here
  % to prevent stDo from generating the same leaf situation more than
  % once, when poss has multiple solutions.
    choice(A,C), once(poss(C,S1)), prob(C,A,S1,P1),
    stDo(B,P2,do(C,S1),S2), P is P1 * P2 ).
stDo((A : B) : C,P,S1,S2) :- stDo(A : (B : C),P,S1,S2).
stDo(?(T) : A,P,S1,S2) :- holds(T,S1), !, stDo(A,P,S1,S2) ;
                          S2 = S1, P = 1. % Program can't continue.
                                          % Create a leaf.
stDo(if(T,A,B) : C,P,S1,S2) :- holds(T,S1), !, stDo(A : C,P,S1,S2) ;
                               stDo(B : C,P,S1,S2).
stDo(A : B,P,S1,S2) :- proc(A,C), stDo(C : B,P,S1,S2).
stDo(while(T,A) : B,P,S1,S2) :- holds(T,S1), !,
                                stDo(A : while(T,A) : B,P,S1,S2) ;
                                stDo(B,P,S1,S2).

prob(C,A,S,P) :- choice(A,C), poss(C,S), !, prob0(C,A,S,P) ; P = 0.0 .

stochastic(A) :- choice(A,N), !.

sub(X1,X2,T1,T2) :- var(T1), T2 = T1.
sub(X1,X2,T1,T2) :- not var(T1), T1 = X1, T2 = X2.
sub(X1,X2,T1,T2) :- not T1 = X1, T1 =..[F|L1], sub_list(X1,X2,L1,L2),
                    T2 =..[F|L2].
sub_list(X1,X2,[],[]).
sub_list(X1,X2,[T1|L1],[T2|L2]) :- sub(X1,X2,T1,T2), sub_list(X1,X2,L1,L2).

/* The holds predicate implements the revised Lloyd-Topor
   transformations on test conditions.  */

holds(P & Q,S) :- holds(P,S), holds(Q,S).
holds(P v Q,S) :- holds(P,S); holds(Q,S).
holds(P => Q,S) :- holds(-P v Q,S).
holds(P <=> Q,S) :- holds((P => Q) & (Q => P),S).
holds(-(-P),S) :- holds(P,S).
holds(-(P & Q),S) :- holds(-P v -Q,S).
holds(-(P v Q),S) :- holds(-P & -Q,S).
holds(-(P => Q),S) :- holds(-(-P v Q),S).
holds(-(P <=> Q),S) :- holds(-((P => Q) & (Q => P)),S).
holds(-all(V,P),S) :- holds(some(V,-P),S).
holds(-some(V,P),S) :- not holds(some(V,P),S).  /* Negation */
holds(-P,S) :- isAtom(P), not holds(P,S).     /* by failure */
holds(all(V,P),S) :- holds(-some(V,-P),S).
holds(some(V,P),S) :- sub(V,_,P,P1), holds(P1,S).

/* The following clause treats the holds predicate for non fluents, including
   Prolog system predicates. For this to work properly, the GOLOG programmer
   must provide, for all fluents, a clause giving the result of restoring
   situation arguments to situation-suppressed terms, for example:
         restoreSitArg(ontable(X),S,ontable(X,S)).             */

holds(A,S) :- restoreSitArg(A,S,F), F ;
              not restoreSitArg(A,S,F), isAtom(A), A.

isAtom(A) :- not (A = -W ; A = (W1 & W2) ; A = (W1 => W2) ;
    A = (W1 <=> W2) ; A = (W1 v W2) ; A = some(X,W) ; A = all(X,W)).

restoreSitArg(poss(A),S,poss(A,S)).


