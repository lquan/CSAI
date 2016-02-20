function [So] = SwapTeams(Si, Ta, Tb)

n = size(Si,2); %nb of rounds
So = Si;
roundsToChange = abs(Si(Ta,:)) ~= Tb;
%swap teams
So([Ta;Tb],roundsToChange) = Si([Tb;Ta],roundsToChange);
%correct opponents
for rr =1:n
    if (roundsToChange(rr))
    oppA = Si(Ta, rr); oppB = Si(Tb, rr);  %get the opponent of A and B
        if (oppA * oppB > 0)
            %if A and B had the same signs of opponents 
            %(i.e., home-home or away -away), no sign switch needed
            So(abs([oppA; oppB]), rr) = Si(abs([oppB; oppA]), rr); 
        else
            So(abs([oppA; oppB]), rr) = -Si(abs([oppB; oppA]), rr);
        end
    end
end
end

% So(Ta,:) = Si(Tb,:);
% So(Tb,:) = Si(Ta,:);
% [ia,ja] = find(abs(So) == Ta);
% [ib,jb] = find(abs(So) == Tb);
% 
% for k = 1:length(ia)    % swap all values concerning Ta en Tb !! signs!!
%     va = So(ia(k),ja(k));
%     vb = So(ib(k),jb(k));
%     So(ia(k),ja(k)) = vb*sign(vb)*sign(va); % swap sign if they differ
%     So(ib(k),jb(k)) = va*sign(vb)*sign(va);
% end
% 
% i = find(abs(So(Ta,:)) == Tb); %signs of matches of Ta against Tb have
% % So(Ta,i(1)) = -So(Ta,i(1));    %unnecessairily been changed.
% % So(Ta,i(2)) = -So(Ta,i(2));
% % So(Tb,i(1)) = -So(Tb,i(1));
% % So(Tb,i(2)) = -So(Tb,i(2));
% So([Ta Tb],i) = -So([Ta Tb], i); %using the shorter version :p


