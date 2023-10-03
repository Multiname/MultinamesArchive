amp = 0.1;
step = 0.001;
t = (0:step:0.25);

freq1 = 25;
freq2 = 40;
freq3 = 60;

s1 = amp*sin(2*pi*freq1*t);
s2 = amp*sin(2*pi*freq2*t);
s3 = amp*sin(2*pi*freq3*t);

%% Фильтр Баттерворта, s1 + s2
s = s1 + s2;

subplot(5, 1, 1)
plot(t, s1)
subplot(5, 1, 2)
plot(t, s2)
subplot(5, 1, 3)
plot(t, s)

n = 4;
w0 = 0.15;
[z, p, k] = buttap(n);      
[b, a] = zp2tf(z, p, k);

[b1, a1] = lp2hp(b, a, w0);                  
f = abs(freqs(b1, a1, t));
subplot(5, 1, 4)
plot(t, f)

sf = s1 + s2.*f;
subplot(5, 1, 5)
plot(t, sf)

%% Фильтр Чебышева 1 рода, s1 + s2
s = s1 + s2;

subplot(5, 1, 1)
plot(t, s1)
subplot(5, 1, 2)
plot(t, s2)
subplot(5, 1, 3)
plot(t, s)

n = 4;
Rp = 0.1;
[z, p, k] = cheb1ap(n, Rp);
[b, a] = zp2tf(z, p, k);

w1 = 0.05;
w2 = 0.2;
w0 = 2 * pi * sqrt(w1 * w2);
Bw = 2 * pi * (w2 - w1);
[b2, a2] = lp2bs(b, a, w0, Bw);
f = abs(freqs(b2, a2, 2*pi*t));
subplot(5, 1, 4)
plot(t, f);

sf = s1.*f + s2;
subplot(5, 1, 5)
plot(t, sf)

%% Фильтр Чебышева 2 рода, s1 + s2
s = s1 + s2;

subplot(5, 1, 1)
plot(t, s1)
subplot(5, 1, 2)
plot(t, s2)
subplot(5, 1, 3)
plot(t, s)

n = 4;
Rs = 40;
w0 = 0.2;
[z, p, k] = cheb2ap(n, Rs);
[b, a] = zp2tf(z, p, k);

[b1, a1] = lp2lp(b, a, w0);
f = abs(freqs(b1, a1, t));
subplot(5, 1, 4)
plot(t, f);

sf = s1.*f + s2;
subplot(5, 1, 5)
plot(t, sf)

%% Эллиптический фильтр, s1 + s2
s = s1 + s2;

subplot(5, 1, 1)
plot(t, s1)
subplot(5, 1, 2)
plot(t, s2)
subplot(5, 1, 3)
plot(t, s)

n = 4;
Rp = 0.1;
Rs = 40;
w1 = 0.05;
w2 = 0.15;
[z, p, k] = ellipap(n, Rp, Rs);
[b, a] = zp2tf(z, p, k);

w0 = sqrt(w1 * w2);
Bw = w2 - w1;
[b1, a1] = lp2bp(b, a, w0, Bw);
f = abs(freqs(b1, a1, t));
subplot(5, 1, 4)
plot(t, f);

sf = s1 + s2.*f;
subplot(5, 1, 5)
plot(t, sf)

%% Фильтр Баттерворта, s1 + s2 + s3
s = s1 + s2 + s3;

subplot(6, 1, 1)
plot(t, s1)
subplot(6, 1, 2)
plot(t, s2)
subplot(6, 1, 3)
plot(t, s3)
subplot(6, 1, 4)
plot(t, s)

n = 4;
w1 = 0.05;
w2 = 0.15;
[z, p, k] = buttap(n);
[b, a] = zp2tf(z, p, k);

w0 = sqrt(w1 * w2);
Bw = w2 - w1;
[b1, a1] = lp2bp(b, a, w0, Bw);                
f = abs(freqs(b1, a1, t));
subplot(6, 1, 5)
plot(t, f)

sf = s1 + s2.*f + s3;
subplot(6, 1, 6)
plot(t, sf)

%% Фильтр Чебышева 1 рода, s1 + s2 + s3
s = s1 + s2 + s3;

subplot(6, 1, 1)
plot(t, s1)
subplot(6, 1, 2)
plot(t, s2)
subplot(6, 1, 3)
plot(t, s3)
subplot(6, 1, 4)
plot(t, s)

n = 4;
Rp = 0.1;
w0 = 0.1;
[z, p, k] = cheb1ap(n, Rp);     
[b, a] = zp2tf(z, p, k);

[b1, a1] = lp2lp(b, a, w0);          
f = abs(freqs(b1, a1, t));
subplot(6, 1, 5)
plot(t, f)

sf = (s1 + s2).*f + s3;
subplot(6, 1, 6)
plot(t, sf)

%% Фильтр Чебышева 2 рода, s1 + s2 + s3
s = s1 + s2 + s3;

subplot(6, 1, 1)
plot(t, s1)
subplot(6, 1, 2)
plot(t, s2)
subplot(6, 1, 3)
plot(t, s3)
subplot(6, 1, 4)
plot(t, s)

n = 4;
Rs = 40;
[z, p, k] = cheb2ap(n, Rs);
[b, a] = zp2tf(z, p, k);

w1 = 0.05;
w2 = 0.1;
w0 = 2 * pi * sqrt(w1 * w2);
Bw = 2 * pi * (w2 - w1);
[b2, a2] = lp2bs(b, a, w0, Bw);
f = abs(freqs(b2, a2, 2*pi*t));
subplot(6, 1, 5)
plot(t, f);

sf = (s1 + s3).*f + s2;
subplot(6, 1, 6)
plot(t, sf)

%% Эллиптический фильтр, s1 + s2 + s3
s = s1 + s2 + s3;

subplot(6, 1, 1)
plot(t, s1)
subplot(6, 1, 2)
plot(t, s2)
subplot(6, 1, 3)
plot(t, s3)
subplot(6, 1, 4)
plot(t, s)

n = 4;
Rp = 0.1;
Rs = 40;
w0 = 0.15;
[z, p, k] = ellipap(n, Rp, Rs);
[b, a] = zp2tf(z, p, k);

[b1, a1] = lp2hp(b, a, w0);                  
f = abs(freqs(b1, a1, t));
subplot(6, 1, 5)
plot(t, f);

sf = s1 + s2 + s3.*f;
subplot(6, 1, 6)
plot(t, sf)
