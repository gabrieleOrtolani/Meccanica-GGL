
clc
close all
clear all

% import from file to array
mydata1 = importdata("datiSTOP_bello.txt")
%converto in matrice
%mydata1 =table2array(mydata);

gyroX = mydata1(:,4) - mean(mydata1(:, 4));
gyroY = mydata1(:, 5) - mean(mydata1(:, 5));
gyroZ = mydata1(:,6) - mean(mydata1(:, 6));

Ts = 0.05;
Fs = 1/Ts;

L = max(size(gyroX)); %numero misurazioni
t = (0:L-1)*Ts;

windowSize = 10;
b = (1/windowSize)*ones(1,windowSize);
a = 1;

% filters the data in vector X with the
%  filter described by vectors A and B to create the filtered data Y.  
filteredX = filter(b, a, gyroX);
filteredY = filter(b, a, gyroY);
filteredZ = filter(b, a, gyroZ);

% accelerations analysis without filter
figure(1)
axis(1) = subplot(3,1,1);
plot(t, gyroX);
title('gyroX', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
grid on;

axis(2) = subplot(3,1,2);
plot(t, gyroY);
title('gyroY', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
grid on;

axis(3) = subplot(3,1,3);
plot(t, gyroZ);
title('gyroZ', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
grid on;

linkaxes(axis, 'x');
% accelerations analisys with filter
figure(2)
axis(1) = subplot(3,1,1);
plot(t, filteredX);
title('gyroX filtered', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
grid on;

axis(2) = subplot(3,1,2);
plot(t, filteredY);
title('gyroY filtered', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
grid on;

axis(3) = subplot(3,1,3);
plot(t, filteredZ);
title(['gyroZ filtered'], 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
grid on;


linkaxes(axis, 'x');
%% FREQUENCY DOMAIN ANALYSIS
% frequency analisys
% fft(X) is the discrete Fourier transform (DFT) of vector X
tfourierX = fft(filteredX);
tfourierY = fft(filteredY);
tfourierZ = fft(filteredZ);

tfourierX = abs(tfourierX/L);
fX = tfourierX(1:L/2+1);
fX(2:end-1) = 2*fX(2:end-1); 

tfourierY = abs(tfourierY/L);
fY = tfourierY(1:L/2+1);
fY(2:end-1) = 2*fY(2:end-1);

tfourierZ = abs(tfourierZ/L);
fZ = tfourierZ(1:L/2+1);
fZ(2:end-1) = 2*fZ(2:end-1); 

f = Fs*(0:(L/2))/L;

figure(3)
axis(1) = subplot(3,1,1);
plot(f, fX);
title('x-axis frequency analysis', 'FontSize', 18);
xlabel('f [Hz]', 'FontSize', 16);
ylabel('|fX(f)|', 'FontSize', 16);
grid on;

axis(2) = subplot(3,1,2);
plot(f, fY);
title('y-axis frequency analysis', 'FontSize', 18);
xlabel('f [Hz]', 'FontSize', 16);
ylabel('|fY(f)|', 'FontSize', 16);
grid on;

axis(3) = subplot(3,1,3);
plot(f, fZ);
title('z-axis frequency analysis', 'FontSize', 18);
xlabel('f [Hz]', 'FontSize', 16);
ylabel('|fZ(f)|', 'FontSize', 16);
grid on;

linkaxes(axis, 'x');
%% STABILITY
% stability analysis (BODE)
%Frequency Response Data (frd) models store the frequency response of linear 
%systems, for example, experimental data collected with a frequency analyzer.
 

sX = frd(fX, f, Ts);
sY = frd(fY, f, Ts);
sZ = frd(fZ, f, Ts);

np =2; % number of poles
nz = np - 1;

sXest = tfest(sX, np, nz);
sYest = tfest(sY, np, nz);
sZest = tfest(sZ, np, nz);

figure(4)
axis(1) = subplot(3,1,1);
bode(sXest);
title('x-axis Bode diagram', 'FontSize', 18);
grid on;

axis(2) = subplot(3,1,2);
bode(sYest);
title('y-axis Bode diagram', 'FontSize', 18);
grid on;

axis(3) = subplot(3,1,3);
bode(sZest);
title('z-axis Bode diagram', 'FontSize', 18);
grid on;

linkaxes(axis, 'x');

% stability analysis (ROOT LOCUS)
figure(5)
axis(1) = subplot(3,1,1);
rlocus(sXest);
title('Location of the X-axis roots', 'FontSize', 18);
grid on;

axis(2) = subplot(3,1,2);
rlocus(sYest);
title('Location of the Y-axis roots', 'FontSize', 18);
grid on;

axis(3) = subplot(3,1,3);
rlocus(sZest);
title('Location of the Z-axis roots', 'FontSize', 18);
grid on;

linkaxes(axis, 'x');

% stability analysis (ISSTABLE FUNCTION)
isstable(sXest)
isstable(sYest)
isstable(sZest)

% stability nyquist (NYQUIST FUNCTION)
figure(6);
axis(1) = subplot(3,1,1);
nyquist(sXest);
title('Nyquist asse X', 'FontSize', 18);
grid on;

axis(2) = subplot(3,1,2);
nyquist(sYest);
title('Nyquist asse Y', 'FontSize', 18);
grid on;

axis(3) = subplot(3,1,3);
nyquist(sZest);
title('Nyquist asse Z', 'FontSize', 18);
grid on;
wShow = 0:0.1:f(end);

figure(7);
axis(1) = subplot(3,1,1);
bodemag(sX, sXest, 'r', wShow);
title('Confronto frequenziale asse X', 'FontSize', 18);
legend('Sperimentale', 'Stimato', 'fontSize', 14);
grid on;

axis(2) = subplot(3,1,2);
bodemag(sY, sYest, 'r', wShow);
title('Confronto frequenziale asse Y', 'FontSize', 18);
legend('Sperimentale', 'Stimato', 'fontSize', 14);
grid on;

axis(3) = subplot(3,1,3);
bodemag(sZ, sZest, 'r', wShow);
title('Confronto frequenziale asse Z', 'FontSize', 18);
legend('Sperimentale', 'Stimato', 'fontSize', 14);
grid on;

linkaxes(axis, 'x');

