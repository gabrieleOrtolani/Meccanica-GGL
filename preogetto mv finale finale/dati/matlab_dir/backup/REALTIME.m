clc
close all
clear all

% import from file to array
ABS = importdata("dati.txt");


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




%GRAFICO SPAZIO-TEMPO
figure(1)
plot(tempo_ABS,distanza_ABS);
xlabel('t [sec]', 'FontSize', 16);
ylabel('cm', 'FontSize', 16);
grid on;



%GRAFICO GIROSCOPIO
figure(2)
axis(1) = subplot(3,1,1);
plot(tempo_ABS,gyroX_ABS)
title('gyroX', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
axis(2) = subplot(3,1,2);
plot(tempo_ABS,gyroY_ABS)
title('gyroY', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
axis(3) = subplot(3,1,3);
plot(tempo_ABS,gyroZ_ABS)
title('gyroZ', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);

%GRAFICO ACCELERAZIONI
figure(3)
axis(1) = subplot(3,1,1);
plot(tempo_ABS,AccX_ABS)
title('AccX', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);
axis(2) = subplot(3,1,2);
plot(tempo_ABS,AccY_ABS)
title('AccY', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);
axis(3) = subplot(3,1,3);
plot(tempo_ABS,AccZ_ABS)
title('AccZ', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);

%GRAFICO PWM-DISTANZA
figure(4)
plot(tempo_ABS,distanza_ABS,tempo_ABS,pwm_ABS)
title('pwm-distnza nel tempo', 'FontSize', 18);
legend('Distanza', 'PWM', 'fontSize', 14);







