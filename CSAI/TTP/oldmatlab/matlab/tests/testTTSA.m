clear;clc;%dbstop if error
D = load('data6.txt');
T = 400;     betaT = 0.98;
    omega = 4000;     delta = 1.04;     theta = 1.04; 
    %maxC = 5000;    maxP = 7100;    maxR = 10;
    maxC = 100;    maxP = 50;    maxR = 0;

params = struct('T',T,'betaT',betaT, ...
    'omega',omega,'delta',delta, 'theta',theta, ...
    'maxC', maxC, 'maxP', maxP, 'maxR', maxR);
tic; [ Sout, cost ] = ttsa(D, params)
toc