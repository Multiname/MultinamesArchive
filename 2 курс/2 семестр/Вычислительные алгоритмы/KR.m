clc;
clear;

inFile   = fopen('Data.txt','r');

while ~feof(inFile) 
    if strfind(fgetl(inFile), "Задача 5.3.1"), break, end
end

while ~feof(inFile)
    line = fgetl(inFile);
    if strfind(line, "Задача 5.3.2"), break, end

    dataArray = fscanf(inFile,'%f %f',[2 Inf])';
end
fclose(inFile);

x = dataArray(:, 1);
y = dataArray(:, 2);

hold on;
plot(x, y, 'o');

A = zeros(11, 2);
B = zeros(11, 1);
for i = 1 : 11
   A(i, 1) = 1;
   A(i, 2) = x(i)^2;
   B(i) = log(y(i));
end

X = (A' * A)^(-1) * A' * B;

a = exp(X(1));
b = X(2);

xx = linspace(-2.5, 2.5, 51);
syms x;
yy = a * exp( b * xx.^2 );

plot(xx, yy, '-');