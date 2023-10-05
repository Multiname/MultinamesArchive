A1 = 1;
A2 = 0.7;
A3 = 1.5;
A4 = 2;

om1 = 20;
om2 = 90;
om3 = 60;
om4 = 45;

phi1 = 0;
phi2 = 120;
phi3 = -80;
phi4 = 40;

sr = 2500;
step = 1/sr;
t = (0:step:1);

S1 = A1*sin(2*pi*om1*t + phi1);
S2 = A2*sin(2*pi*om2*t + phi2);
S3 = A3*sin(2*pi*om3*t + phi3);
S4 = A4*sin(2*pi*om4*t + phi4);

S = (S1 + S2 + S3) .* S4;
subplot(7, 2, 2)
plot(t, S)

N_s = length(S);
ft = abs(fft(S));
frequencies = (0:N_s-1)*(sr/N_s);
subplot(7, 2, 1)
plot(frequencies(1:150), ft(1:150))

[pks, locs] = findpeaks(ft);

n = 3;
for i = 1:length(locs)/2
    [b, a] = butter(n, [locs(i)*0.92/(sr/2) locs(i)*1.08/(sr/2)], 'bandpass');
    f = filter(b, a, S);

    N_f = length(f);
    ftf = abs(fft(f));
    frequencies = (0:N_f-1)*(sr/N_f);
    subplot(7, 2, i*2 + 1)
    plot(frequencies(1:150), ftf(1:150))

    ftfi = ifft(ftf);
    subplot(7, 2, i*2 + 2)
    plot(t, ftfi)
end
