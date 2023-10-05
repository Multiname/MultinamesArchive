amp = 0.1;
sr = 1000;
step = 1/sr;
t = (0:step:0.25);

freq1 = 25;
freq2 = 40;
freq3 = 60;

s1 = amp*sin(2*pi*freq1*t);
s2 = amp*sin(2*pi*freq2*t);
s3 = amp*sin(2*pi*freq3*t);

%% Фильтр Баттерворта, s1 + s2
s = s1 + s2;

subplot(4, 1, 1)
plot(t, s)

n = 4;
[z, p, k] = buttap(n);
[b, a] = zp2tf(z, p, k);

f = abs(filter(b, a, s));

sf = s1 + s2.*f;
subplot(4, 1, 2)
plot(t, sf)

N_s = length(s);
ft = fft(s);
frequencies = (0:N_s-1)*(sr/N_s);
subplot(4, 1, 3)
plot(frequencies(1:31), ft(1:31))

N_sf = length(sf);
ftf = fft(sf);
frequencies = (0:N_sf-1)*(sr/N_sf);
subplot(4, 1, 4)
plot(frequencies(1:31), ftf(1:31))

%% Фильтр Чебышева 1 рода, s1 + s2
s = s1 + s2;

subplot(4, 1, 1)
plot(t, s)

n = 25;
Rp = 0.1;
[z, p, k] = cheb1ap(n, Rp);
[b, a] = zp2tf(z, p, k);

f = abs(filter(b, a, s));

sf = s1.*f + s2;
subplot(4, 1, 2)
plot(t, sf)

N_s = length(s);
ft = fft(s);
frequencies = (0:N_s-1)*(sr/N_s);
subplot(4, 1, 3)
plot(frequencies(1:31), ft(1:31))

N_sf = length(sf);
ftf = fft(sf);
frequencies = (0:N_sf-1)*(sr/N_sf);
subplot(4, 1, 4)
plot(frequencies(1:31), ftf(1:31))

%% Фильтр Чебышева 2 рода, s1 + s2
s = s1 + s2;

subplot(4, 1, 1)
plot(t, s)

n = 4;
Rs = 40;
[z, p, k] = cheb2ap(n, Rs);
[b, a] = zp2tf(z, p, k);

f = abs(filter(b, a, s));

sf = s1.*f + s2;
subplot(4, 1, 2)
plot(t, sf)

N_s = length(s);
ft = fft(s);
frequencies = (0:N_s-1)*(sr/N_s);
subplot(4, 1, 3)
plot(frequencies(1:31), ft(1:31))

N_sf = length(sf);
ftf = fft(sf);
frequencies = (0:N_sf-1)*(sr/N_sf);
subplot(4, 1, 4)
plot(frequencies(1:31), ftf(1:31))

%% Эллиптический фильтр, s1 + s2
s = s1 + s2;

subplot(4, 1, 1)
plot(t, s)

n = 25;
Rp = 0.1;
Rs = 40;
[z, p, k] = ellipap(n, Rp, Rs);
[b, a] = zp2tf(z, p, k);

f = abs(filter(b, a, s));

sf = s1 + s2.*f;
subplot(4, 1, 2)
plot(t, sf)

N_s = length(s);
ft = fft(s);
frequencies = (0:N_s-1)*(sr/N_s);
subplot(4, 1, 3)
plot(frequencies(1:31), ft(1:31))

N_sf = length(sf);
ftf = fft(sf);
frequencies = (0:N_sf-1)*(sr/N_sf);
subplot(4, 1, 4)
plot(frequencies(1:31), ftf(1:31))

%% Фильтр Баттерворта, s1 + s2 + s3
s = s1 + s2 + s3;

subplot(4, 1, 1)
plot(t, s)

n = 4;
w1 = 0.05;
w2 = 0.15;
[z, p, k] = buttap(n);
[b, a] = zp2tf(z, p, k);

f = abs(filter(b, a, s));

sf = s1 + s2.*f + s3;
subplot(4, 1, 2)
plot(t, sf)

N_s = length(s);
ft = fft(s);
frequencies = (0:N_s-1)*(sr/N_s);
subplot(4, 1, 3)
plot(frequencies(1:31), ft(1:31))

N_sf = length(sf);
ftf = fft(sf);
frequencies = (0:N_sf-1)*(sr/N_sf);
subplot(4, 1, 4)
plot(frequencies(1:31), ftf(1:31))

%% Фильтр Чебышева 1 рода, s1 + s2 + s3
s = s1 + s2 + s3;

subplot(4, 1, 1)
plot(t, s)

n = 25;
Rp = 0.1;
w0 = 0.1;
[z, p, k] = cheb1ap(n, Rp);     
[b, a] = zp2tf(z, p, k);

f = abs(filter(b, a, s));

sf = (s1 + s2).*f + s3;
subplot(4, 1, 2)
plot(t, sf)

N_s = length(s);
ft = fft(s);
frequencies = (0:N_s-1)*(sr/N_s);
subplot(4, 1, 3)
plot(frequencies(1:31), ft(1:31))

N_sf = length(sf);
ftf = fft(sf);
frequencies = (0:N_sf-1)*(sr/N_sf);
subplot(4, 1, 4)
plot(frequencies(1:31), ftf(1:31))

%% Фильтр Чебышева 2 рода, s1 + s2 + s3
s = s1 + s2 + s3;

subplot(4, 1, 1)
plot(t, s)

n = 4;
Rs = 40;
[z, p, k] = cheb2ap(n, Rs);
[b, a] = zp2tf(z, p, k);

f = abs(filter(b, a, s));

sf = (s1 + s3).*f + s2;
subplot(4, 1, 2)
plot(t, sf)

N_s = length(s);
ft = fft(s);
frequencies = (0:N_s-1)*(sr/N_s);
subplot(4, 1, 3)
plot(frequencies(1:31), ft(1:31))

N_sf = length(sf);
ftf = fft(sf);
frequencies = (0:N_sf-1)*(sr/N_sf);
subplot(4, 1, 4)
plot(frequencies(1:31), ftf(1:31))

%% Эллиптический фильтр, s1 + s2 + s3
s = s1 + s2 + s3;

subplot(4, 1, 1)
plot(t, s)

n = 25;
Rp = 0.1;
Rs = 40;
w0 = 0.15;
[z, p, k] = ellipap(n, Rp, Rs);
[b, a] = zp2tf(z, p, k);

f = abs(filter(b, a, s));

sf = s1 + s2 + s3.*f;
subplot(4, 1, 2)
plot(t, sf)

N_s = length(s);
ft = fft(s);
frequencies = (0:N_s-1)*(sr/N_s);
subplot(4, 1, 3)
plot(frequencies(1:31), ft(1:31))

N_sf = length(sf);
ftf = fft(sf);
frequencies = (0:N_sf-1)*(sr/N_sf);
subplot(4, 1, 4)
plot(frequencies(1:31), ftf(1:31))