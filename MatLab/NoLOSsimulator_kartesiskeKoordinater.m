%Denne koden er ikke fullstendig kommentert, kildekode til reel kjøring av
%båt er kommenter fullstendig

%% Initial parameters
t = 0;
% Position Matrix
pos = [0 0; 2 10; 4 10; 6 0; 8 0; 10 10; 12 10; 14 0; 16 0; 18 10; 20 10; 22 0; 24 0; 26 10; 28 10; 
    30 0; 32 0; 34 10; 36 10; 38 0; 40 0; 42 10; 44 10; 46 0]*5


%Boat initial position
Xc = pos(1,1)
Yc = pos(1,2)

windSpeed = 0.0;
windAngle = 0;

Rk = 10;
r = 0;
boatSpeed = 2;
i = 1;

compassAngle = 7/4*pi;

%% Main code
while(t < 800 && ((pos(i,1) ~= pos(end,1)) || (pos(i,2) ~= pos(end,2))))
    t = t + 1
    Xa = pos(i,1);
    Ya = pos(i,2);
    Xb = pos(i+1,1);
    Yb = pos(i+1,2);
    Xw = Xb;
    Yw = Yb;
%% Compass
waypointAngle = atan((Yw - Yc)/(Xw-Xc))
if waypointAngle < 0
    waypointAngle = waypointAngle + 2*pi
end

if (Yw - Yc) > 0 && pi < waypointAngle && waypointAngle < 2*pi
    waypointAngle = waypointAngle - pi
    
elseif (Yw - Yc) < 0 && 0 < waypointAngle && waypointAngle < pi
        waypointAngle = waypointAngle + pi
end

corrAngle = waypointAngle - compassAngle
if corrAngle > pi
    corrAngle = corrAngle - 2*pi
elseif corrAngle < -pi
    corrAngle = corrAngle + 2*pi
end


%%Motor Control
if corrAngle < 0
    leftMotorThrustRatio = 1
    rightMotorThustRatio = 1 + (corrAngle/(pi))
elseif corrAngle > 0
    leftMotorThrustRatio = 1 - (corrAngle/(pi))
    rightMotorThustRatio = 1
elseif corrAngle == 0
    leftMotorThrustRatio = 1
    rightMotorThustRatio = 1   
end

%%Påvirkninger på båten
Xc = Xc + boatSpeed*cos(compassAngle) + windSpeed*cos(windAngle)
Yc = Yc + boatSpeed*sin(compassAngle) + windSpeed*sin(windAngle)
compassAngle = compassAngle + corrAngle*0.3

if compassAngle < 0
    compassAngle = compassAngle + 2*pi
elseif compassAngle > 2*pi
    compassAngle = compassAngle - 2*pi
end

if (sqrt((Xb-Xc)^2+(Yb-Yc)^2) < Rk)
    i = i + 1;
end

%plot punkter og linjer
plot(Xa,Ya,'*',Xb,Yb,'*',Xc,Yc,'*',Xw,Yw,'*',[Xa Xb], [Ya Yb])
hold on

%plot radius sirkel
th = 0:pi/50:2*pi;
xunit = r * cos(th) + Xc;
yunit = r * sin(th) + Yc;
plot(xunit, yunit)

%plot båt vektor
starts = [Xc,Yc];
[rx, ry] = pol2cart(compassAngle, boatSpeed);
ends = starts + [rx, ry];
xlist = [starts(:,1), ends(:,1), nan(size(starts,1),1)] .';
ylist = [starts(:,2), ends(:,2), nan(size(starts,1),1)] .';
plot( xlist(:), ylist(:) );

end
t