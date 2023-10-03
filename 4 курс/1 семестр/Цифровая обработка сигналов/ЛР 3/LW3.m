%% Фильтр Баттерворта
n = 4;
[z, p, k] = buttap(n);		
[b, a] = zp2tf(z, p, k);
w = 0:0.1:5;					
h = freqs(b, a, w);
plot(w, abs(h)),	

%% Фильтр Чебышева 1 рода
n = 4;
Rp = 5;
[z, p, k] = cheb1ap(n, Rp);		
[b, a] = zp2tf(z, p, k);		
w = 0:0.1:5;					
h = freqs(b, a, w);
plot(w, abs(h)),	

%% Фильтр Чебышева 2 рода
n = 4;
Rs = 65;
[z, p, k] = cheb2ap(n, Rs);     
[b, a] = zp2tf(z, p, k);        
w = 0:0.1:5;                    
h = freqs(b, a, w);
plot(w, abs(h)),    

%% Эллиптический фильтр
n = 4;
Rp = 5;
Rs = 65;
[z, p, k] = ellipap(n, Rp, Rs);     
[b, a] = zp2tf(z, p, k);        
w = 0:0.1:5;                    
h = freqs(b, a, w);
plot(w, abs(h)),

%% Фильтр Бесселя
n = 4;
[z, p, k] = besselap(n);        
[b, a] = zp2tf(z, p, k);        
w = 0:0.1:5;                    
h = freqs(b, a, w);
plot(w, abs(h)),

%% Фильтр Баттерворта - ФНЧ
n = 4;
w0 = 3;
[z, p, k] = buttap(n);      
[b, a] = zp2tf(z, p, k);
[b1, a1] = lp2lp(b, a, w0);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Фильтр Чебышева 1 рода - ФНЧ
n = 4;
Rp = 5;
w0 = 3;
[z, p, k] = cheb1ap(n, Rp);     
[b, a] = zp2tf(z, p, k);        
[b1, a1] = lp2lp(b, a, w0);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Фильтр Чебышева 2 рода - ФНЧ
n = 4;
Rs = 65;
w0 = 3;
[z, p, k] = cheb2ap(n, Rs);     
[b, a] = zp2tf(z, p, k);        
[b1, a1] = lp2lp(b, a, w0);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Эллиптический фильтр - ФНЧ
n = 4;
Rp = 5;
Rs = 65;
w0 = 3;
[z, p, k] = ellipap(n, Rp, Rs);     
[b, a] = zp2tf(z, p, k);        
[b1, a1] = lp2lp(b, a, w0);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Фильтр Бесселя - ФНЧ
n = 4;
w0 = 3;
[z, p, k] = besselap(n);		
[b, a] = zp2tf(z, p, k);		
[b1, a1] = lp2lp(b, a, w0);
w = 0:0.1:5;					
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Фильтр Баттерворта - полосовой
n = 4;
w1 = 1;
w2 = 3;
[z, p, k] = buttap(n);      
[b, a] = zp2tf(z, p, k);
w0 = sqrt(w1 * w2);
Bw = w2 - w1;
[b1, a1] = lp2bp(b, a, w0, Bw);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Фильтр Чебышева 1 рода - полосовой
n = 4;
Rp = 5;
w1 = 1;
w2 = 3;
[z, p, k] = cheb1ap(n, Rp);     
[b, a] = zp2tf(z, p, k);
w0 = sqrt(w1 * w2);
Bw = w2 - w1;
[b1, a1] = lp2bp(b, a, w0, Bw);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Фильтр Чебышева 2 рода - полосовой
n = 4;
Rs = 65;
w1 = 1;
w2 = 3;
[z, p, k] = cheb2ap(n, Rs);     
[b, a] = zp2tf(z, p, k);        
w0 = sqrt(w1 * w2);
Bw = w2 - w1;
[b1, a1] = lp2bp(b, a, w0, Bw);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Эллиптический фильтр - полосовой
n = 4;
Rp = 5;
Rs = 65;
w1 = 1;
w2 = 3;
[z, p, k] = ellipap(n, Rp, Rs);     
[b, a] = zp2tf(z, p, k);        
w0 = sqrt(w1 * w2);
Bw = w2 - w1;
[b1, a1] = lp2bp(b, a, w0, Bw);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),

%% Фильтр Бесселя - полосовой
n = 4;
w1 = 1;
w2 = 3;
[z, p, k] = besselap(n);        
[b, a] = zp2tf(z, p, k);        
w0 = sqrt(w1 * w2);
Bw = w2 - w1;
[b1, a1] = lp2bp(b, a, w0, Bw);
w = 0:0.1:5;                    
h = freqs(b1, a1, w);
plot(w, abs(h)),
