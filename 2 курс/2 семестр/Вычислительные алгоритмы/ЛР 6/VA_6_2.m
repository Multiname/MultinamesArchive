clc;
clear;

f = @(x) (2.*x).^3.*cos(x);
a = 0;
b = pi / 2;

I = integral(f, a, b)

S = zeros(19:1);
for n = 2 : 20
   h = (b - a) / n;
   S(n - 1) = 0;
   for i = 1 : n
       x_i = a + (i - 1) * h;
       x_i_1 = a + i * h;
       S(n - 1) = S(n - 1) + f((x_i + x_i_1) / 2) * h;
   end
   fprintf("n = %i; h = %f, S = %f\n", n, h, S(n - 1));
end

n = linspace(2, 20, 19);
h = (b - a) ./ n;
A = S - I;
x = linspace(h(19), h(1), 100);
y = (x.*1.07).^2;
plot(h, A,'-o', x, y, '--');
xlabel('Шаг h');
ylabel('Абсолютная погрешность')
legend('Зависимость погрешности', 'x^2')
