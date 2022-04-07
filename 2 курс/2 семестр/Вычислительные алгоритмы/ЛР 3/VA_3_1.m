ezplot ('tan(pi * x / 4)', [-8 8]);
hold on
ezplot ('x + 3', [-8 8]);
hold on

syms x;
x_1 = fzero("tan(pi * x / 4) - x - 3", -5.5);
fprintf("Matlab x_1: %f\n", x_1);

x_2 = fzero("tan(pi * x / 4) - x - 3", 1.7);
fprintf("Matlab x_2: %f\n", x_2);

x_3 = fzero("tan(pi * x / 4) - x - 3", 5.8);
fprintf("Matlab x_3: %f\n", x_3);

fprintf("\n");
f = inline('tan(pi * x / 4) - x - 3');
df = inline('pi / (4 * cos(pi * x / 4)^2) - 1');

x_1 = newton(f, df, -5.6);
x_2 = newton(f, df, 1.7);
x_3 = newton(f, df, 5.8);

chord(f, -5.5, -5.6, 0.001, x_1);
chord(f, 1.7, 1.8, 0.001, x_2);
chord(f, 5.8, 5.9, 0.001, x_3);

function [root] = newton(f, df, x0)
    eps = 1e-6;
    root = x0;
    y0 = f(x0);
    k = 0;
    
    fprintf("Newton method table\n");
    
    while abs(y0) > eps
        old_root = root;
        root = old_root - f(old_root) / df(old_root);
        y0 = f(root);
        fprintf("%i %f %f %f %f", k, root, root - old_root, f(root));
        fprintf("\n");
        k = k + 1;
    end
    fprintf("\n");
end

function [root] = chord(f, a, b, eps, x_i)
    root = a;
    old_root = b;
    k = 0;
    fprintf("Chord method table\n");
    while abs(root - old_root) > eps
        old_root = root;
        root = old_root - (old_root - b) * f(old_root) / (f(old_root) - f(b));
        fprintf("%i %f %f %f %f\n", k, root, root - old_root, root - x_i, f(root));
        k = k + 1;
    end
    fprintf("\n");
end