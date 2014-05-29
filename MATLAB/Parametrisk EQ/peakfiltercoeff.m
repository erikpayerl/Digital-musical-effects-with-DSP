function [ a,b ] = peakfiltercoeff( G, Q, fc, fs )
%PEAKFILTERCOEFF Cofficients for second order peak IRR filter, Canonical form
%       
%   Syntax:
%     [ a,b ] = peakfiltercoeff( G, Q, fc, fs )
% 
%   Description:
%     IRR peak filter described by numerator coefficient vector b and 
%     denominator coefficient vector a. Peak filters boost or cut 
%     mid-frequency bands with parameters center frequency fc, Q factor, 
%     and gain G. The Q factor is defined by the ratio of the bandwidth 
%     to center frequency Q = fb/fc. fs i sampling frequency.
%
%     max(abs(a))<V0 and max(abs(b))<V0
%     G < 12 -> V0 < 4 -> a and b can be stored in Q2.13 format

K = tan(pi*fc/fs);  % tan(x) divergerar för pi/2, dvs då fc=fs/2, 0<K<6.8 då  0<fc<20000
V0 = 10^(G/20);     % -9 < G < 9 -> 0.34 < V0 < 2.82
V_0 = 1/V0;
K2=K*K;
KQ=K/Q;

if G >= 0
    den = 1/((1+KQ+K2));
    b = [(1+V0*KQ+K2) * den, 2*(K2-1) * den, (1-V0*KQ+K2) * den];
    a = [1, b(2), (1-KQ+K2) * den];
else
    den = 1/(1+V_0*KQ+K2);
    b = [(1+KQ+K2) * den, 2*(K2-1) * den, (1-KQ+K2) * den];
    a = [1, b(2), (1-V_0*KQ+K2) * den];
end

% disp('Peakfilter coefficients')
% disp(['K = ' num2str(K) ';    K2 = ' num2str(K2) ';    K/Q = ' num2str(KQ) ';    V0 = ' num2str(V0) ';    1/V0 = ' num2str(V_0)])
% disp(['b1 = ' num2str(b(1)) ';    b2 = ' num2str(b(2)) ';    b3 = ' num2str(b(3))])
% disp(['a1 = ' num2str(a(2)) ';    a2 = ' num2str(a(3))])

%Fixed point conversion -> Q2.13
% a = sfi(a,16,13);
% b = sfi(b,16,13);
end

