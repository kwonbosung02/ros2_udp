file = fopen('output.txt','r');
format = '%f';

Matrix = fscanf(file, format);
Y = Matrix';
[x_, x] = size(Y);
X = 1 : 1 : x;
figure;

plot(X,Y);
title('UDP communication 20Hz delay');
ytickformat('%fsec');
hl = legend('mean : '+string(mean(Y)));
