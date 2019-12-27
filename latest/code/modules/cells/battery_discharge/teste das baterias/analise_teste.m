clc
clear
close all

%{
    TESTE DE DESCARGA 
%}

%% 
%IMPORTANDO O LOG DE TENSAO 

Bat_voltages = importdata('teste_baterias_log.txt');

%% CONFORMANDO DADOS

t_total_sec = linspace(1,132480, 132480); % Duracao total do teste (em segundos)
t_total_hour = t_total_sec./3600; 

%% RETIRANDO PARTES INDESEJADAS DOS DADOS

n = find(Bat_voltages < 5); % encontrando local onde ha inconsistencia
n = n(1) - 200; % subtraio 200 amostras 
t_amostras_sec = linspace(1,1.46*n, n);
t_amostras_sec = t_amostras_sec';
batvoltage = Bat_voltages(1: n);

%% FITTING A CURVA DE TENSÃO POLINOMIALMENTE

V_coef = polyfit(t_amostras_sec,batvoltage, 5); % usando polyfit para pegar os coeficientes do polinomio que aproxima a curva de dados
Voltage_fitted = polyval(V_coef, t_total_sec); % Usando os coeficientes obtidos para gerar novos dados

%% ANALISE DE CARGA

Resistencia = 9.40; %Valor da resistência utilizada durante o teste
Current_fitted = Voltage_fitted./Resistencia; % Tranformando a curva de tensao em curva de corrente
Charge = trapz(t_total_hour, Current_fitted); % calculando a carga em Ah através da integral da curva (metodo do trapezio)

%% ENALISE DE ENERGIA

Power = Voltage_fitted .* Current_fitted; % Utilizando os dados de correnten e tensao para saber o valor da potencia (sempre instantanea)
Energy = trapz(t_total_hour, Power); % Integral da potencia no tempo para obter energia em Wh

%% PLOTS

figure (1)

plot(t_amostras_sec,batvoltage);
hold on
plot(t_total_sec, Voltage_fitted);
title('Curva obtida - Original e Curva Ajustada');
xlabel('Tempo (sec)');
ylabel('Tensao (V)');
legend('Curva Original','Curva Ajustada');
hold off

figure (2)
subplot(2,1,1);
plot (t_total_hour,Voltage_fitted, 'g');
title('Curvas de Corrente, Tensao');
xlabel('Tempo (hours)');
ylabel('Tensao na carga');

subplot(2,1,2);

plot(t_total_hour,Current_fitted, 'b');
xlabel('Tempo (hours)');
ylabel('Tensao Amplitude');
title('Corrente Drenada');
hold off

figure(3)

plot(t_total_hour, Power, 'r');
xlabel('Tempo (hours)');
ylabel('Potencia (W)');
title('Potencia na Carga');
hold off
