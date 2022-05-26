clc;
clear;

c_0 = 1;
c_1 = 0.9;
c_2 = 0.8;
c_3 = 0.7;
c_4 = 0.5;

a = 1;
b = 1.44;

P = @(x) c_0 + c_1.*x + c_2.*x.^2 + c_3.*x.^3 + c_4.*x.^4;

I = integral(P, a, b);
Trap = (P(a) + P(b)) / 2 * (b - a);
Simp = (b - a) / 6 * (P(a) + 4*P((a + b) / 2) + P(b));
fprintf("Интеграл = %f\n", I);
fprintf("Метод трапеций = %f; погрешность = %f\n", Trap, I - Trap);
fprintf("Формула Симпсона = %f; погрешность = %f\n", Simp, I - Simp);

syms x;
P2(x) = diff(c_0 + c_1.*x + c_2.*x.^2 + c_3.*x.^3 + c_4.*x.^4, 2);
xm = fminbnd(-abs(P2), a, b);
m = vpa(P2(xm));

n = ceil(solve(m * (b - a)^3 / (12 * x^2) == 0.0001, x));
n = n(2);

h = (b - a) / n;
S = 0;
for i = 1 : n
    x_i = a + (i - 1)*h;
    x_i_1 = a + i*h;
    S = S + (P(x_i) + P(x_i_1)) / 2 * h;
end
fprintf("n = %i; h = %f; метод трапеций = %f; погрешность = %f\n", n, h, S, I - S);

P4(x) = diff(c_0 + c_1.*x + c_2.*x.^2 + c_3.*x.^3 + c_4.*x.^4, 4);
xm = fminbnd(-abs(P4), a, b);
m = vpa(P4(xm));

n = ceil(solve((b - a) / 2880 * ((b - a) / x)^4 * m == 0.0001, x));
n = n(2);

if (mod(n, 2) ~= 0)
    n = n + 1;
end
h = (b - a) / n;
S = P(a) + P(b);
for i = 1 : (n - 1)
    x_i = a + i*h;
    if (mod(i, 2) == 0)
        S = S + 2*P(x_i);
    else
        S = S + 4*P(x_i);
    end
end
S = S * h / 3;
fprintf("n = %i; h = %f; формула Симпсона = %f; погрешность = %f\n", n, h, S, I - S);