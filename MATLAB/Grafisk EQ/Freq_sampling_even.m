%% Frequency sampling med jämt antal samplingspunkter
clear
N = 128; %Length of filter, even!
g = N/2; %Group delay
fs=44100; %Sample rate for wav

%Phase part
k=0:g-1;
phase = exp(-1i*pi*k);

%Frequency response
a = [1 0 2 0 1 0];
fref=200; %Hz
n=0:5; 
fc=fref.*2.^n;
fc=2.*fc./fs;

dF=1/N;
k=0:g-1;

A(1:g) = freq(dF*k,a,fc,g);

%plot(A,'*')

H = A.*phase;

for i=0:g-2
    %disp([num2str(N-i) num2str(i+2)])
    H(N-i) = conj(H(i+2));
end
H(g+1)=0;

% for i = 1:g+1
%     j=mod(N-i+1,N)+1;
%      if H(i) == conj(H(j))
%          disp('true')
%      else
%          disp('false')
%      end
% end

figure
h = ifft(H,N);
plot(abs(h))

fvtool(h,1)







