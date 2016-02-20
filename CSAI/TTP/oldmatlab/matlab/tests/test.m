clear;clc;
D = load('data4.txt');

atl = 1; nym =2; phi =3; mon =4;
% ATL  NYM  PHI  MON 
%  ---  ---  ---  --- 
%   PHI  MON @ATL @NYM
%   NYM @ATL  MON @PHI
%   MON @PHI  NYM @ATL
%  @PHI @MON  ATL  NYM
%  @NYM  ATL @MON  PHI
%  @MON  PHI @NYM  ATL
Soptimal = [  phi , nym, mon, -phi, -nym, -mon ;
            mon, -atl, -phi, -mon, atl, phi ;
             -atl, mon, nym, atl, -mon, -nym;
             -nym, -phi, -atl, nym, phi, atl ];
cost = calcCost(Soptimal, D) % should be 8276

% a non optimal schedule to test
S = [Soptimal(:,2) Soptimal(:,1) Soptimal(:,3:end)]
cost2 = calcCost(S,D);

[ Sout, counter ] = ttsa( D, S )



