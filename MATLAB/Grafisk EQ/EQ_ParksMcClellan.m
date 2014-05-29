%% EQ with ParksMcClellans method of designing fir filter.

clc
N = 127; %Filter length odd
fs = 44100; %Sample rate for wav

fref=200; %Hz
nr=6;
n=0:1:nr-1;
fc1=fref.*2.^n;
fc=2.*fc1./fs;


%f = [0 0.009 0.018 0.0186 0.0358 0.0368 0.07 0.11 0.14 0.20 0.23 1];
d = 0.015;

f = [0 fc(2)-d fc(2) fc(3)-d fc(3) fc(4)-d fc(4) fc(5)-d fc(5) fc(6)-d fc(6) 1];

a1=1;
a2=0;
a3=1;
a4=0;
a5=1;

a = [a1 a1 a2 a2 a3 a3 a4 a4 a5 a5 0 0];
aa = [a1 a2 a3 a4 a5 0];

b = firpm(N,f,a);

[h,w] = freqz(b,1,512);
figure (1)
freqz(b,1,512)
figure (2)
plot(fc,aa,'*',f,a,w/pi,abs(h))
%plot(fc*fs/2,aa,'*',f*fs/2,a,w*fs/(2*pi),abs(h))