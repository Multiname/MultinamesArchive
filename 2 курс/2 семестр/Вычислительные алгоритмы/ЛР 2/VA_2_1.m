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
c = cond(A);

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
    X_i(i, :) = A\transpose(B_i(i, :));
    D(i) = norm(X - transpose(X_i(i, :)), Inf) / norm(transpose(X_i(i, :)), Inf);
end

bar(1:n, D);

[b_m, index] = max(D);
delta_b = norm(transpose(B) - B_i(index, :), "inf") / norm(B, "inf");
delta_xm = c * delta_b;

fprintf('cond(A) = %.4f\n', c);
fprintf('δ(b) = %.4f\n', delta_b);
fprintf('δ(x) = %.4f\n', delta_xm);