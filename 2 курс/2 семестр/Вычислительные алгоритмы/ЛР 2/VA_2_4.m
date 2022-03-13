N = 4;
A = [2 15 22 7; 1 14.1 18.8 2.3; 2 4 9 9; -0.4 2.5 2.1 -2.4];
B = zeros(N, N);

for i = 1:N
    B(i, i) = A(i, i) * 0.1;
end

B = B + A;

rank_A = rank(A)

modified_A(1, 1) = 1.1 * A(1, 1);
rank_modified_A = rank(modified_A)

modified_A_2 = 1.1 * A;
rank_modified_A_2 = rank(modified_A_2)