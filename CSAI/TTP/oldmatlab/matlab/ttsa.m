function [ Sout, bestFeasible ] = ttsa(D, params)
%TTSA computes a schedule using simulated annealing for the TTP
%
% IN
%   D - the distance matrix
%   params - parameter structure
% OUT
%   S - the schedule

if (nargin < 2)
    % some parameters
    T = 500;     betaT = 0.9999;
    omega = 5000;     delta = 1.04;     theta = 1.04; 
    maxC = 100;    maxP = 100;    maxR = 0;
else
    T = params.T; betaT = params.betaT;
    omega = params.omega;    delta =  params.delta;    theta = params.theta;
    maxC = params.maxC; maxP = params.maxP; maxR = params.maxR;
end

[m] = size(D,1); % nb of teams;

%initialization
%find random schedule S
S = randomSchedule(m); Sout = S;
bestFeasible = Inf; nbf = Inf;
bestInfeasible = Inf; nbi = Inf;
reheat = 0; %counter = 0;



%some aliasses
cost = @calcCost;

while reheat <= maxR
    phase = 0;
    while phase <= maxP
        counter = 0;
        while counter <= maxC
            % select a random move m from neighbourhood S
            move = randi(5); 
	    % let newS (=S' in paper) be the schedule obtained with m
            newS = changeSched(S,move); 
            % calculate the cost change
            oldCost = cost(S,D,omega);
	        [newCost, nbvNewS] = cost(newS,D,omega);
           % fprintf('reheat %d, phase %d, counter %d\n', ...
           %             reheat, phase, counter); 
           % fprintf('\t cost: %f\n', newCost);
            deltaC = newCost - oldCost;
            if  deltaC < 0 || ...
                    ( nbvNewS == 0 && newCost < bestFeasible  ) || ...
                    ( nbvNewS > 0 && newCost < bestInfeasible )
                accept = 1;
            else
                prob = exp(-deltaC/T);
                %fprintf('the probability %f\n', prob)
                if prob > rand 
		    %accept with probability exp(delta/T)
                    accept = 1;
                else
                    accept = 0;
                    %fprintf('rejection\n');
                end
            end
            %
	    %line 21
            
            if accept
                %fprintf('accept\n');
                S = newS;
   
                if nbvNewS == 0 %nbv(S) == 0
                    nbf = min(newCost, bestFeasible);
                    
                else
                    nbi = min(newCost, bestInfeasible);
                end
                if nbf < bestFeasible || nbi < bestInfeasible
                    reheat = 0; counter = 0; phase = 0;
                    bestTemperature = T;
                    bestFeasible = nbf;
                    bestInfeasible = nbi;
                    if nbvNewS == 0 %nbv(S) == 0
                        fprintf('\t\tnew best solution found with cost %f\n', newCost)
                        disp(newS)
                        Sout = newS;
                        
                        omega = omega / theta;
                    else
                        omega = omega * delta;
                    end
                else
                    counter = counter + 1;
                end
            end
        end
        phase = phase + 1;
        T = T * betaT; %update the temperature
    end
    reheat = reheat + 1;
    T = 2 * bestTemperature;
end




end

