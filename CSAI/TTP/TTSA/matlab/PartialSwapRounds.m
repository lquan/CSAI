function [ So ] = PartialSwapRounds( Si, Ti, ra, rb )
So = Si;
% idx = abs(Si(:, rk)) ~= abs(Si(:,rl)); %the logical indices to swap
% So(Ti, [rk rl]) = Si(Ti, [rl rk]); %the effective swap
% So(idx, [rk rl]) = Si(idx, [rl rk]); %the other

k = -Ti;
while(k~=Ti) % it forms a kinda reachability graph: Ti plays at ra agains x
    k = abs(Si(abs(k),ra)); %, while x plays against y at rb and y ...
    So(k,ra) = Si(k,rb); % till some team z plays against Ti at ra
    So(k,rb) = Si(k,ra); % all these should be swapped
    k = abs(Si(abs(k),rb));
    So(k,ra) = Si(k,rb);
    So(k,rb) = Si(k,ra);
end

end
