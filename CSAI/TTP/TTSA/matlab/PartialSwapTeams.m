function [ So ] = PartialSwapTeams( Si, Ta, Tb, r )
%PARTIALSWAPTEAMS Swap the games of team Ta and Tb at round r ensuring
%   the schedule stays consistent
% @pre: Schedule Si is in a consistent state, which means that it should
%       represent a double round robin tournament schedule

So = Si;
s = Si(Ta,r);
if( abs(s) ~= Tb)
    b = 0;
    col = r;
    while(s ~= b)
        % assign to a and b the values of team Ta and Tb at round col
        a = Si(Ta,col);
        b = Si(Tb,col);
        % switch values of teams Ta and Tb at round col
        So(Ta,col) = b;
        So(Tb,col) = a;
        % switch values of teams |a| and |b| at round col
        So(abs(a),col) = Si(abs(b),col);
        So(abs(b),col) = Si(abs(a),col);
        if(a*b < 0)
            So(abs(a),col) = -So(abs(a),col);
            So(abs(b),col) = -So(abs(b),col);
        end
        % find round in which Ta has value b (the last calculation is
        % unnecessary, since it will again be equal to r)
        col = Si(Ta,:) == b;
    end
    
else
    % this method does nothing; 
    % alternatively, the most logical move can be SwapHomes
    
end

end
