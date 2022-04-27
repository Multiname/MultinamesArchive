clc;
clear;

syms x;
f(x) = tan(sqrt(x))/sqrt(x);
fplot(f(x),[0.01 1]);
hold on;

R_2_2(x) = pade(f,'ExpansionPoint',1,'Order',[2,2]);
rat(R_2_2(0.5))

xx = linspace(0.01, 1, 100);
yy_2_2 = R_2_2(xx);
plot(xx, yy_2_2, '--r');
hold on;

R_5_4(x) = pade(f,'ExpansionPoint',1,'Order',[5,4]);

val = zeros(1, length(xx));
for i = 1 : length(xx)
    a = R_5_4(xx(i));
    %b = tan(sqrt(xx(i)))/sqrt(xx(i));
    b = f(xx(i));
    val(i) = abs(a - b);
end
m = max(val);
double(m)

vpa(R_2_2)

c_0_0 = 32.092547426026460909802462045313
c_0_1 = -3.5906692264207225242486732286867;
c_0_2 = 0.035709477375403940279719999164367;
c_1_0 = 32.092543868698179613063030252732
c_1_1 = -14.288167705155923568264683066608;
c_1_2 = 0.51939816042588529322441110139088;

c_2_0 = c_1_0 * c_0_1 - c_0_0 * c_1_1
c_2_1 = c_1_0 * c_0_2 - c_0_0 * c_1_2

c_3_0 = c_2_0 * c_1_1 - c_1_0 * c_2_1
