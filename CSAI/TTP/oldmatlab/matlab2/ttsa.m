function [ Sout, bestFeasible ] = ttsa(D, params, S)
%TTSA computes a schedule using simulated annealing for the TTP
%
% IN
%   D - the distance matrix
%   params - parameter structure
%   S - the random schedule to start with (optional)
% OUT
%   Sout - the schedule

[m] = size(D,1); % nb of teams;
if (nargin < 3)  %find random schedule S
    S = randomSchedule(m);
end

if (nargin == 1)
        % some default parameters
        T = 500;     betaT = 0.99;
        omega = 5000;     delta = 1.04;     theta = 1.04; 
        maxC = 100;    maxP = 70;    maxR = 10;

elseif (nargin >= 2)
        T = params.T; betaT = params.betaT;
        omega = params.omega;    delta =  params.delta;    theta = params.theta;
        maxC = params.maxC; maxP = params.maxP; maxR = params.maxR;
end
    

%initialization
Sout = S;
bestFeasible = Inf; nbf = Inf;
bestInfeasible = Inf; nbi = Inf;
reheat = 0; %counter = 0;
bestTemperature = T;

%open file and write information
fid = fopen('experiments.txt', 'a');
fprintf(fid,'\n\n\n%%NL%d, T=%d, betaT=%f, w=%d, maxC=%d, maxP=%d, maxR=%d\n', ...
                m,  T,  betaT, omega, maxC, maxP, maxR);
fprintf(fid,'%%time (s)\tcost\n');

tstart = tic;
while reheat <= maxR
    phase = 0;
    while phase <= maxP
        counter = 0;
        while counter <= maxC 
            newS = changeSchedule(S); 
            % calculate the cost change
            oldCost = calcCost(S,D,omega);
	        [newCost, nbvNewS] = calcCost(newS,D,omega);
            deltaC = newCost - oldCost;
            if  deltaC < 0 || ...
                    ( nbvNewS == 0 && newCost < bestFeasible  ) || ...
                    ( nbvNewS > 0 && newCost < bestInfeasible )
                accept = 1;
            else
                prob = exp(-deltaC/T);
                if prob >= rand 
                %accept with probability exp(delta/T)
                    accept = 1;
                else
                    accept = 0;
                    %fprintf('rejection\n');
                end
            end

            if accept
                S = newS;
   
                if nbvNewS == 0 %nbv(S) == 0
                    nbf = min(newCost, bestFeasible);
                    
                else
                    nbi = min(newCost, bestInfeasible);
                end
                
                
                if nbf < bestFeasible || nbi < bestInfeasible
                    %fprintf('reheat %d, phase %d, counter %d\n', ...
                    %                reheat, phase, counter); 
                    reheat = 0; counter = 0; phase = 0;
                    bestTemperature = T;
                    bestFeasible = nbf;
                    bestInfeasible = nbi;
                    if nbvNewS == 0 
                        %new best feasible
                        elapsed = toc(tstart);
                        fprintf('New best cost found: %d\n', newCost);
                        fprintf('\tElapsed time is %f\n', elapsed);
                        fprintf('\tCurrent T: %f\n', T);
                        fprintf('\tCurrent w: %f\n', omega);
                        fprintf(fid, '%d\t%d\n', elapsed, newCost);
                        %fprintf('\t\tnew best solution found with cost %f\n', newCost)
                        disp(newS)
                        Sout = newS;
                        omega = omega / theta;
                    else
                        %new best infeasible
                        omega = omega * delta;
                    end
                else
                    counter = counter + 1;
                end
            end
            %counter = counter + 1;
        end
        phase = phase + 1;
        T = T * betaT; %update the temperature
    end
    reheat = reheat + 1;
    T = 2 * bestTemperature;
end
toc(tstart)
fclose(fid);
end
