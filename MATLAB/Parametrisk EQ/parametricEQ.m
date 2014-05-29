function varargout = parametricEQ(varargin)
% PARAMETRICEQ MATLAB code for parametricEQ.fig
%      PARAMETRICEQ, by itself, creates a new PARAMETRICEQ or raises the existing
%      singleton*.
%
%      H = PARAMETRICEQ returns the handle to a new PARAMETRICEQ or the handle to
%      the existing singleton*.
%
%      PARAMETRICEQ('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PARAMETRICEQ.M with the given input arguments.
%
%      PARAMETRICEQ('Property','Value',...) creates a new PARAMETRICEQ or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before parametricEQ_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to parametricEQ_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help parametricEQ

% Last Modified by GUIDE v2.5 24-Feb-2014 22:25:21

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @parametricEQ_OpeningFcn, ...
                   'gui_OutputFcn',  @parametricEQ_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before parametricEQ is made visible.
function parametricEQ_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to parametricEQ (see VARARGIN)

handles.fs=44100; %Sample rate for wav
handles.time = 6; %Playtime in seconds
handles.samples = [1,handles.time*handles.fs];
handles.file = 'test.wav';

maxFreq = handles.fs/2;

%Set slider1 start values
Q1=1; % is Q factor 
Fc1 = 200; % is center frequency
G1 = -9; % is the gain in dB.

set(handles.sliderFc1, 'Min', 10);
set(handles.sliderFc1, 'Max', maxFreq);
set(handles.sliderFc1, 'Value', Fc1);
set(handles.sliderFc1, 'SliderStep', [2/maxFreq , 20/maxFreq ]);

set(handles.sliderQ1, 'Min', 0.1);
set(handles.sliderQ1, 'Max', 30);
set(handles.sliderQ1, 'Value', Q1);
set(handles.sliderQ1, 'SliderStep', [1/80 , 10/80 ]);

set(handles.sliderG1, 'Min', -15);
set(handles.sliderG1, 'Max', 15);
set(handles.sliderG1, 'Value', G1);
set(handles.sliderG1, 'SliderStep', [1/30 , 10/30 ]);

handles.G1=G1;
handles.Q1=Q1;
handles.Fc1=Fc1;

%Set slider2 start values
Q2=3; % is Q factor 
Fc2 = 1000; % is center frequency
G2 = 6; % is the gain in dB.

set(handles.sliderFc2, 'Min', 10);
set(handles.sliderFc2, 'Max', maxFreq);
set(handles.sliderFc2, 'Value', Fc2);
set(handles.sliderFc2, 'SliderStep', [2/maxFreq , 20/maxFreq ]);

set(handles.sliderQ2, 'Min', 0.1);
set(handles.sliderQ2, 'Max', 30);
set(handles.sliderQ2, 'Value', Q2);
set(handles.sliderQ2, 'SliderStep', [1/80 , 10/80 ]);

set(handles.sliderG2, 'Min', -15);
set(handles.sliderG2, 'Max', 15);
set(handles.sliderG2, 'Value', G2);
set(handles.sliderG2, 'SliderStep', [1/30 , 10/30 ]);

handles.G2=G2;
handles.Q2=Q2;
handles.Fc2=Fc2;

%Set slider3 start values
Q3=7; % is Q factor 
Fc3 = 5000; % is center frequency
G3 = -5; % is the gain in dB.

set(handles.sliderFc3, 'Min', 10);
set(handles.sliderFc3, 'Max', maxFreq);
set(handles.sliderFc3, 'Value', Fc3);
set(handles.sliderFc3, 'SliderStep', [2/maxFreq , 20/maxFreq ]);

set(handles.sliderQ3, 'Min', 0.1);
set(handles.sliderQ3, 'Max', 30);
set(handles.sliderQ3, 'Value', Q3);
set(handles.sliderQ3, 'SliderStep', [1/80 , 10/80 ]);

set(handles.sliderG3, 'Min', -15);
set(handles.sliderG3, 'Max', 15);
set(handles.sliderG3, 'Value', G3);
set(handles.sliderG3, 'SliderStep', [1/30 , 10/30 ]);

handles.G3=G3;
handles.Q3=Q3;
handles.Fc3=Fc3;

%Set sliderHi start values
FcHi = 8000; % is center frequency
GHi = 0; % is the gain in dB.

set(handles.sliderFcHi, 'Min', 10);
set(handles.sliderFcHi, 'Max', maxFreq);
set(handles.sliderFcHi, 'Value', FcHi);
set(handles.sliderFcHi, 'SliderStep', [2/maxFreq , 20/maxFreq ]);

set(handles.sliderGHi, 'Min', -15);
set(handles.sliderGHi, 'Max', 15);
set(handles.sliderGHi, 'Value', GHi);
set(handles.sliderGHi, 'SliderStep', [1/30 , 10/30 ]);

handles.GHi=GHi;
handles.FcHi=FcHi;

%Set sliderLo start values
FcLo = 100; % is center frequency
GLo = 0; % is the gain in dB.

set(handles.sliderFcLo, 'Min', 10);
set(handles.sliderFcLo, 'Max', maxFreq);
set(handles.sliderFcLo, 'Value', FcLo);
set(handles.sliderFcLo, 'SliderStep', [2/maxFreq , 20/maxFreq ]);

set(handles.sliderGLo, 'Min', -15);
set(handles.sliderGLo, 'Max', 15);
set(handles.sliderGLo, 'Value', GLo);
set(handles.sliderGLo, 'SliderStep', [1/30 , 10/30 ]);

handles.GLo=GLo;
handles.FcLo=FcLo;

%Textbox values
set(handles.editFc1, 'String', num2str(handles.Fc1)); 
set(handles.editFc2, 'String', num2str(handles.Fc2)); 
set(handles.editFc3, 'String', num2str(handles.Fc3)); 

set(handles.editG1, 'String', num2str(handles.G1));
set(handles.editG2, 'String', num2str(handles.G2));
set(handles.editG3, 'String', num2str(handles.G3)); 

set(handles.editQ1, 'String', num2str(handles.Q1));
set(handles.editQ2, 'String', num2str(handles.Q2));
set(handles.editQ3, 'String', num2str(handles.Q3));

set(handles.editFcHi, 'String', num2str(handles.FcHi));
set(handles.editFcLo, 'String', num2str(handles.FcLo));
set(handles.editGHi, 'String', num2str(handles.GHi));
set(handles.editGLo, 'String', num2str(handles.GLo));

%Get filter coefficients
[ handles.a1,handles.b1 ] = peakfiltercoeff( handles.G1, handles.Q1, handles.Fc1, handles.fs );
[ handles.a2,handles.b2 ] = peakfiltercoeff( handles.G2, handles.Q2, handles.Fc2, handles.fs );
[ handles.a3,handles.b3 ] = peakfiltercoeff( handles.G3, handles.Q3, handles.Fc3, handles.fs );

[ handles.aHi,handles.bHi ] = shelvingcoeff( handles.fs, handles.FcHi, handles.GHi, 1 );
[ handles.aLo,handles.bLo ] = shelvingcoeff( handles.fs, handles.FcLo, handles.GLo, 0 );

%Plot frequency response...
handles.H1=dfilt.df2t(handles.b1,handles.a1);
handles.H2=dfilt.df2t(handles.b2,handles.a2);
handles.H3=dfilt.df2t(handles.b3,handles.a3);
handles.Hi=dfilt.df2t(handles.bHi,handles.aHi);
handles.Lo=dfilt.df2t(handles.bLo,handles.aLo);

freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Choose default command line output for parametricEQ
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes parametricEQ wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = parametricEQ_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on slider movement.
function sliderQ3_Callback(hObject, eventdata, handles)
% hObject    handle to sliderQ3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get new slider value
handles.Q3 = get(hObject,'Value');

%Set textbox value
set(handles.editQ3, 'String', num2str(handles.Q3)); 

%Calculate new filter coefficients
[ handles.a3,handles.b3 ] = peakfiltercoeff( handles.G3, handles.Q3, handles.Fc3, handles.fs );

% Calculate new filter
handles.H3=dfilt.df2t(handles.b3,handles.a3);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sliderQ3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderQ3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderFc3_Callback(hObject, eventdata, handles)
% hObject    handle to sliderFc3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get new slider value
handles.Fc3 = get(hObject,'Value');

%Set textbox value
set(handles.editFc3, 'String', num2str(handles.Fc3)); 

%Calculate new filter coefficients
[ handles.a3,handles.b3 ] = peakfiltercoeff( handles.G3, handles.Q3, handles.Fc3, handles.fs );

% Calculate new filter
handles.H3=dfilt.df2t(handles.b3,handles.a3);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function sliderFc3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderFc3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderG3_Callback(hObject, eventdata, handles)
% hObject    handle to sliderG3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get new slider value
handles.G3 = get(hObject,'Value');

%Set textbox value
set(handles.editG3, 'String', num2str(handles.G3)); 

%Calculate new filter coefficients
[ handles.a3,handles.b3 ] = peakfiltercoeff( handles.G3, handles.Q3, handles.Fc3, handles.fs );

% Calculate new filter
handles.H3=dfilt.df2t(handles.b3,handles.a3);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sliderG3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderG3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderQ2_Callback(hObject, eventdata, handles)
% hObject    handle to sliderQ2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get new slider value
handles.Q2 = get(hObject,'Value');

%Set textbox value
set(handles.editQ2, 'String', num2str(handles.Q2)); 

%Calculate new filter coefficients
[ handles.a2,handles.b2 ] = peakfiltercoeff( handles.G2, handles.Q2, handles.Fc2, handles.fs );

% Calculate new filter
handles.H2=dfilt.df2t(handles.b2,handles.a2);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function sliderQ2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderQ2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderFc2_Callback(hObject, eventdata, handles)
% hObject    handle to sliderFc2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get slider value
handles.Fc2 = get(hObject,'Value');

%Set textbox value
set(handles.editFc2, 'String', num2str(handles.Fc2)); 

%Get filter coefficients
[ handles.a2,handles.b2 ] = peakfiltercoeff( handles.G2, handles.Q2, handles.Fc2, handles.fs );

% Calculate new filter
handles.H2=dfilt.df2t(handles.b2,handles.a2);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sliderFc2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderFc2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderG2_Callback(hObject, eventdata, handles)
% hObject    handle to sliderG2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get slider value
handles.G2 = get(hObject,'Value');

%Set textbox value
set(handles.editG2, 'String', num2str(handles.G2)); 

%Get filter coefficients
[ handles.a2,handles.b2 ] = peakfiltercoeff( handles.G2, handles.Q2, handles.Fc2, handles.fs );

% Calculate new filter
handles.H2=dfilt.df2t(handles.b2,handles.a2);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sliderG2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderG2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderQ1_Callback(hObject, eventdata, handles)
% hObject    handle to sliderQ1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.Q1 = get(hObject,'Value');

%Set textbox value
set(handles.editQ1, 'String', num2str(handles.Q1)); 

%Get filter coefficients
[ handles.a1,handles.b1 ] = peakfiltercoeff( handles.G1, handles.Q1, handles.Fc1, handles.fs );

% Calculate new filter
handles.H1=dfilt.df2t(handles.b1,handles.a1);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function sliderQ1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderQ1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderFc1_Callback(hObject, eventdata, handles)
% hObject    handle to sliderFc1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get slider value
handles.Fc1 = get(hObject,'Value');

%Set textbox value
set(handles.editFc1, 'String', num2str(handles.Fc1)); 

%Get filter coefficients
[ handles.a1,handles.b1 ] = peakfiltercoeff( handles.G1, handles.Q1, handles.Fc1, handles.fs );

% Calculate new filter
handles.H1=dfilt.df2t(handles.b1,handles.a1);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% --- Executes during object creation, after setting all properties.
function sliderFc1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderFc1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderG1_Callback(hObject, eventdata, handles)
% hObject    handle to sliderG1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.G1 = get(hObject,'Value');

%Set textbox value
set(handles.editG1, 'String', num2str(handles.G1)); 

%Get filter coefficients
[ handles.a1,handles.b1 ] = peakfiltercoeff( handles.G1, handles.Q1, handles.Fc1, handles.fs );

% Calculate new filter
handles.H1=dfilt.df2t(handles.b1,handles.a1);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function sliderG1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderG1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in Play.
function Play_Callback(hObject, eventdata, handles)
% hObject    handle to Play (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

y = audioread(handles.file,handles.samples);

left=(y(:,1));
right=(y(:,2));

% bl = 2^10; %blocklength
% 
% %Fix lengt of vectors
% X=zeros(handles.samples(2)+bl-mod(handles.samples(2),bl),1);
% left(numel(X)) = 0;
% right(numel(X)) = 0;
% 
% % Split the vector in blocks. Block i = matrix(:,i)
% nrOfB = length(X)/bl; %Number of blocks
% left=reshape(left,bl,nrOfB);
% right=reshape(right,bl,nrOfB);
% 
% % Filter 1
% [left(:,1), xhl] = filter(handles.b1,handles.a1,left(:,1));
% [right(:,1), xhr] = filter(handles.b1,handles.a1,right(:,1));
% for i=2:nrOfB
%     [left(:,i), xhl] = filter(handles.b1,handles.a1,left(:,i), xhl);
%     [right(:,i), xhr] = filter(handles.b1,handles.a1,right(:,i), xhr);
% end
% 
% % Filter 2
% [left(:,1), xhl] = filter(handles.b2,handles.a2,left(:,1));
% [right(:,1), xhr] = filter(handles.b2,handles.a2,right(:,1));
% for i=2:nrOfB
%     [left(:,i), xhl] = filter(handles.b2,handles.a2,left(:,i), xhl);
%     [right(:,i), xhr] = filter(handles.b2,handles.a2,right(:,i), xhr);
% end
% 
% % Filter 3
% [left(:,1), xhl] = filter(handles.b3,handles.a3,left(:,1));
% [right(:,1), xhr] = filter(handles.b3,handles.a3,right(:,1));
% for i=2:nrOfB
%     [left(:,i), xhl] = filter(handles.b3,handles.a3,left(:,i), xhl);
%     [right(:,i), xhr] = filter(handles.b3,handles.a3,right(:,i), xhr);
% end
% 
% % Reassemble blocks to a vector
% left = (reshape(left,[],1));
% right = (reshape(right,[],1));
% 
% %Play filtered sound
% sound(double([left right]),handles.fs)

%Filter sound
Hcas=dfilt.cascade(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo);
left = filter(Hcas,left);
right = filter(Hcas,right);

%Play filtered sound
sound(double([left right]),handles.fs)



function editFc3_Callback(hObject, eventdata, handles)
% hObject    handle to editFc3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editFc3 as text
%        str2double(get(hObject,'String')) returns contents of editFc3 as a double

% Get textbox value
handles.Fc3 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderFc3, 'Value', handles.Fc3); 

%Get filter coefficients
[ handles.a3,handles.b3 ] = peakfiltercoeff( handles.G3, handles.Q3, handles.Fc3, handles.fs );

% Calculate new filter
handles.H3=dfilt.df2t(handles.b3,handles.a3);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editFc3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editFc3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editQ3_Callback(hObject, eventdata, handles)
% hObject    handle to editQ3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editQ3 as text
%        str2double(get(hObject,'String')) returns contents of editQ3 as a double

% Get textbox value
handles.Q3 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderQ3, 'Value', handles.Q3); 

%Get filter coefficients
[ handles.a3,handles.b3 ] = peakfiltercoeff( handles.G3, handles.Q3, handles.Fc3, handles.fs );

% Calculate new filter
handles.H3=dfilt.df2t(handles.b3,handles.a3);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editQ3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editQ3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editG3_Callback(hObject, eventdata, handles)
% hObject    handle to editG3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editG3 as text
%        str2double(get(hObject,'String')) returns contents of editG3 as a double

% Get textbox value
handles.G3 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderG3, 'Value', handles.G3); 

%Get filter coefficients
[ handles.a3,handles.b3 ] = peakfiltercoeff( handles.G3, handles.Q3, handles.Fc3, handles.fs );

% Calculate new filter
handles.H3=dfilt.df2t(handles.b3,handles.a3);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editG3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editG3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editFc2_Callback(hObject, eventdata, handles)
% hObject    handle to editFc2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editFc2 as text
%        str2double(get(hObject,'String')) returns contents of editFc2 as a double

% Get textbox value
handles.Fc2 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderFc2, 'Value', handles.Fc2); 

%Get filter coefficients
[ handles.a2,handles.b2 ] = peakfiltercoeff( handles.G2, handles.Q2, handles.Fc2, handles.fs );

% Calculate new filter
handles.H2=dfilt.df2t(handles.b2,handles.a2);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editFc2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editFc2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editQ2_Callback(hObject, eventdata, handles)
% hObject    handle to editQ2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editQ2 as text
%        str2double(get(hObject,'String')) returns contents of editQ2 as a double

% Get textbox value
handles.Q2 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderQ2, 'Value', handles.Q2); 

%Get filter coefficients
[ handles.a2,handles.b2 ] = peakfiltercoeff( handles.G2, handles.Q2, handles.Fc2, handles.fs );

% Calculate new filter
handles.H2=dfilt.df2t(handles.b2,handles.a2);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editQ2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editQ2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editG2_Callback(hObject, eventdata, handles)
% hObject    handle to editG2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editG2 as text
%        str2double(get(hObject,'String')) returns contents of editG2 as a double

% Get textbox value
handles.G2 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderG2, 'Value', handles.G2); 

%Get filter coefficients
[ handles.a2,handles.b2 ] = peakfiltercoeff( handles.G2, handles.Q2, handles.Fc2, handles.fs );

% Calculate new filter
handles.H2=dfilt.df2t(handles.b2,handles.a2);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function editG2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editG2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editFc1_Callback(hObject, eventdata, handles)
% hObject    handle to editFc1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editFc1 as text
%        str2double(get(hObject,'String')) returns contents of editFc1 as a double

% Get textbox value
handles.Fc1 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderFc1, 'Value', handles.Fc1); 

%Get filter coefficients
[ handles.a1,handles.b1 ] = peakfiltercoeff( handles.G1, handles.Q1, handles.Fc1, handles.fs );

% Calculate new filter
handles.H1=dfilt.df2t(handles.b1,handles.a1);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function editFc1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editFc1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editQ1_Callback(hObject, eventdata, handles)
% hObject    handle to editQ1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editQ1 as text
%        str2double(get(hObject,'String')) returns contents of editQ1 as a double

% Get textbox value
handles.Q1 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderQ1, 'Value', handles.Q1); 

%Get filter coefficients
[ handles.a1,handles.b1 ] = peakfiltercoeff( handles.G1, handles.Q1, handles.Fc1, handles.fs );

% Calculate new filter
handles.H1=dfilt.df2t(handles.b1,handles.a1);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function editQ1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editQ1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editG1_Callback(hObject, eventdata, handles)
% hObject    handle to editG1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editG1 as text
%        str2double(get(hObject,'String')) returns contents of editG1 as a double

% Get textbox value
handles.G1 = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderG1, 'Value', handles.G1); 

%Get filter coefficients
[ handles.a1,handles.b1 ] = peakfiltercoeff( handles.G1, handles.Q1, handles.Fc1, handles.fs );

% Calculate new filter
handles.H1=dfilt.df2t(handles.b1,handles.a1);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editG1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editG1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function sliderGLo_Callback(hObject, eventdata, handles)
% hObject    handle to sliderGLo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get slider value
handles.GLo = get(hObject,'Value');

%Set textbox value
set(handles.editGLo, 'String', num2str(handles.GLo)); 

%Get filter coefficients
[ handles.aLo,handles.bLo ] = shelvingcoeff( handles.fs, handles.FcLo, handles.GLo, 0 );

% Calculate new filter
handles.Lo=dfilt.df2t(handles.bLo,handles.aLo);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sliderGLo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderGLo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderFcLo_Callback(hObject, eventdata, handles)
% hObject    handle to sliderFcLo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get slider value
handles.FcLo = get(hObject,'Value');

%Set textbox value
set(handles.editFcLo, 'String', num2str(handles.FcLo)); 

%Get filter coefficients
[ handles.aLo,handles.bLo ] = shelvingcoeff( handles.fs, handles.FcLo, handles.GLo, 0 );

% Calculate new filter
handles.Lo=dfilt.df2t(handles.bLo,handles.aLo);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sliderFcLo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderFcLo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function editFcLo_Callback(hObject, eventdata, handles)
% hObject    handle to editFcLo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editFcLo as text
%        str2double(get(hObject,'String')) returns contents of editFcLo as a double

% Get textbox value
handles.FcLo = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderFcLo, 'Value', handles.FcLo); 

%Get filter coefficients
[ handles.aLo,handles.bLo ] = shelvingcoeff( handles.fs, handles.FcLo, handles.GLo, 0 );

% Calculate new filter
handles.Lo=dfilt.df2t(handles.bLo,handles.aLo);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editFcLo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editFcLo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editGLo_Callback(hObject, eventdata, handles)
% hObject    handle to editGLo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editGLo as text
%        str2double(get(hObject,'String')) returns contents of editGLo as a double

% Get textbox value
handles.GLo = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderGLo, 'Value', handles.GLo); 

%Get filter coefficients
[ handles.aLo,handles.bLo ] = shelvingcoeff( handles.fs, handles.FcLo, handles.GLo, 0 );

% Calculate new filter
handles.Lo=dfilt.df2t(handles.bLo,handles.aLo);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editGLo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editGLo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function sliderGHi_Callback(hObject, eventdata, handles)
% hObject    handle to sliderGHi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get slider value
handles.GHi = get(hObject,'Value');

%Set textbox value
set(handles.editGHi, 'String', num2str(handles.GHi)); 

%Get filter coefficients
[ handles.aHi,handles.bHi ] = shelvingcoeff( handles.fs, handles.FcHi, handles.GHi, 1 );

% Calculate new filter
handles.Hi=dfilt.df2t(handles.bHi,handles.aHi);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function sliderGHi_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderGHi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderFcHi_Callback(hObject, eventdata, handles)
% hObject    handle to sliderFcHi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Get new slider value
handles.FcHi = get(hObject,'Value');

%Set textbox value
set(handles.editFcHi, 'String', num2str(handles.FcHi)); 

%Calculate new filter coefficients
[ handles.aHi,handles.bHi ] = shelvingcoeff( handles.fs, handles.FcHi, handles.GHi, 1 );

% Calculate new filter
handles.Hi=dfilt.df2t(handles.bHi,handles.aHi);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sliderFcHi_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderFcHi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function editFcHi_Callback(hObject, eventdata, handles)
% hObject    handle to editFcHi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editFcHi as text
%        str2double(get(hObject,'String')) returns contents of editFcHi as a double

% Get textbox value
handles.FcHi = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderFcHi, 'Value', handles.FcHi); 

%Calculate new filter coefficients
[ handles.aHi,handles.bHi ] = shelvingcoeff( handles.fs, handles.FcHi, handles.GHi, 1 );

% Calculate new filter
handles.Hi=dfilt.df2t(handles.bHi,handles.aHi);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function editFcHi_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editFcHi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editGHi_Callback(hObject, eventdata, handles)
% hObject    handle to editGHi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editGHi as text
%        str2double(get(hObject,'String')) returns contents of editGHi as a double

% Get textbox value
handles.GHi = str2double(get(hObject,'String'));

%Set slider value
set(handles.sliderGHi, 'Value', handles.GHi); 

%Get filter coefficients
[ handles.aHi,handles.bHi ] = shelvingcoeff( handles.fs, handles.FcHi, handles.GHi, 1 );

% Calculate new filter
handles.Hi=dfilt.df2t(handles.bHi,handles.aHi);

%Plot frequency response...
freqResp(handles.H1,handles.H2,handles.H3,handles.Hi,handles.Lo,handles.fs)

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function editGHi_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editGHi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
