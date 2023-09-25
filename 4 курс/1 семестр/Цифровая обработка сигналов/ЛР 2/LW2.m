N = 38;
f = @(t) 3*sin(4*t);
T = 2*pi/4;
h = T/(N - 1);
X = 0:h:T;
F = f(X);
amplitude = 3;

%% Импульсное разложение
values = zeros(N, N);

for i=1:N
    for j=1:N
        if (j==i) 
            values(i, i) = F(i);
        end 
    end 
end

for k=1:N 
    subplot(5, 8, k);
    plot(X, values(:,k), '.-black', 'LineWidth', 1);
    axis([0 T -amplitude amplitude]);
end
sgtitle("Импульсное разложение");

%% Ступенчатое разложение

decomposition = zeros(N);

for i=2:N 
    difference = F(i) - F(i - 1); 
    for j=i:N
        decomposition(i, j) = difference;
    end 
end

for k=1:N 
    subplot(5, 8, k);
    plot(X, decomposition(k,:), '.-black', 'LineWidth', 1);
    axis([0 T -2 2]);
end
sgtitle("Ступенчатое разложение");

%% Чётно-нечётное разложение

even = zeros(N, 1);
uneven = zeros(N, 1);

for k=1:N
    even(k) = (F(k) + F(N-k+1)) / 2;
end
subplot(2, 1, 1);
plot(X, even, '.-black', 'LineWidth', 1);
axis([0 T -amplitude amplitude]);
legend("Чётная симметрия");

for k=1:N
    uneven(k) = (F(k) - F(N-k+1)) / 2;
end
subplot(2, 1, 2);
plot(X, uneven, '.-black', 'LineWidth', 1);
axis([0 T -amplitude amplitude]);
legend("Нечётная симметрия");
sgtitle("Чётно-нечётное разложение");

%% Чередующееся разложение
subplot(2, 1, 1);
F1 = F;
F2 = F;
for k = 1:(N) 
    if mod(k, 2) == 0 
        F1(k) = 0; 
    end
end
plot(X, F1, '.-black'); 
grid;
axis([0 T -amplitude amplitude]);
legend("Нечётные выборки");

subplot(2, 1, 2);
for k = 1:(N) 
    if mod(k, 2) ~= 0 
        F2(k) = 0; 
    end
end
plot(X, F2, '.-black'); 
grid;
axis([0 T -amplitude amplitude])
legend("Чётные выборки");
sgtitle("Чередующееся разложение");