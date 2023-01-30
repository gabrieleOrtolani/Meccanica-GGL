clc
close all
clear all

% import from file to array
ABS = importdata("datiABS_bellobello.txt");
STOP = importdata("datiSTOP_bello.txt");

%tempo di campionamento ABS
tempo_ABS= ABS(:,8)*0.001;
%giroscopio ABS 
gyroX_ABS = ABS(:, 4);
gyroY_ABS= ABS(:, 5);
gyroZ_ABS = ABS(:, 6);
%accelerazioni ABS 
AccX_ABS = ABS(:, 1);
AccY_ABS = ABS(:, 2);
AccZ_ABS = ABS(:, 3);
%spazio (distanza) ABS 
distanza_ABS = ABS(:,7);
pwm_ABS = ABS(:,9);



%tempo di campionamento STOP
tempo_STOP = STOP(:,8)*0.001;
%giroscopio STOP 
gyroX_STOP = STOP(:, 4);
gyroY_STOP = STOP(:, 5);
gyroZ_STOP = STOP(:, 6);
%accelerazioni STOP
AccX_STOP =STOP(:, 1);
AccY_STOP =STOP(:, 2);
AccZ_STOP =STOP(:, 3);
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
ylabel('°/s', 'FontSize', 16);
axis(2) = subplot(3,1,2);
plot(tempo_STOP,AccY_STOP,tempo_ABS,AccY_ABS)
title('AccY', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
axis(3) = subplot(3,1,3);
plot(tempo_STOP,AccZ_STOP,tempo_ABS,AccZ_ABS)
title('AccZ', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);

%GRAFICO PWM-DISTANZA
figure(4)
axis(1)=subplot(2,1,1);
plot(tempo_ABS,distanza_ABS,tempo_ABS,pwm_ABS)
title('pwm-distnza nel tempo', 'FontSize', 18);
legend('Distanza', 'PWM', 'fontSize', 14);

axis(2)=subplot(2,1,2);
plot(tempo_STOP,distanza_STOP,tempo_STOP,pwm_STOP)
legend('Distanza', 'PWM', 'fontSize', 14);



figure(5)
strips(AccY_STOP,0.18,1000,1.25)
hold on
strips(AccY_ABS,0.18,1000,1.25)



