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

D = zeros(n, n);
X_ = zeros(n, 1);

delta = rand();
for k = 1:n
    for j = 1:n
        A_ = A;
        A_(k, j) = A(k, j) + delta;
        X_ = A_ \ B;
        D(k, j) = norm(X - X_, Inf) / norm (X, Inf);
        
        fprintf('A_%i_%i =\n', k, j);
        disp(A_);
        fprintf('X_%i_%i =\n', k, j);
        disp(X_);
    end 
end

disp('D = ');
disp(D);

bar(1:n, D);

rel_dx = max(max(D));
[rel_dx_i, rel_dx_j] = find(D == rel_dx);

A_ = A;
A_(rel_dx_i, rel_dx_j) = A(rel_dx_i, rel_dx_j) + delta;

rel_A = norm(A - A_, "inf")/norm(A, "inf");
rel_xm = c * rel_A;

disp('A_m = ');
disp(A_);
fprintf('δ(A) = %.4f\n', rel_A);
fprintf('δ(x) = %.4f\n', rel_xm);
fprintf('d_m = %.4f\n', rel_dx);