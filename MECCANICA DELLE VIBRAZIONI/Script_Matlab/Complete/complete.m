clc
close all
clear all

%%Accelerometro e giroscpio moltiplicati per 1.5

% import from file to array
ABS = importdata("./abs/dati3_abs.txt");
STOP = importdata("./stop/dati5_stop.txt");

%tempo di campionamento ABS
tempo_ABS= ABS(:,8)*0.001;
%giroscopio ABS 
gyroX_ABS = ABS(:, 4)/131.0;% [°] unit
gyroY_ABS= ABS(:, 5)/131.0;% [°] unit
gyroZ_ABS = ABS(:, 6)/131.0;% [°] unit
%accelerazioni ABS 
AccX_ABS = ABS(:, 1)/16384.0;% [g] unit
AccY_ABS = ABS(:, 2)/16384.0;% [g] unit
AccZ_ABS = ABS(:, 3)/16384.0;% [g] unit
%spazio (distanza) ABS 
distanza_ABS = ABS(:,7);
pwm_ABS = ABS(:,9);



%tempo di campionamento STOP
tempo_STOP = STOP(:,8)*0.001;
%giroscopio STOP 
gyroX_STOP = STOP(:, 4)/131.0;% [°] unit
gyroY_STOP = STOP(:, 5)/131.0;% [°] unit
gyroZ_STOP = STOP(:, 6)/131.0;% [°] unit
%accelerazioni STOP
AccX_STOP =STOP(:, 1)/16384.0;% [g] unit
AccY_STOP =STOP(:, 2)/16384.0;% [g] unit
AccZ_STOP =STOP(:, 3)/16384.0;% [g] unit
%spazio (distanza) STOP 
distanza_STOP = STOP(:,7);
pwm_STOP = STOP(:,9);

%GRAFICO SPAZIO-TEMPO
figure(1)
axis(1) = subplot(3,1,1);
plot(tempo_STOP,distanza_STOP);
title('Distanza - Tempo', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('cm', 'FontSize', 16);
grid on;
axis(2) = subplot(3,1,2);
plot(tempo_ABS,distanza_ABS);
xlabel('t [sec]', 'FontSize', 16);
ylabel('cm', 'FontSize', 16);
grid on;
axis(3)=subplot(3,1,3);
plot(tempo_ABS,distanza_ABS,tempo_STOP,distanza_STOP);
xlabel('t [sec]', 'FontSize', 16);
ylabel('cm', 'FontSize', 16);
grid on;


%GRAFICO GIROSCOPIO
figure(2)
axis(1) = subplot(3,1,1);
plot(tempo_STOP,gyroX_STOP,tempo_ABS,gyroX_ABS)
title('gyroX', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
legend('Senza ABS', 'ABS')
axis(2) = subplot(3,1,2);
plot(tempo_STOP,gyroY_STOP,tempo_ABS,gyroY_ABS)
title('gyroY', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
axis(3) = subplot(3,1,3);
plot(tempo_STOP,gyroZ_STOP,tempo_ABS,gyroZ_ABS)
title('gyroZ', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);

%GRAFICO ACCELERAZIONI
figure(3)
axis(1) = subplot(3,1,1);
plot(tempo_STOP,AccX_STOP,tempo_ABS,AccX_ABS)
title('AccX', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);
legend('Senza ABS', 'ABS')
axis(2) = subplot(3,1,2);
plot(tempo_STOP,AccY_STOP,tempo_ABS,AccY_ABS)
title('AccY', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);
axis(3) = subplot(3,1,3);
plot(tempo_STOP,AccZ_STOP,tempo_ABS,AccZ_ABS)
title('AccZ', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);

%GRAFICO PWM-DISTANZA
figure(4)
axis(1)=subplot(2,1,1);
plot(tempo_ABS,distanza_ABS,tempo_ABS,pwm_ABS)
title('pwm-distanza nel tempo', 'FontSize', 18);
legend('Distanza', 'PWM', 'fontSize', 14);

axis(2)=subplot(2,1,2);
plot(tempo_STOP,distanza_STOP,tempo_STOP,pwm_STOP)
legend('Distanza', 'PWM', 'fontSize', 14);

% Analsi in frequenza:
%% Analisi in frequenza del Giroscopio

%Tempo campionamento(uguale per tutte le misurazioni)
Ts = 0.05;

% Calcola la frequenza di campionamento
Fs = 1/Ts ; % la frequenza di campionamento è di di circa 20Hz 

% Calcola il numero di campioni
N_abs = length(gyroX_ABS);
N_stop = length(gyroX_STOP);

% Calcola la frequenza di Nyquist
Fn = Fs/2;

% Calcola la trasformata di Fourier su ogni asse
X_abs = fft(gyroX_ABS)/N_abs;
Y_abs = fft(gyroY_ABS)/N_abs;
Z_abs = fft(gyroZ_ABS)/N_abs;


X_stop = fft(gyroX_STOP)/N_stop;
Y_stop = fft(gyroY_STOP)/N_stop;
Z_stop = fft(gyroZ_STOP)/N_stop;

% Calcola il vettore delle frequenze
f_abs_g = (0:N_abs-1)*Fs/N_abs;
f_stop_g = (0:N_stop-1)*Fs/N_stop;


% Visualizza i risultati della trasformata di Fourier sugli assi x, y e z
figure(5);
subplot(3,1,1);
plot(f_abs_g,abs(X_abs));
title('Trasformata di Fourier sull''asse x del Giroscopio ABS');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

subplot(3,1,2);
plot(f_abs_g,abs(Y_abs));
title('Trasformata di Fourier sull''asse y del Giroscopio ABS');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

subplot(3,1,3);
plot(f_abs_g,abs(Z_abs));
title('Trasformata di Fourier sull''asse z del Giroscopio ABS');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');


figure(6);
subplot(3,1,1);
plot(f_stop_g,abs(X_stop));
title('Trasformata di Fourier sull''asse x del Giroscopio STOP');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

subplot(3,1,2);
plot(f_stop_g,abs(Y_stop));
title('Trasformata di Fourier sull''asse y del Giroscopio STOP');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

subplot(3,1,3);
plot(f_stop_g,abs(Z_stop));
title('Trasformata di Fourier sull''asse z del Giroscopio STOP');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

%% Analisi in frequenza dell'accelerometro

Ts = 0.05;

% Calcola la frequenza di campionamento
Fs = 1/Ts; % la frequenza di campionamento è di 20 Hz

% Calcola il numero di campioni
N_abs = length(AccX_ABS);
N_stop = length(AccX_STOP);

% Calcola la frequenza di Nyquist
Fn = Fs/2;

% Calcola la trasformata di Fourier su ogni asse

X_abs = fft(AccX_ABS)/N_abs;
Y_abs = fft(AccY_ABS)/N_abs;
Z_abs = fft(AccZ_ABS)/N_abs;


X_stop = fft(AccX_STOP)/N_stop;
Y_stop = fft(AccY_STOP)/N_stop;
Z_stop = fft(AccZ_STOP)/N_stop;

% Calcola il vettore delle frequenze
f_abs_a = (0:N_abs-1)*Fs/N_abs;
f_stop_a = (0:N_stop-1)*Fs/N_stop;


% Visualizza i risultati della trasformata di Fourier sugli assi x, y e z
figure(6);
subplot(3,1,1);
plot(f_abs_a,abs(X_abs));
title('Trasformata di Fourier sull''asse x dell Accelerometro ABS');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

subplot(3,1,2);
plot(f_abs_a,abs(Y_abs));
title('Trasformata di Fourier sull''asse y dell Accelerometro ABS');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

subplot(3,1,3);
plot(f_abs_a,abs(Z_abs));
title('Trasformata di Fourier sull''asse z dell Accelerometro ABS');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');


figure(7);
subplot(3,1,1);
plot(f_stop_a,abs(X_stop));
title('Trasformata di Fourieir sull''asse x dell Accelerometro  STOP');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

subplot(3,1,2);
plot(f_stop_a,abs(Y_stop));
title('Trasformata di Fourier sull''asse y dell Accelerometro STOP');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');

subplot(3,1,3);
plot(f_stop_a,abs(Z_stop));
title('Trasformata di Fourier sull''asse z dell Accelerometro STOP');
xlabel('Frequenza (Hz)');
ylabel('Amplitude');




