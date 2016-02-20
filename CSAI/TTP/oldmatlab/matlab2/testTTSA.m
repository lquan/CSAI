clear;clc; %dbstop if error

D = load('./data/data12.txt');  %change to 'dataN.txt' for N teams

fprintf('Starting TTSA for %d teams\n', size(D,1));

% parameters for ttsa
T = 500;     betaT = 0.99;
    omega = 4000;     delta = 1.04;     theta = 1.04; 
    maxC = 200;    maxP = 100;    maxR = 5; 
%     maxC = 5000;    maxP = 7100;    maxR = 10;  %% default


params = struct('T',T,'betaT',betaT, ...
    'omega',omega,'delta',delta, 'theta',theta, ...
    'maxC', maxC, 'maxP', maxP, 'maxR', maxR);
tic; [ Sout, cost ] = ttsa(D, params)
toc