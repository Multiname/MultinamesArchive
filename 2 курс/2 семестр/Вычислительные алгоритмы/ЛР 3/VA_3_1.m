S = 0;
for n = 1:3
    syms x;
    S = vpasolve(tan(pi * x / 4) - x - 3 == 0, x, [S+10^-29 Inf])
end
