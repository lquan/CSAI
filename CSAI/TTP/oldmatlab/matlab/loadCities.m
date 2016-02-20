fid = fopen('NLcities.txt');
cities = textscan(fid, '%s', 'CommentStyle', '%')
fclose(fid);

