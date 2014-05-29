function [a, b] = shelvingcoeff(fs, fc, G, HPLP)
% [a, b] = shelvingcoeff(fs, fc, G, HPLP)
%returns filter coefficients b0,b1,b2 in the vector b and a0,a1,a2 in vector a.
%fs is sampling freq
%fc is filter cut off freq
%G is boost/cut
%HPLP chooses low freq or high freq. 0 = low freq, 1 = high freq

V0 = 10^(G/20);
K = tan((pi*fc)/fs);

if G>=0 && HPLP == 0                %LF and boost
    b = [(1+sqrt(2*V0)*K+V0*K^2)/(1+sqrt(2)*K+K^2) (2*(V0*K^2-1))/(1+sqrt(2)*K+K^2) (1-sqrt(2*V0)*K+V0*K^2)/(1+sqrt(2)*K+K^2)];
    a = [1 (2*(K^2-1))/(1+sqrt(2)*K+K^2) (1-sqrt(2)*K+K^2)/(1+sqrt(2)*K+K^2)];
elseif G<0 && HPLP == 0             %LF and cut
    b = [(V0*(1+sqrt(2)*K+K^2))/(V0+sqrt(2*V0)*K+K^2) (2*V0*(K^2-1))/(V0+sqrt(2*V0)*K+K^2) (V0*(1-sqrt(2)*K+K^2))/(V0+sqrt(2*V0)*K+K^2)];
    a = [1 (2*(K^2-V0))/(V0+sqrt(2*V0)*K+K^2) (V0-sqrt(2*V0)*K+K^2)/(V0+sqrt(2*V0)*K+K^2)];
elseif G>=0 && HPLP == 1            %HF and boost
    b = [(V0+sqrt(2*V0)*K+K^2)/(1+sqrt(2)*K+K^2) (2*(K^2-V0))/(1+sqrt(2)*K+K^2) (V0-sqrt(2*V0)*K+K^2)/(1+sqrt(2)*K+K^2)];
    a = [1 (2*(K^2-1))/(1+sqrt(2)*K+K^2) (1-sqrt(2)*K+K^2)/(1+sqrt(2)*K+K^2)];
elseif G<0 && HPLP == 1             %HF and cut
    b = [(V0*(1+sqrt(2)*K+K^2))/(1+sqrt(2*V0)*K+V0*K^2) (2*V0*(K^2-1))/(1+sqrt(2*V0)*K+V0*K^2) (V0*(1-sqrt(2)*K+K^2))/(1+sqrt(2*V0)*K+V0*K^2)];
    a = [1 (2*(V0*K^2-1))/(1+sqrt(2*V0)*K+V0*K^2) (1-sqrt(2*V0)*K+V0*K^2)/(1+sqrt(2*V0)*K+V0*K^2)];
end

end