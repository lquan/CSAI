function [ So ] = SwapRounds(Si, rk, rl)
%SWAPROUNDS swaps the rounds r and k in Si
So = Si;
So(:,[rk rl]) = Si(:,[rl rk]);
end

