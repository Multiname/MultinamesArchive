N = 15;
n = 6;
A = zeros(n, n);
for i = 1:n
    for j = 1:n
        c = 0.1 * N * i * j;
        A(i, j) = 88.5 / (c + 0.03 * c^2);
    end
end

B = zeros(n, 1) + N;

X = A\B;
c = cond(A, 1);

disp('A = ');
disp(A);
disp('X = ');
disp(X);
disp('B = ');
disp(B);

fprintf('cond(A) = %.4f\n\n', c);

B_i = zeros(n, n);
D = zeros(n, 1);
X_i = zeros(n, n);

delta = rand();
for i = 1:n
    for k = 1:n
        if k == i
            B_i(i, k) = B(k) + delta;
        else
            B_i(i, k) =  B(k);
        end
    end
    X_i(:, i) = A\B_i(:, i);
    D(i) = norm(X - X_i(:, i), Inf) / norm(X, Inf);
end

disp('B_i = ');
disp(B_i);
disp('X_i = ');
disp(X_i);
disp('D = ');
disp(D);

bar(1:n, D);

[d_m, index] = max(D);
b_m = B_i(:, index);
delta_b = norm(B - b_m, "inf") / norm(B, "inf");
delta_x_m = c * delta_b;

disp('b_m = ');
disp(b_m);

fprintf('δ(b_m) = %.4f\n', delta_b);
fprintf('δ(x_m) = %.4f\n', delta_x_m);
fprintf('d_m = %.4f\n', d_m);