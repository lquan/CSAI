%CALCCOST calculates the cost as defined on p 9 (objective function C)
%defined as follows: C = cost(S)                              if S is feasible
%			 sqrt(cost(S)^2+(omega*f(nbv(S)))^2)  otherwise
%		where f is a sublinear function such that f(1) = 1
%               f is defined in myFun and is currently 1 + sqrt(v)*ln(v/2)
% IN
%    S - the schedule
%    D - distance matrix
%    omega - weight 
%
% OUT
%    C - the cost
%    nbv - the nb of violations
function [ C, nbv ] = calcCost( S, D, omega)

costS = calcDistance(S,D); %first calculate the distance
nbv = calcNbViolations(S);

isFeasible = ( nbv == 0 );
if isFeasible
    C = costS;
else
    f = @myFun;
    C = sqrt( costS^2 + ( omega * f(nbv) )^2 ); 
end

end

