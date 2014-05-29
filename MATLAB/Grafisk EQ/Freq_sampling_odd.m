%% Frequency sampling med udda antal samplingspunkter
clear
N = 255; %Length of filter, odd!
g = (N-1)/2; %Group delay
fs=44100; %Sample rate for wav

%Phase part
k=0:g;
phase = exp(-1i*g*2*pi/N*k);


%Frequency response
a = [1 0 1 0 1 0];
fref=200; %Hz
n=0:5; 
fc=fref.*2.^n
fc=2.*fc./fs;

dF=1/N;
k=0:g;

A(1:g+1) = freq(dF*k,a,fc,g+1);

plot(A,'*')

H = A.*phase;


for i=0:g-1
    H(N-i) = conj(H(i+2));
end

% for i = 1:g+1
%     j=mod(N-i+1,N)+1;
%  if H(i) == conj(H(j))
%      disp('true')
%  else
%      disp('false')
%  end
% end

%H(N+1)=0;
figure
NFFT = 2^nextpow2(N); % Next power of 2 from length of y
h = ifft(H,N);
plot(abs(h))

fvtool(h,1)







