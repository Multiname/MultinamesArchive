clc;
clear;
clear global;

x = [-0.6 -0.5 -0.3 -0.2 0 0.2];
y = sin(x);

global Matrix;

xx = linspace(-0.6, 0.2, 81);
Pix = zeros(1, length(x));
dFx = zeros(1, length(x));
Mi = zeros(1, length(x));
Ri = zeros(1, length(x));

for i = 1 : length(x)
    t = zeros(1, i);
    for j = 1 : i
        t(j) = x(j);
    end
    
    yy = newton(t, y, xx);
    Pix(i) = yy(21);
    dFx(i) = sin(-0.4) - yy(21);
    
    syms q;
    Mi(i) = sin(fminbnd(inline(-diff(sin(q), i)), -0.6, x(i)));
    
    wi = 1;
    for j = 1 : i
        wi = wi * (-0.4 - x(j));
    end
    
    Ri(i) = Mi(i) * wi / factorial(i);
end

yy = newton(x, y, xx);

figure
plot(xx,yy, '-g', xx, sin(xx),'--r')
grid on;
opengl('software');
opengl('save','software');
legend('Через интерполяционный многочлен Ньютона', 'sin(x)');

names = {'i','Узлы','Pi(x*)','f(x*)-Pi(x*)','Mi+1','Ri(x*)'};
i = [0;1;2;3;4;5];

T = table(i,transpose(x),transpose(Pix),transpose(dFx),transpose(Mi),transpose(Ri),'VariableNames',names)

function yy = newton(x, y, xx)
    N = length(x);
    global Matrix;
    dif = y;
    for  k = 1 : N-1
        for i = 1: N - k
            dif(i) = (dif(i+1) - dif(i)) / (x(i+k) - x(i))
            Matrix(i, k) = dif(i);
        end
    end
    yy = dif(1) * ones(size(xx));
    for k = 2 : N
        yy = dif(k) + (xx - x(k)) .* yy;
    end
end