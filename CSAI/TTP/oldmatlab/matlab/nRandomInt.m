function [ out ] = nRandomInt( N, M )
%NRANDOMINT Generate N unique random integers from 1:M

out = randperm(M);
out = out(1:N);

end

