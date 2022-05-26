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
fprintf("Интеграл = %f\n", I);

bma = (b - a) / 2;
apb = (a + b) / 2;

A = [
    2 1 0.55555555555556 0.347854845137454;
    0 1 0.88888888888888 0.652145154862546;
    0 0 0.55555555555556 0.652145154862546;
    0 0 0 0.347854845137454;
    ];

T = [
    0 -0.577350269189626 -0.77459666929954 -0.861136311594052;
    0 0.577350269189626 0 -0.339981043584856;
    0 0 0.77459666929954 0.339981043584856;
    0 0 0 0.861136311594052;
    ];

err = zeros(4:1);
for N = 1 : 4
    S = 0;
    for i = 1 : N
        S = S + A(i, N) * P(apb + bma * T(i, N));
    end
    S = bma * S;
    err(N) = I - S;
    fprintf("N = %i; S = %f; Error = %d\n", N, S, err(N));
end

B = bar(1:4, err);
text(B.XEndPoints, B.YEndPoints, string(B.YData), ...
    'HorizontalAlignment','center', ...
    'VerticalAlignment','bottom');

for N = 1 : 4
    S = 0;
    for i = 1 : N
        S = S + A(i, N) * F(apb + bma * T(i, N), N - 1);
    end
    S = bma * S;
    f = @(x) F(x, N - 1);
    fprintf("N = %i; S = %f; Error = %f\n", N, S, integral(f, a, b) - S);
end

function y = F(t, n)
    y = 0;
    for m = 0 : (2*n + 1)
        y = y + t.^m;
    end
end