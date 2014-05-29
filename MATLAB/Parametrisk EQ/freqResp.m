function freqResp(H1,H2,H3,Hi,Lo,fs)  %( b,a,fs)
%FREQRESP Summary of this function goes here
%   Detailed explanation goes here

% T = 1/fs;% sampling interval in seconds
% w = linspace(0,pi/T); % radian frequency
% 
% %As always, radian frequency $ \omega$ is related to frequency $ f$ in Hz by the relation $ \omega=2\pi f$ . Also as always in this book, the sampling rate is denoted by $ f_s=1/T$ . Since the frequency axis for digital signals goes from $ -f_s/2$ to $ f_s/2$ (non-inclusive), we have $ \omega T\in[-\pi,\pi)$ , where $ [\;)$ denotes a half-open interval. Since the frequency $ f=\pm f_s/2$ is usually rejected in applications, it is more practical to take $ \omega T\in(-\pi,\pi)$ . 
% 
% x=exp(-1i.*w.*T);
% num = b(1) + b(2).*x + b(3).*x.*x;
% den = a(1) + a(2).*x + a(3).*x.*x;
% 
% H=abs(num./den);
% plot(w,H)

Hcas=dfilt.cascade(Lo,H1,H2,H3,Hi);

%[h1,f1]=freqz(H1,[],fs);
%[h2,f3]=freqz(H2,[],fs);
%[h3,f2]=freqz(H3,[],fs);
[hcas,fcas]=freqz(Hcas,[],fs);

%plot(f1,20*log10(h1),f2,20*log10(h2),f3,20*log10(h3),fcas,20*log10(hcas))
%semilogx(fcas,20*log10(abs(hcas)))
plot(fcas,20*log10(abs(hcas)))
axis([0 fs/2 -15 15])
xlabel('Frequency [Hz]')
ylabel('Magnitude [dB]')

end

