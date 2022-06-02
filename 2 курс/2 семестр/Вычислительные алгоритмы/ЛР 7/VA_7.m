clc;
clear;

syms t;
syms y;
f(t, y) = -t*y + (1 + t)*exp(-t)*y^2;

t0 = 0;
T = 1;
y0 = 1;
h = 0.1;

X1 = linspace(t0, T, (T - t0) / h + 1);
Y1 = y0;
for i = 1 : (T - t0) / h
    xi = X1(i + 1);
    yi = Y1(i);
    
    k1 = f(xi, yi);
    k2 = f(xi + h/2,yi + h * k1 / 2);
    k3 = f(xi + h/2, yi + h * k2 / 2);
    k4 = f(xi + h, yi + h*k3);
    
    Y1(end + 1) = yi + h/6 * (k1 + 2*k2 + 2*k3 + k4);
end

h = h / 2;
X2 = linspace(t0, T, (T - t0) / h + 1);
Y2 = y0;
for i = 1 : (T - t0) / h
    xi = X2(i + 1);
    yi = Y2(i);
    
    k1 = f(xi, yi);
    k2 = f(xi + h/2,yi + h * k1 / 2);
    k3 = f(xi + h/2, yi + h * k2 / 2);
    k4 = f(xi + h, yi + h*k3);
    
    Y2(end + 1) = yi + h/6 * (k1 + 2*k2 + 2*k3 + k4);
end

h = h * 2;
E1 = [];
p = 4;
for i = 1 : (T - t0) / h + 1
    E1(end + 1) = (Y2(2*i - 1) - Y1(i)) / (2^p - 1);
end

Y3 = [];
for i = 1 : (T - t0) / h + 1
    Y3(end + 1) = Y2(2*i - 1) + E1(i);
end


Y4 = y0;
for i = 1 : (T - t0) / h
    xi = X1(i + 1);
    yi = Y4(i);
    
    k1 = h*f(xi, yi);
    k2 = h*f(xi + h/2, yi + k1 / 2);
    k3 = h*f(xi + h, yi - k1 + 2*k2);
    
    Y4(end + 1) = yi + 1/6 * (k1 + 4*k2 + k3);
end

h = h / 2;
Y5 = y0;
for i = 1 : (T - t0) / h
    xi = X2(i + 1);
    yi = Y5(i);
    
    k1 = h*f(xi, yi);
    k2 = h*f(xi + h/2, yi + k1 / 2);
    k3 = h*f(xi + h, yi - k1 + 2*k2);
    
    Y5(end + 1) = yi + 1/6 * (k1 + 4*k2 + k3);
end

h = h * 2;
E2 = [];
p = 3;
for i = 1 : (T - t0) / h + 1
    E2(end + 1) = (Y5(2*i - 1) - Y4(i)) / (2^p - 1);
end

Y6 = [];
for i = 1 : (T - t0) / h + 1
    Y6(end + 1) = Y5(2*i - 1) + E2(i);
end


plot(X2, Y2, X2, Y5, X1, Y3, X1, Y6);
legend("Метод Рунге-Кутты 4 порядка", "Метод Рунге-Кутты 3 порядка", ...
    "Уточненный график метода Рунге-Кутты 4 порядка", "Уточненный график метода Рунге-Кутты 3 порядка");

XY = {'X', 'Y'};
XE = {'X', 'E'};

T1 = table(transpose(X1), transpose(Y1), 'VariableNames', XY)
T2 = table(transpose(X2), transpose(Y2), 'VariableNames', XY)
T3 = table(transpose(X1), transpose(E1), 'VariableNames', XE)
T4 = table(transpose(X1), transpose(Y3), 'VariableNames', XY)

T5 = table(transpose(X1), transpose(Y4), 'VariableNames', XY)
T6 = table(transpose(X2), transpose(Y5), 'VariableNames', XY)
T7 = table(transpose(X1), transpose(E2), 'VariableNames', XE)
T8 = table(transpose(X1), transpose(Y6), 'VariableNames', XY)
