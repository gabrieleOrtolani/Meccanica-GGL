%Media ABS:
clc
close all
clear all

ABS_1= importdata("./ABS_r/dati1_abs.txt");
ABS_2= importdata("./ABS_r/dati2_abs.txt");
ABS_3= importdata("./ABS_r/dati3_abs.txt");
ABS_4= importdata("./ABS_r/dati4_abs.txt");
ABS_5= importdata("./ABS_r/dati5_abs.txt");

ABS_1(:,8) = ABS_1(:,8) - ABS_1(1,8);
ABS_2(:,8) = ABS_2(:,8) - ABS_2(1,8);
ABS_3(:,8) = ABS_3(:,8) - ABS_3(1,8);
ABS_4(:,8) = ABS_4(:,8) - ABS_4(1,8);
ABS_5(:,8) = ABS_5(:,8) - ABS_5(1,8);

figure(1)
axis(1) = subplot(2,1,1);
title('Distanza ABS')
hold on

plot(ABS_1(:,8),ABS_1(:,7));
plot(ABS_2(:,8),ABS_2(:,7));
plot(ABS_3(:,8),ABS_3(:,7));
plot(ABS_4(:,8),ABS_4(:,7));
plot(ABS_5(:,8),ABS_5(:,7));
legend('ABS_1','ABS_2','ABS_3','ABS_4', 'ABS_5')
hold off
ABS_media = (ABS_1+ ABS_2+ABS_3+ ABS_4+ABS_5)/5;

figure(2)
axis(2) = subplot(2,1,1);
title('Distanza ABS media')

plot(ABS_media(:,8),ABS_media(:,7));
legend('ABS Distanza Media')


% Media STOP:

STOP_1= importdata("./STOP_r/dati1_stop.txt");
STOP_2= importdata("./STOP_r/dati2_stop.txt");
STOP_3= importdata("./STOP_r/dati3_stop.txt");
STOP_4= importdata("./STOP_r/dati4_stop.txt");
STOP_5= importdata("./STOP_r/dati5_stop.txt");

STOP_1(:,8) = STOP_1(:,8) - STOP_1(1,8);
STOP_2(:,8) = STOP_2(:,8) - STOP_2(1,8);
STOP_3(:,8) = STOP_3(:,8) - STOP_3(1,8);
STOP_4(:,8) = STOP_4(:,8) - STOP_4(1,8);
STOP_5(:,8) = STOP_5(:,8) - STOP_5(1,8);


figure(1)
axis(2) = subplot(2,1,2);
title('Distanza Stop')
hold on 
plot(STOP_1(:,8),STOP_1(:,7));
plot(STOP_2(:,8),STOP_2(:,7));
plot(STOP_3(:,8),STOP_3(:,7));
plot(STOP_4(:,8),STOP_4(:,7));
plot(STOP_5(:,8),STOP_5(:,7));
legend('STOP_1','STOP_2','STOP_3','STOP_4', 'STOP_5')
hold off

STOP_media = (STOP_1+ STOP_2+STOP_3+ STOP_4+STOP_5)/5;

figure(2)
axis(1) = subplot(2,1,2);
title('STOP distanza media')
plot(STOP_media(:,8),STOP_media(:,7));
legend('STOP Distanza Media')

%% Accelerazione

%Accelerazione Stop
figure(3)
axis(3) = subplot(3,2,1);
title('Accelerazione Stop X');
hold on 
plot(STOP_1(:,8),STOP_1(:,1));
plot(STOP_2(:,8),STOP_2(:,1));
plot(STOP_3(:,8),STOP_3(:,1));
plot(STOP_4(:,8),STOP_4(:,1));
plot(STOP_5(:,8),STOP_5(:,1));
legend('AccX_1','AccX_2','AccX_3','AccX_4', 'AccX_5')
hold off

axis(3) = subplot(3,2,3);
title('Accelerazione Stop Y')
hold on 
plot(STOP_1(:,8),STOP_1(:,2));
plot(STOP_2(:,8),STOP_2(:,2));
plot(STOP_3(:,8),STOP_3(:,2));
plot(STOP_4(:,8),STOP_4(:,2));
plot(STOP_5(:,8),STOP_5(:,2));
legend('AccY_1','AccY_2','AccY_3','AccY_4', 'AccY_5')
hold off

axis(3) = subplot(3,2,5);
title('Accelerazione Stop Z')
hold on 
plot(STOP_1(:,8),STOP_1(:,3));
plot(STOP_2(:,8),STOP_2(:,3));
plot(STOP_3(:,8),STOP_3(:,3));
plot(STOP_4(:,8),STOP_4(:,3));
plot(STOP_5(:,8),STOP_5(:,3));
legend('AccZ_1','AccZ_2','AccZ_3','AccZ_4', 'AccZ_5')
hold off

% Accelerazione stop media
figure(4)
axis(4) = subplot(3,2,1);
plot(STOP_media(:,8),STOP_media(:,1));
legend('Accelerazione media X STOP')

axis(4) = subplot(3,2,3);
plot(STOP_media(:,8),STOP_media(:,2));
legend('Accelerazione media Y STOP')

axis(4) = subplot(3,2,5);
plot(STOP_media(:,8),STOP_media(:,3));
legend('Accelerazione media Z STOP')


% Accelerazione ABS
figure(3)
axis(3) = subplot(3,2,2);
title('Accelerazione ABS X')
hold on 
plot(ABS_1(:,8),ABS_1(:,1));
plot(ABS_2(:,8),ABS_2(:,1));
plot(ABS_3(:,8),ABS_3(:,1));
plot(ABS_4(:,8),ABS_4(:,1));
plot(ABS_5(:,8),ABS_5(:,1));
legend('AccX_1','AccX_2','AccX_3','AccX_4', 'AccX_5')
hold off

axis(3) = subplot(3,2,4);
title('Accelerazione ABS Y')
hold on 
plot(ABS_1(:,8),ABS_1(:,2));
plot(ABS_2(:,8),ABS_2(:,2));
plot(ABS_3(:,8),ABS_3(:,2));
plot(ABS_4(:,8),ABS_4(:,2));
plot(ABS_5(:,8),ABS_5(:,2));
legend('AccY_1','AccY_2','AccY_3','AccY_4', 'AccY_5')
hold off

axis(3) = subplot(3,2,6);
title('Accelerazione ABS Z')
hold on 
plot(ABS_1(:,8),ABS_1(:,3));
plot(ABS_2(:,8),ABS_2(:,3));
plot(ABS_3(:,8),ABS_3(:,3));
plot(ABS_4(:,8),ABS_4(:,3));
plot(ABS_5(:,8),ABS_5(:,3));
legend('AccZ_1','AccZ_2','AccZ_3','AccZ_4', 'AccZ_5')
hold off

% Accelerazione abs media
figure(4)
axis(4) = subplot(3,2,2);
plot(ABS_media(:,8),ABS_media(:,1));
legend('Accelerazione media X ABS')

axis(4) = subplot(3,2,4);
plot(ABS_media(:,8),ABS_media(:,2));
legend('Accelerazione media Y ABS')

axis(4) = subplot(3,2,6);
plot(ABS_media(:,8),ABS_media(:,3));
legend('Accelerazione media Z ABS')

%% Giroscopio

%Giroscopio Stop
figure(5)
axis(5) = subplot(3,2,1);
title('Giroscopio Stop X');
hold on 
plot(STOP_1(:,8),STOP_1(:,4));
plot(STOP_2(:,8),STOP_2(:,4));
plot(STOP_3(:,8),STOP_3(:,4));
plot(STOP_4(:,8),STOP_4(:,4));
plot(STOP_5(:,8),STOP_5(:,4));
legend('GyrX_1','GyrX_2','GyrX_3','GyrX_4', 'GyrX_5')
hold off

axis(5) = subplot(3,2,3);
title('Giroscopio Stop Y')
hold on 
plot(STOP_1(:,8),STOP_1(:,5));
plot(STOP_2(:,8),STOP_2(:,5));
plot(STOP_3(:,8),STOP_3(:,5));
plot(STOP_4(:,8),STOP_4(:,5));
plot(STOP_5(:,8),STOP_5(:,5));
legend('GyrY_1','GyrY_2','GyrY_3','GyrY_4', 'GyrY_5')
hold off

axis(5) = subplot(3,2,5);
title('Giroscopio Stop Z')
hold on 
plot(STOP_1(:,8),STOP_1(:,6));
plot(STOP_2(:,8),STOP_2(:,6));
plot(STOP_3(:,8),STOP_3(:,6));
plot(STOP_4(:,8),STOP_4(:,6));
plot(STOP_5(:,8),STOP_5(:,6));
legend('GyrZ_1','GyrZ_2','GyrZ_3','GyrZ_4', 'GyrZ_5')
hold off

% Accelerazione stop media
figure(6)
axis(6) = subplot(3,2,1);
plot(STOP_media(:,8),STOP_media(:,4));
legend('Giroscopio media X STOP')

axis(6) = subplot(3,2,3);
plot(STOP_media(:,8),STOP_media(:,5));
legend('Giroscopio media Y STOP')

axis(6) = subplot(3,2,5);
plot(STOP_media(:,8),STOP_media(:,6));
legend('Giroscopio media Z STOP')


% Accelerazione ABS
figure(5)
axis(5) = subplot(3,2,2);
title('Giroscopio ABS X')
hold on 
plot(ABS_1(:,8),ABS_1(:,4));
plot(ABS_2(:,8),ABS_2(:,4));
plot(ABS_3(:,8),ABS_3(:,4));
plot(ABS_4(:,8),ABS_4(:,4));
plot(ABS_5(:,8),ABS_5(:,4));
legend('GyrX_1','GyrX_2','GyrX_3','GyrX_4', 'GyrX_5')
hold off

axis(5) = subplot(3,2,4);
title('Giroscopio ABS Y')
hold on 
plot(ABS_1(:,8),ABS_1(:,5));
plot(ABS_2(:,8),ABS_2(:,5));
plot(ABS_3(:,8),ABS_3(:,5));
plot(ABS_4(:,8),ABS_4(:,5));
plot(ABS_5(:,8),ABS_5(:,5));
legend('GyrY_1','GyrY_2','GyrY_3','GyrY_4', 'GyrY_5')
hold off

axis(5) = subplot(3,2,6);
title('Giroscopio ABS Z')
hold on 
plot(ABS_1(:,8),ABS_1(:,6));
plot(ABS_2(:,8),ABS_2(:,6));
plot(ABS_3(:,8),ABS_3(:,6));
plot(ABS_4(:,8),ABS_4(:,6));
plot(ABS_5(:,8),ABS_5(:,6));
legend('GyrZ_1','GyrZ_2','GyrZ_3','GyrZ_4', 'GyrZ_5')
hold off

% Accelerazione abs media
figure(6)
axis(6) = subplot(3,2,2);
plot(ABS_media(:,8),ABS_media(:,4));
legend('Giroscopio media X ABS')

axis(6) = subplot(3,2,4);
plot(ABS_media(:,8),ABS_media(:,5));
legend('Giroscopio media Y ABS')

axis(6) = subplot(3,2,6);
plot(ABS_media(:,8),ABS_media(:,6));
legend('Giroscopio media Z ABS')



