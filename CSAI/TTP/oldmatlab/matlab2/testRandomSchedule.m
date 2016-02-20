clc;clear
%teams =12; t = (1:teams)'; weeks = 2 * teams -2;

% nbTeams =10;
% tic
% schedule = randomSchedule(nbTeams)
% toc
fid = fopen('randomschedules.txt', 'a');
fprintf(fid,'\n%%generation of random scheduels\n');

max = 14;
% figure
% hold all
tteams = 14:2:max;
nb = 10;
% xlabel('experiment')
% ylabel('tijd (s)')
% title('tijd om een random schedule te genereren')

% lstrings= cell(1,numel(tteams));
% for temp = 1:numel(tteams)
% lstrings{temp} = strcat('n=', num2str(tteams(temp)));
% end


for t = tteams
    for i = 1:nb
    tic; 
    fprintf('searching for n =%d, experiment %d\n', t, i);
    [ schedule ] = randomSchedule( t);
    fprintf(fid,'%d\t%f\n',i, toc);
    end
    fprintf(fid,'\n\n');
    
end
fclose(fid);

