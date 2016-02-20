clc;clear
%teams =12; t = (1:teams)'; weeks = 2 * teams -2;
figure
hold all
tteams = 4:2:16;
nb = 10;
xlabel('experiment')
ylabel('tijd (s)')
title('tijd om een random schedule te genereren')

for temp = 1:numel(tteams)
lstrings{temp} = strcat('n=', num2str(tteams(temp)));
end


for teams = tteams
times = zeros(1,nb);
for i = 1:nb
tic; 
[ schedule ] = randomSchedule( teams )
times(i) = toc;
end

plot((1:nb),times)

end

legend(lstrings)



%D = load('data8.txt');
%omega = 1;
%[ C ,nbv] = calcCost( schedule, D, omega)
% 
% %some sanity checks
% dimCheck = all([teams weeks] == size(schedule));
% allDifferent = all(sum(abs(schedule)) == sum(t));
% twoPosCheck = all(sum(schedule > 0) == teams/2);
% sortCheck = all(all(sort(abs(schedule)) == repmat(t,1,weeks)));
% sort2check = all(~any(sort(abs(schedule),2) == repmat(t,1,weeks)));
% 
% if  dimCheck && allDifferent && twoPosCheck && sortCheck && sort2check
%     disp('generation of random schedule succeeded');
% else
%     disp('generation of random schedule FAILED');
% end



