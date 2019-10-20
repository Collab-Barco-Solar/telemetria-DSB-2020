clc
close all

adcID = fopen('adc.txt','r');
adc = fscanf(adcID,'%f');
fclose(adcID);

dacID = fopen('dac.txt','r');
dac = fscanf(dacID,'%f');
fclose(dacID);
[p,s] = polyfit(adc,dac,4);
figure
plot(adc,dac,'x');
