clc;
clear;

x = [-0.6 -0.5 -0.3 -0.2 0 0.2];
y = sin(x);

cs = spline(x,[cos(-0.6) y cos(0.2)]);
xx = linspace(-0.6, 0.2, 81);
%xx_0 = linspace(-0.6, -0.5, 11);
%xx = linspace(-0.5, 0, 51);
%xx_n = linspace(0, 0.2, 21);
%yy_0 = linspace(cos(-0.6), cos(-0.6), 11);
%yy = spline(x,y,xx);
%yy_n = linspace(cos(0.2), cos(0.2), 21);
plot(x,y,'--o',xx,ppval(cs,xx),'-');
%plot(x, y, 'o', xx_0, yy_0, xx, yy, xx_n, yy_n);