clc
close all
x = 1:542;1;
adcID = fopen('adc.txt','r');
adc = fscanf(adcID,'%f');
fclose(adcID);

dacID = fopen('dac.txt','r');
dac = fscanf(dacID,'%f');
fclose(dacID);

adc_fittedID = fopen('adc_fitted.txt','r');
adc_fitted = fscanf(adc_fittedID,'%f');
fclose(adc_fittedID);
figure
hold on

plot(x,dac, 'b');
plot(x,adc, 'r');
plot(x,adc_fitted, 'k');
legend('DAC output', 'ADC read', 'ADC fitted','location','SouthEast');