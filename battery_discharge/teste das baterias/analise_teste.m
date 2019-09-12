clc
clear

%teste de baterias, analise dos dados

%importando o log das baterias

Bat_voltages = importdata('teste_baterias_log.txt');
t_amostras = linspace(1,length(Bat_voltages), length(Bat_voltages));

figure 
plot(t_amostras,Bat_voltages);
