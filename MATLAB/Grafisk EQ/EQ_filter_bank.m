%%Exempel på grafisk Equlizer med 3 band konstruerad med en filterbank.
Fc    = [0.0027,    0.0054,    0.0108,    0.0217,    0.0433,    0.0867,    0.1733];

N = 2000;  
Hf = fdesign.lowpass('N,Fc',N,Fc(1));
Hd1 = design(Hf,'window','window',@hamming,'SystemObject',true);
 
Hf = fdesign.bandpass('N,Fc1,Fc2',N,Fc(1),Fc(2));
Hd2 = design(Hf,'window','window',@hamming,'SystemObject',true);
 
Hf = fdesign.highpass('N,Fc',N,Fc(2));
Hd3 = design(Hf,'window','window',@hamming,'SystemObject',true);

nr=5000;
x=linspace(0,1,nr).*24000;
h1 = freqz(Hd1,nr);
h2 = freqz(Hd2,nr);
h3 = freqz(Hd3,nr);

subplot(2,1,1); 
hold on
plot(x,abs(h1),'r', 'LineWidth',2);
plot(x,abs(h2),'g', 'LineWidth',2);
plot(x,abs(h3),'b', 'LineWidth',2);
axis([0 250 0 1.3])
xlabel('Frekvens [Hz]')
ylabel('Magnitud')
title('Frekvenssvar för individuella filter','FontWeight','bold')

s = coeffs(Hd1);
Hd1 = dfilt.dffir(s.Numerator);
s = coeffs(Hd2);
Hd2 = dfilt.dffir(s.Numerator);
s = coeffs(Hd3);
Hd3 = dfilt.dffir(s.Numerator);

Hpar = parallel(Hd1 ,Hd2, Hd3);  

[h,w] = freqz(Hpar,nr);

subplot(2,1,2);
hold on
plot(x,20*log10(abs(h)),'b', 'LineWidth',2);
axis([0 250 -3 5])
xlabel('Frekvens [Hz]')
ylabel('Magnitud (dB)')
title('Frekvenssvar för summa av filter','FontWeight','bold')
