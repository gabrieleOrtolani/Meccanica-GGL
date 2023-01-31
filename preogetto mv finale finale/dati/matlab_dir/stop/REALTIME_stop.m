clc
close all
clear all

% import from file to array
STOP = importdata("dati.txt");


%tempo di campionamento ABS
tempo_STOP= STOP(:,8)*0.001;
%giroscopio ABS 
gyroX_STOP = STOP(:, 4)/131.0;% [°] unit
gyroY_STOP= STOP(:, 5)/131.0;% [°] unit
gyroZ_STOP = STOP(:, 6)/131.0;% [°] unit
%accelerazioni ABS 
AccX_STOP = STOP(:, 1)/16384.0;% [g] unit
AccY_STOP = STOP(:, 2)/16384.0;% [g] unit
AccZ_STOP = STOP(:, 3)/16384.0;% [g] unit
%spazio (distanza) ABS 
distanza_STOP = STOP(:,9);
pwm_STOP = STOP(:,7);




%GRAFICO SPAZIO-TEMPO
figure(1)
plot(tempo_STOP,distanza_STOP);
xlabel('t [sec]', 'FontSize', 16);
ylabel('cm', 'FontSize', 16);
grid on;



%GRAFICO GIROSCOPIO
figure(2)
axis(1) = subplot(3,1,1);
plot(tempo_STOP,gyroX_STOP)
title('gyroX', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
axis(2) = subplot(3,1,2);
plot(tempo_STOP,gyroY_STOP)
title('gyroY', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);
axis(3) = subplot(3,1,3);
plot(tempo_STOP,gyroZ_STOP)
title('gyroZ', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('°/s', 'FontSize', 16);

%GRAFICO ACCELERAZIONI
figure(3)
axis(1) = subplot(3,1,1);
plot(tempo_STOP,AccX_STOP)
title('AccX', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);
axis(2) = subplot(3,1,2);
plot(tempo_STOP,AccY_STOP)
title('AccY', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);
axis(3) = subplot(3,1,3);
plot(tempo_STOP,AccZ_STOP)
title('AccZ', 'FontSize', 18);
xlabel('t [sec]', 'FontSize', 16);
ylabel('g', 'FontSize', 16);

%GRAFICO PWM-DISTANZA
figure(4)
plot(tempo_STOP,distanza_STOP,tempo_STOP,pwm_STOP)
title('pwm-distnza nel tempo', 'FontSize', 18);
legend('Distanza', 'PWM', 'fontSize', 14);







