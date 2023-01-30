
clc
close all
clear all

% import from file to array
mydata1 = importdata("datiABS_bellobello.txt");

%tempo di campionamento
tempo = mydata1(:,8)*0.001;
%giroscopio
gyroX = mydata1(:, 4);
gyroY = mydata1(:, 5);
gyroZ = mydata1(:, 6);
%accelerazioni
AccX=mydata1(:, 1);
AccY=mydata1(:, 2);
AccZ=mydata1(:, 3);
%spazio (distanza)
distanza=mydata1(:,7);
pwn=mydata1(:,9);

%-----
windowSize = 10;
b = (1/windowSize)*ones(1,windowSize);
a = 1;

dist_filtered=filter(b,a,distanza);

figure(1)
plot(tempo, gyroX,tempo,gyroY,tempo,gyroZ);
%hold on
%plot(tempo, filter(b,a,gyroX),tempo,filter(b,a,gyroY),tempo,filter(b,a,gyroZ));

figure(2)
plot(tempo, AccX,tempo,AccY,tempo,AccZ);

figure(3)
plot(tempo,distanza,tempo,dist_filtered);
figure(4)
plot(tempo,distanza,tempo,pwn)