%% EQ designad med Frequency sampling method
clc
clear all
rounding = @round;

N = 512; %Length of filter, even!
g = N/2; %Group delay
fs=48000; %Sample rate for wav

%Phase part
k=0:g-1;
%phase = exp(-1i*pi*k); %varrannan är negativ! 1 -1 1 -1 1 -1 ...
phase = zeros(1,g);
for i=1:g/2
    phase(2*i-1)=1;
    phase(2*i)=-1;
end

for i=1:N
    Hamming(i) = 0.54 - 0.46 *cos(2*pi*i/N );
    Blackman(i) = 0.42 - 0.5 * cos(2*pi*i/N ) + 0.08 * cos(4*pi*i /N );
end

%Frequency response
% uint8 = 0 to 255
a(1) = 128;
a(2) = 128;
a(3) = 128;
a(4) = 0;
a(5) = 0;
a(6) = 0;
a(7) = 0;
a(8) = 128;

a = a*128;
fref=130; %Hz
n=0:6; 
fc=fref.*2.^n;
fc=fc./fs;

fc = int16(rounding(fc .* 2^15)); %Q15

A=zeros(1,g);

dF = int16(rounding(1/N .* 2^15)); %Q15
for i=1:g
    x=(i-1)*dF;
    if (x<fc(1))
        A(i)=a(1);
    elseif (x<fc(2))
        A(i)=a(2);
    elseif (x<fc(3))
        A(i)=a(3);
    elseif (x<fc(4))
        A(i)=a(4);
    elseif (x<fc(5))
        A(i)=a(5);
    elseif (x<fc(6))
        A(i)=a(6);
    elseif (x<fc(7))
        A(i)=a(7);
    elseif (x<11360) %13763
        A(i)=a(8);    
    else
        A(i)=0;
    end
end

%A -> Q15
%phase ->Q15
H = A.*phase;

for i=0:g-2
    %disp([num2str(N-i) num2str(i+2)])
    H(N-i) = (H(i+2));
end
H(g+1)=0; %Must be equal to zero for liner phase

H=(double(H).*2^-15);

Turkey=tukeywin(N,0.6)';

h = ifft(H,N);

h_tu=h.*Turkey;
fvtool(h,1,h_tu,1)