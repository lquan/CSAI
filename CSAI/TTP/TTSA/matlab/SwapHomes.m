function [ So ] = SwapHomes( Si,Ta,Tb )
%SWAPHOMES swaps the home/away roles of teams a and b in Si

So = Si;
%the indices of the rounds to change
rId =  abs(Si(Ta,:)) == Tb;
So([Ta Tb],rId) = -Si([Ta Tb],rId);


end

