N = 4;
A = [2 15 22 7; 1 14.1 18.8 2.3; 2 4 9 9; -0.4 2.5 2.1 -2.4];

rank_A = rank(A);

modified_A = zeros(N, N) + A;
modified_A(1, 1) = 1.001 * A(1, 1);
rank_modified_A = rank(modified_A);

modified_A_2 = 1.001 * A;
rank_modified_A_2 = rank(modified_A_2);

fprintf('rank(A) = %.4f\n', rank_A);
fprintf('rank(A_1) = %.4f\n', rank_modified_A);
fprintf('rank(A_2) = %.4f\n', rank_modified_A_2);