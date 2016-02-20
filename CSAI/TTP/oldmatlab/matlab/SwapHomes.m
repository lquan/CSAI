function [ So ] = SwapHomes( Si,Ta,Tb )
%SWAPHOMES swaps the home/away roles of teams a and b in Si

So = Si;
%select the trip of Ta
%tripA = Si(Ta,:); rId = tripA == Tb | tripA == -Tb; 

%the indices of the rounds to change
rId =  abs(Si(Ta,:)) == Tb;
So([Ta Tb],rId) = -Si([Ta Tb],rId);

%Ca = find(Si(Ta,:) == Tb);
%Cb = find(Si(Ta,:) == -Tb);
%So(Ta,Ca) = -Si(Ta,Ca);
%So(Ta,Cb) = -Si(Ta,Cb);
%So(Tb,Ca) = -Si(Tb,Ca);
%So(Tb,Cb) = -Si(Tb,Cb);

end

