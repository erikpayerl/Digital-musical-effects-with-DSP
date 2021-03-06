%% J�mf�r av idealt frekvenssvar och det approximerade frekvenssvaret med eller utan f�nsterfunkton.
%  F�nster av typ Hamming och Blackman

% Rounding options
%   round(A) - rounds the elements of A to the nearest integers
%   fix(A) - rounds the elements of A toward zero
%   floor(A) - rounds the elements of A to the nearest integers less than or equal to A 
%   ceil(A) - rounds the elements of A to the nearest integers greater than or equal to A
rounding = @round;

%% Skapar idealt frekvenssvar
N = 4*2048; %Length of filter, even!
g = N/2; %Group delay
fs=48000; %Sample rate for wav

%Phase part
k=0:g-1;
phase = zeros(1,g);
for i=1:g/2
    phase(2*i-1)=1;
    phase(2*i)=-1;
end

%Frequency response
% uint8 = 0 to 255
a = [100 200 50 255 200 150 100];
a = a*128;
fref=150; %Hz
n=0:5; 
fc=fref.*2.^n
fc=fc./fs
fc = int16(rounding(fc .* 2^15)); %Q15

A=zeros(1,g);

dF = int16(rounding(1/N .* 2^15)); %Q15
c=0;
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
    elseif (x<13763)
        A(i)=a(7);
    else
        A(i)=0;
        c=c+1;
    end
end

f=linspace(0,fs/2,N/2);

%% Frekvenssvar ber�knade p� DSPn

%Blackman
Hblack=[0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 2, 1, 2, 1, 1, 2, 2, 3, 2, 3, 3, 2, 3, 2, 4, 2, 3, 3, 2, 3, 0, 2, -1, 0, 0, -1, 2, -1, 2, 1, 0, 2, -2, 2, -2, 1, 2, 0, 3, -3, 1, -4, -3, -2, -6, 2, -4, 3, 1, 0, 3, -4, 3, -4, 2, 2, -1, 7, -3, 5, -5, -4, -3, -11, 2, -7, 5, 3, 3, 11, -1, 13, 0, 10, 11, 8, 23, 8, 23, 9, 9, 11, -5, 13, -5, 14, 9, 8, 20, -3, 16, -8, 1, -3, -14, 6, -21, 0, -25, -30, -33, -66, -45, -80, -58, -68, -71, -51, -85, -55, -92, -79, -84, -101, -66, -102, -61, -89, -87, -82, -126, -90, -142, -104, -115, -113, -71, -112, -55, -102, -78, -80, -106, -49, -100, -31, -61, -48, -31, -93, -37, -116, -66, -83, -81, -12, -64, 33, -25, 19, 23, -15, 75, 1, 113, 81, 117, 163, 83, 176, 55, 124, 89, 77, 177, 90, 240, 150, 213, 209, 124, 237, 88, 232, 156, 188, 249, 100, 230, 2, 68, -41, -121, -5, -197, 30, -138, -43, -51, -217, -34, -327, -87, -230, -164, -5, -240, 81, -317, -143, -342, -520, -259, -690, -128, -466, -144, -40, -411, 208, -677, 113, -402, -148, 744, -300, 2403, -278, 3637, 12564, 3637, -277, 2401, -300, 744, -148, -401, 113, -675, 209, -410, -40, -144, -463, -127, -687, -258, -518, -340, -143, -314, 80, -239, -5, -163, -229, -86, -324, -33, -214, -50, -43, -136, 30, -194, -5, -120, -41, 67, 2, 228, 99, 246, 186, 155, 230, 87, 235, 124, 206, 209, 148, 238, 89, 175, 76, 88, 123, 54, 173, 81, 160, 115, 80, 111, 1, 74, -15, 23, 18, -25, 33, -63, -11, -79, -81, -65, -114, -37, -90, -31, -47, -60, -30, -98, -47, -104, -78, -76, -100, -54, -109, -69, -110, -111, -102, -138, -89, -123, -79, -84, -86, -59, -99, -64, -98, -81, -77, -89, -53, -83, -49, -69, -66, -56, -78, -43, -63, -32, -29, -24, 0, -21, 6, -14, -3, 1, -8, 16, -2, 20, 8, 9, 13, -5, 13, -5, 11, 9, 9, 22, 8, 22, 8, 11, 9, 0, 12, -1, 11, 3, 3, 5, -7, 2, -10, -3, -4, -4, 4, -3, 7, -1, 2, 2, -4, 3, -4, 3, 0, 1, 3, -4, 2, -6, -2, -3, -4, 1, -3, 3, 0, 1, 1, -2, 2, -2, 2, 0, 1, 2, -1, 2, -1, 0, 0, -1, 2, 0, 3, 2, 3, 3, 2, 3, 1, 3, 2, 2, 3, 2, 3, 1, 2, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0];
Hblack = double(Hblack)*2^-15;
[hblack, f] =freqz(Hblack,1,N/2,fs);

%Hamming
Hhamm= [-8, -4, -7, -5, -3, -5, -1, -6, -2, -5, -5, -3, -5, -1, -4, -1, -2, -5, -2, -7, -2, -5, -2, 1, -1, 5, 1, 5, 3, 3, 7, 3, 11, 7, 11, 11, 9, 13, 6, 11, 7, 10, 13, 10, 18, 11, 18, 14, 12, 16, 8, 17, 9, 15, 13, 9, 14, 1, 8, -2, 0, 2, -4, 8, -2, 8, 3, 1, 6, -6, 7, -4, 5, 5, 0, 10, -6, 4, -9, -8, -4, -14, 5, -9, 8, 2, 0, 9, -9, 8, -8, 4, 5, -1, 16, -6, 10, -9, -8, -6, -21, 4, -14, 10, 6, 7, 21, -2, 24, 1, 18, 21, 14, 42, 14, 41, 16, 16, 19, -8, 23, -8, 23, 15, 14, 33, -4, 27, -13, 1, -4, -22, 10, -32, 0, -38, -44, -49, -96, -66, -116, -83, -97, -101, -72, -119, -76, -127, -109, -114, -137, -89, -137, -82, -118, -114, -107, -164, -117, -183, -134, -147, -144, -90, -141, -68, -127, -97, -99, -130, -60, -121, -37, -74, -57, -37, -110, -44, -136, -77, -97, -93, -14, -74, 38, -29, 21, 27, -17, 84, 1, 127, 91, 130, 180, 91, 193, 60, 136, 97, 84, 192, 97, 259, 161, 228, 223, 132, 252, 93, 245, 165, 197, 261, 105, 241, 2, 71, -42, -126, -5, -203, 31, -142, -44, -52, -222, -35, -334, -88, -234, -166, -5, -243, 82, -320, -145, -345, -524, -261, -694, -129, -468, -145, -40, -412, 209, -678, 113, -402, -148, 744, -300, 2403, -278, 3637, 12564, 3637, -277, 2402, -300, 745, -148, -402, 113, -677, 210, -411, -40, -145, -466, -128, -693, -261, -523, -344, -144, -318, 81, -243, -5, -166, -234, -88, -332, -33, -220, -52, -44, -141, 31, -201, -5, -125, -42, 70, 2, 239, 104, 259, 196, 164, 244, 93, 250, 132, 221, 225, 160, 258, 97, 190, 83, 96, 135, 59, 192, 90, 179, 128, 90, 126, 1, 84, -17, 26, 21, -29, 38, -73, -13, -92, -95, -76, -135, -43, -108, -37, -57, -73, -37, -120, -58, -128, -97, -95, -125, -68, -139, -88, -141, -144, -132, -180, -116, -162, -105, -112, -116, -80, -135, -87, -135, -112, -107, -125, -75, -117, -70, -99, -96, -81, -114, -64, -94, -47, -43, -37, 0, -31, 10, -21, -4, 1, -12, 26, -4, 33, 13, 15, 23, -7, 22, -8, 19, 16, 16, 40, 15, 41, 14, 21, 18, 1, 24, -2, 21, 6, 6, 10, -13, 4, -20, -5, -8, -9, 10, -6, 16, -1, 5, 4, -8, 8, -9, 9, 0, 2, 8, -8, 5, -13, -4, -7, -9, 4, -6, 10, 0, 5, 5, -4, 6, -6, 6, 1, 3, 8, -1, 8, -3, 2, 0, -2, 8, 1, 13, 9, 13, 14, 9, 16, 8, 15, 12, 13, 17, 11, 17, 9, 12, 9, 7, 11, 5, 12, 8, 10, 11, 6, 10, 3, 7, 3, 3, 5, 1, 5, -1, 1, -2, -5, -2, -6, -2, -4, -2, -1, -4, -1, -5, -2, -5, -4, -2, -5, -1, -5, -3, -5, -7, -4];
Hhamm = double(Hhamm)*2^-15;
[hhamm, f] =freqz(Hhamm,1,N/2,fs);

%No window
H=[-99, -48, -76, -50, -32, -56, -9, -61, -24, -50, -50, -24, -58, -2, -41, -11, -21, -45, -15, -66, -16, -43, -15, 11, -4, 53, 11, 55, 35, 36, 66, 33, 94, 59, 96, 92, 72, 103, 46, 89, 53, 73, 92, 70, 125, 79, 118, 90, 80, 98, 51, 101, 56, 86, 77, 50, 76, 10, 43, -6, 2, 13, -15, 41, -5, 40, 15, 6, 27, -24, 29, -15, 21, 22, 2, 40, -22, 17, -31, -25, -13, -45, 17, -27, 26, 8, 2, 28, -27, 27, -22, 13, 16, -2, 45, -16, 29, -23, -21, -13, -52, 12, -34, 27, 15, 17, 52, -3, 56, 3, 42, 48, 32, 92, 32, 88, 35, 35, 39, -15, 46, -14, 46, 30, 27, 63, -6, 50, -22, 3, -6, -38, 18, -55, 0, -64, -74, -81, -159, -107, -188, -134, -155, -160, -112, -185, -117, -194, -165, -172, -205, -131, -201, -119, -170, -164, -152, -232, -164, -255, -185, -201, -196, -121, -189, -91, -168, -127, -129, -169, -77, -155, -47, -93, -72, -46, -137, -54, -168, -94, -118, -113, -16, -88, 46, -34, 26, 32, -19, 99, 2, 147, 105, 149, 206, 104, 219, 68, 153, 109, 94, 213, 108, 285, 177, 249, 243, 144, 273, 101, 264, 177, 211, 278, 112, 255, 3, 75, -44, -131, -5, -211, 33, -147, -45, -53, -228, -35, -342, -90, -239, -169, -5, -247, 84, -324, -146, -348, -529, -263, -699, -129, -470, -145, -40, -413, 210, -679, 114, -402, -148, 745, -300, 2404, -278, 3638, 12565, 3638, -277, 2404, -300, 746, -148, -402, 114, -679, 211, -413, -40, -145, -469, -129, -699, -263, -529, -348, -146, -323, 83, -247, -5, -169, -239, -90, -341, -34, -227, -53, -45, -146, 33, -210, -5, -131, -44, 75, 3, 255, 112, 278, 211, 177, 264, 101, 273, 145, 243, 248, 177, 286, 108, 213, 94, 109, 153, 68, 219, 104, 206, 149, 105, 147, 2, 99, -20, 32, 26, -34, 47, -88, -15, -113, -117, -94, -168, -54, -136, -46, -72, -93, -47, -156, -76, -169, -128, -126, -168, -91, -189, -121, -195, -200, -185, -254, -165, -232, -152, -163, -170, -118, -201, -130, -205, -171, -165, -194, -117, -185, -112, -159, -155, -133, -188, -106, -158, -80, -74, -63, 1, -55, 19, -38, -6, 3, -22, 50, -6, 64, 27, 30, 46, -14, 46, -15, 40, 35, 36, 88, 33, 92, 33, 48, 42, 4, 57, -3, 53, 17, 16, 27, -33, 12, -52, -12, -20, -23, 29, -16, 46, -1, 16, 14, -22, 26, -27, 29, 3, 9, 27, -26, 18, -45, -13, -25, -31, 18, -22, 41, 2, 22, 22, -15, 29, -23, 28, 6, 15, 40, -4, 42, -14, 15, 3, -6, 43, 10, 77, 51, 77, 87, 57, 102, 51, 99, 81, 91, 119, 80, 126, 71, 93, 73, 54, 89, 47, 103, 72, 92, 97, 60, 94, 34, 67, 36, 35, 56, 12, 53, -4, 12, -14, -43, -16, -65, -14, -44, -21, -10, -41, -2, -58, -22, -50, -48, -24, -59, -8, -55, -32, -50, -76, -48];
H = double(H)*2^-15;
[h, f] =freqz(H,1,N/2,fs);

clear fig
plot(f,abs(hblack), 'LineWidth',1)
hold all
plot(f,abs(hhamm), 'LineWidth',1)
plot(f,abs(h), 'LineWidth',1)
plot(f,A/32767, 'LineWidth',2);
axis([0 6000 0 1.2])
xlabel('Frekvens')
ylabel('Magnitud')
title('Frekvenssvar: Grafisk EQ','FontWeight','bold')


