%% Stabilità accelerometro:

clc
close all
clear all

% import from file to array
ABS = importdata("./abs/dati1_abs.txt");
STOP = importdata("./stop/dati3_stop.txt");

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

%% Analisi in frequenza dell'accelerometro
% Calcola la trasformata di Fourier su ogni asse

Ts = 0.05;

% Calcola la frequenza di campionamento
Fs = 1/Ts; % la frequenza di campionamento è di 20 Hz

% Calcola il numero di campioni
N_abs = length(AccX_ABS);
N_stop = length(AccX_STOP);

% Calcola la frequenza di Nyquist
Fn = Fs/2;

%Calcola la trasformata di Fourier su ogni asse
X_ABS = fft(AccX_ABS)/N_abs;
Y_ABS = fft(AccY_ABS)/N_abs;
Z_ABS = fft(AccZ_ABS)/N_abs;


X_STOP = fft(AccX_STOP)/N_stop;
Y_STOP = fft(AccY_STOP)/N_stop;
Z_STOP = fft(AccZ_STOP)/N_stop;

% Calcola il vettore delle frequenze
f_abs_a = (0:N_abs-1)*Fs/N_abs;
f_stop_a = (0:N_stop-1)*Fs/N_stop;

%% Stabilità ACCELEROMETRO ABS

%Introduciamo prima la risposta in frequenza dei tre assi e in seguito
%calcoliamo la funzione di trasferimento:
Ts = 1/Fs;
rX_ABS = frd(X_ABS,f_abs_a,Ts);
rY_ABS = frd(Y_ABS,f_abs_a,Ts);
rZ_ABS = frd(Z_ABS,f_abs_a,Ts);

np = 8;
nz = np-1;

%Funzione di trasferimento:
fdtX_ABS = tfest(rX_ABS, np, nz);
fdtY_ABS =tfest(rY_ABS, np, nz);
fdtZ_ABS =tfest(rZ_ABS, np, nz);

%Esaminiamo la stabiità del sistema tramite vari metodi:
%Valutazione dei poli della funzione di trasferimento:
pole(fdtX_ABS)
pole(fdtY_ABS)
pole(fdtZ_ABS)

isstable(fdtX_ABS)
isstable(fdtY_ABS)
isstable(fdtZ_ABS)

%Valutazione tramite rlocus:
figure(1)
axis(1) = subplot(3,1,1);
rlocus(fdtX_ABS);
title('Luogo delle radici ABS asse X');
grid on;

axis(2) = subplot(3,1,2);
rlocus(fdtY_ABS);
title('Luogo delle radici ABS asse Y');
grid on;

axis(3) = subplot(3,1,3);
rlocus(fdtZ_ABS);
title('Luogo delle radici ABS asse Z');
grid on;


%Valutazione tramite Nyquist (Per semplicità visiva useremo la funzione nyqlog)
figure(2)
axis(1) = subplot(3,1,1);
nyquist(fdtX_ABS)
title('Nyquist abs asse X');
grid on;

axis(2) = subplot(3,1,2);
nyquist(fdtY_ABS)
title('Nyquist ABS asse Y');
grid on;

axis(3) = subplot(3,1,3);
nyquist(fdtZ_ABS)
title('Nyquist ABS asse Z');
grid on;

%% Stabilità Accelerometro stop:
%Introduciamo prima la risposta in frequenza dei tre assi e in seguito
%calcoliamo la funzione di trasferimento:
Ts = 1/Fs;
rX_STOP = frd(X_STOP,f_stop_a,Ts);
rY_STOP = frd(Y_STOP,f_stop_a,Ts);
rZ_STOP = frd(Z_STOP,f_stop_a,Ts);


np = 8;
nz = np-1;


%Funzione di trasferimento:
fdtX_STOP = tfest (rX_STOP, np, nz);
fdtY_STOP =tfest (rY_STOP, np, nz);
fdtZ_STOP =tfest (rZ_STOP, np, nz);

%Esaminiamo la stabiità del sistema tramite vari metodi:
%Valutazione dei poli della funzione di trasferimento:
pole(fdtX_STOP)
pole(fdtY_STOP)
pole(fdtZ_STOP)

isstable(fdtX_STOP)
isstable(fdtY_STOP)
isstable(fdtZ_STOP)

%Valutazione tramite rlocus:
figure(3)
axis(1) = subplot(3,1,1);
rlocus(fdtX_STOP);
title('Luogo delle radici STOP asse X');
grid on;

axis(2) = subplot(3,1,2);
rlocus(fdtY_STOP);
title('Luogo delle radici STOP asse Y');
grid on;

axis(3) = subplot(3,1,3);
rlocus(fdtZ_STOP);
title('Luogo delle radici STOP asse Z');
grid on;


%Valutazione tramite Nyquist
figure(4)
axis(1) = subplot(3,1,1);
nyquist(fdtX_STOP)
title('Nyquist STOP asse X');
grid on;

axis(2) = subplot(3,1,2);
nyquist(fdtY_STOP)
title('Nyquist STOP asse Y');
grid on;

axis(3) = subplot(3,1,3);
nyquist(fdtZ_STOP)
title('Nyquist STOP asse Z');
grid on;

