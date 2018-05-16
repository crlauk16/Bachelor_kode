%Denne koden er ikke fullstendig kommentert, kildekode til reel kjøring av
%båt er kommenter fullstendig

%% Initial parameters
windSpeed = 1;
windAngle = 0;
% Position Matrix
pos = [0 0; 2 10; 4 10; 6 0; 8 0; 10 10; 12 10; 14 0; 16 0; 18 10; 20 10; 22 0; 24 0; 26 10; 28 10; 
    30 0; 32 0; 34 10; 36 10; 38 0; 40 0; 42 10; 44 10; 46 0]*5

Xc = pos(1,1);
Yc = pos(1,2);

Rb = 5;
Rk = 10;
boatSpeed = 2;
i = 1;

t = 0;
compassAngle = 2/4*pi;
%% Main code
while(t < 800 && ((pos(i,1) ~= pos(end,1)) || (pos(i,2) ~= pos(end,2))))
    r = Rb;
    t = t + 1;
    Xa = pos(i,1);
    Ya = pos(i,2);
    Xb = pos(i+1,1);
    Yb = pos(i+1,2);
while(true)
    if r > sqrt((Xb-Xc)^2+(Yb-Yc)^2)
        r = sqrt((Xb-Xc)^2+(Yb-Yc)^2);
    end
    
    if Xa == Xb && Ya ~= Yb 
        resultx1 = Xa;
        resultx2 = Xa;
        resulty1 = sqrt(r^2-(resultx1-Xc)^2)+Yc;
        resulty2 = 2*Yc - resulty1;
    elseif Ya == Yb && Xa ~= Xb
        resulty1 = Ya;
        resulty2 = Ya;
        resultx1 =  (Xa*(- Xa^2*Yb^2 + 2*Xa^2*Yb*Yc - Xa^2*Yc^2 + Xa^2*r^2 + 2*Xa*Xb*Ya*Yb - 2*Xa*Xb*Ya*Yc - 2*Xa*Xb*Yb*Yc + 2*Xa*Xb*Yc^2 - 2*Xa*Xb*r^2 - 2*Xa*Xc*Ya*Yb + 2*Xa*Xc*Ya*Yc + 2*Xa*Xc*Yb^2 - 2*Xa*Xc*Yb*Yc - Xb^2*Ya^2 + 2*Xb^2*Ya*Yc - Xb^2*Yc^2 + Xb^2*r^2 + 2*Xb*Xc*Ya^2 - 2*Xb*Xc*Ya*Yb - 2*Xb*Xc*Ya*Yc + 2*Xb*Xc*Yb*Yc - Xc^2*Ya^2 + 2*Xc^2*Ya*Yb - Xc^2*Yb^2 + Ya^2*r^2 - 2*Ya*Yb*r^2 + Yb^2*r^2)^(1/2) - Xb*(- Xa^2*Yb^2 + 2*Xa^2*Yb*Yc - Xa^2*Yc^2 + Xa^2*r^2 + 2*Xa*Xb*Ya*Yb - 2*Xa*Xb*Ya*Yc - 2*Xa*Xb*Yb*Yc + 2*Xa*Xb*Yc^2 - 2*Xa*Xb*r^2 - 2*Xa*Xc*Ya*Yb + 2*Xa*Xc*Ya*Yc + 2*Xa*Xc*Yb^2 - 2*Xa*Xc*Yb*Yc - Xb^2*Ya^2 + 2*Xb^2*Ya*Yc - Xb^2*Yc^2 + Xb^2*r^2 + 2*Xb*Xc*Ya^2 - 2*Xb*Xc*Ya*Yb - 2*Xb*Xc*Ya*Yc + 2*Xb*Xc*Yb*Yc - Xc^2*Ya^2 + 2*Xc^2*Ya*Yb - Xc^2*Yb^2 + Ya^2*r^2 - 2*Ya*Yb*r^2 + Yb^2*r^2)^(1/2) + Xa^2*Xc + Xb^2*Xc + Xa*Yb^2 + Xb*Ya^2 - 2*Xa*Xb*Xc - Xa*Ya*Yb + Xa*Ya*Yc - Xb*Ya*Yb - Xa*Yb*Yc - Xb*Ya*Yc + Xb*Yb*Yc)/(Xa^2 - 2*Xa*Xb + Xb^2 + Ya^2 - 2*Ya*Yb + Yb^2);
        resultx2 =  (Xb*(- Xa^2*Yb^2 + 2*Xa^2*Yb*Yc - Xa^2*Yc^2 + Xa^2*r^2 + 2*Xa*Xb*Ya*Yb - 2*Xa*Xb*Ya*Yc - 2*Xa*Xb*Yb*Yc + 2*Xa*Xb*Yc^2 - 2*Xa*Xb*r^2 - 2*Xa*Xc*Ya*Yb + 2*Xa*Xc*Ya*Yc + 2*Xa*Xc*Yb^2 - 2*Xa*Xc*Yb*Yc - Xb^2*Ya^2 + 2*Xb^2*Ya*Yc - Xb^2*Yc^2 + Xb^2*r^2 + 2*Xb*Xc*Ya^2 - 2*Xb*Xc*Ya*Yb - 2*Xb*Xc*Ya*Yc + 2*Xb*Xc*Yb*Yc - Xc^2*Ya^2 + 2*Xc^2*Ya*Yb - Xc^2*Yb^2 + Ya^2*r^2 - 2*Ya*Yb*r^2 + Yb^2*r^2)^(1/2) - Xa*(- Xa^2*Yb^2 + 2*Xa^2*Yb*Yc - Xa^2*Yc^2 + Xa^2*r^2 + 2*Xa*Xb*Ya*Yb - 2*Xa*Xb*Ya*Yc - 2*Xa*Xb*Yb*Yc + 2*Xa*Xb*Yc^2 - 2*Xa*Xb*r^2 - 2*Xa*Xc*Ya*Yb + 2*Xa*Xc*Ya*Yc + 2*Xa*Xc*Yb^2 - 2*Xa*Xc*Yb*Yc - Xb^2*Ya^2 + 2*Xb^2*Ya*Yc - Xb^2*Yc^2 + Xb^2*r^2 + 2*Xb*Xc*Ya^2 - 2*Xb*Xc*Ya*Yb - 2*Xb*Xc*Ya*Yc + 2*Xb*Xc*Yb*Yc - Xc^2*Ya^2 + 2*Xc^2*Ya*Yb - Xc^2*Yb^2 + Ya^2*r^2 - 2*Ya*Yb*r^2 + Yb^2*r^2)^(1/2) + Xa^2*Xc + Xb^2*Xc + Xa*Yb^2 + Xb*Ya^2 - 2*Xa*Xb*Xc - Xa*Ya*Yb + Xa*Ya*Yc - Xb*Ya*Yb - Xa*Yb*Yc - Xb*Ya*Yc + Xb*Yb*Yc)/(Xa^2 - 2*Xa*Xb + Xb^2 + Ya^2 - 2*Ya*Yb + Yb^2);
    elseif Ya == Yb && Xa == Xb
        resultx1 = Xa;
        resultx2 = Xa;
        resulty1 = Ya;
        resulty2 = Ya;
        
    else
    resultx1 =  (Xa*(- Xa^2*Yb^2 + 2*Xa^2*Yb*Yc - Xa^2*Yc^2 + Xa^2*r^2 + 2*Xa*Xb*Ya*Yb - 2*Xa*Xb*Ya*Yc - 2*Xa*Xb*Yb*Yc + 2*Xa*Xb*Yc^2 - 2*Xa*Xb*r^2 - 2*Xa*Xc*Ya*Yb + 2*Xa*Xc*Ya*Yc + 2*Xa*Xc*Yb^2 - 2*Xa*Xc*Yb*Yc - Xb^2*Ya^2 + 2*Xb^2*Ya*Yc - Xb^2*Yc^2 + Xb^2*r^2 + 2*Xb*Xc*Ya^2 - 2*Xb*Xc*Ya*Yb - 2*Xb*Xc*Ya*Yc + 2*Xb*Xc*Yb*Yc - Xc^2*Ya^2 + 2*Xc^2*Ya*Yb - Xc^2*Yb^2 + Ya^2*r^2 - 2*Ya*Yb*r^2 + Yb^2*r^2)^(1/2) - Xb*(- Xa^2*Yb^2 + 2*Xa^2*Yb*Yc - Xa^2*Yc^2 + Xa^2*r^2 + 2*Xa*Xb*Ya*Yb - 2*Xa*Xb*Ya*Yc - 2*Xa*Xb*Yb*Yc + 2*Xa*Xb*Yc^2 - 2*Xa*Xb*r^2 - 2*Xa*Xc*Ya*Yb + 2*Xa*Xc*Ya*Yc + 2*Xa*Xc*Yb^2 - 2*Xa*Xc*Yb*Yc - Xb^2*Ya^2 + 2*Xb^2*Ya*Yc - Xb^2*Yc^2 + Xb^2*r^2 + 2*Xb*Xc*Ya^2 - 2*Xb*Xc*Ya*Yb - 2*Xb*Xc*Ya*Yc + 2*Xb*Xc*Yb*Yc - Xc^2*Ya^2 + 2*Xc^2*Ya*Yb - Xc^2*Yb^2 + Ya^2*r^2 - 2*Ya*Yb*r^2 + Yb^2*r^2)^(1/2) + Xa^2*Xc + Xb^2*Xc + Xa*Yb^2 + Xb*Ya^2 - 2*Xa*Xb*Xc - Xa*Ya*Yb + Xa*Ya*Yc - Xb*Ya*Yb - Xa*Yb*Yc - Xb*Ya*Yc + Xb*Yb*Yc)/(Xa^2 - 2*Xa*Xb + Xb^2 + Ya^2 - 2*Ya*Yb + Yb^2);
    resultx2 =  (Xb*(- Xa^2*Yb^2 + 2*Xa^2*Yb*Yc - Xa^2*Yc^2 + Xa^2*r^2 + 2*Xa*Xb*Ya*Yb - 2*Xa*Xb*Ya*Yc - 2*Xa*Xb*Yb*Yc + 2*Xa*Xb*Yc^2 - 2*Xa*Xb*r^2 - 2*Xa*Xc*Ya*Yb + 2*Xa*Xc*Ya*Yc + 2*Xa*Xc*Yb^2 - 2*Xa*Xc*Yb*Yc - Xb^2*Ya^2 + 2*Xb^2*Ya*Yc - Xb^2*Yc^2 + Xb^2*r^2 + 2*Xb*Xc*Ya^2 - 2*Xb*Xc*Ya*Yb - 2*Xb*Xc*Ya*Yc + 2*Xb*Xc*Yb*Yc - Xc^2*Ya^2 + 2*Xc^2*Ya*Yb - Xc^2*Yb^2 + Ya^2*r^2 - 2*Ya*Yb*r^2 + Yb^2*r^2)^(1/2) - Xa*(- Xa^2*Yb^2 + 2*Xa^2*Yb*Yc - Xa^2*Yc^2 + Xa^2*r^2 + 2*Xa*Xb*Ya*Yb - 2*Xa*Xb*Ya*Yc - 2*Xa*Xb*Yb*Yc + 2*Xa*Xb*Yc^2 - 2*Xa*Xb*r^2 - 2*Xa*Xc*Ya*Yb + 2*Xa*Xc*Ya*Yc + 2*Xa*Xc*Yb^2 - 2*Xa*Xc*Yb*Yc - Xb^2*Ya^2 + 2*Xb^2*Ya*Yc - Xb^2*Yc^2 + Xb^2*r^2 + 2*Xb*Xc*Ya^2 - 2*Xb*Xc*Ya*Yb - 2*Xb*Xc*Ya*Yc + 2*Xb*Xc*Yb*Yc - Xc^2*Ya^2 + 2*Xc^2*Ya*Yb - Xc^2*Yb^2 + Ya^2*r^2 - 2*Ya*Yb*r^2 + Yb^2*r^2)^(1/2) + Xa^2*Xc + Xb^2*Xc + Xa*Yb^2 + Xb*Ya^2 - 2*Xa*Xb*Xc - Xa*Ya*Yb + Xa*Ya*Yc - Xb*Ya*Yb - Xa*Yb*Yc - Xb*Ya*Yc + Xb*Yb*Yc)/(Xa^2 - 2*Xa*Xb + Xb^2 + Ya^2 - 2*Ya*Yb + Yb^2);

    resulty1 = ((Yb-Ya)/(Xb-Xa))*(resultx1-Xa)+Ya;
    resulty2 = ((Yb-Ya)/(Xb-Xa))*(resultx2-Xa)+Ya;
    end
    
    realCheckx1 = isreal(resultx1);
    realCheckx2 = isreal(resultx2);
    realChecky1 = isreal(resulty1);
    realChecky2 = isreal(resulty2);
    realCheck = (realCheckx1 == true && realChecky1 == true) || (realCheckx2 == true && realChecky2 == true)
    
    %% Check if LOS waypoint is bettween way points
    if realCheck
    if Xa < Xb
        lineCheckX = (Xa <= resultx1 && resultx1 <= Xb) || (Xa <= resultx2 && resultx2 <= Xb)
    elseif Xb < Xa
        lineCheckX = (Xa >= resultx1 && resultx1 >= Xb) || (Xa >= resultx2 && resultx2 >= Xb)
    elseif Xa == Xb
        lineCheckX = true
    end
    
    if Ya < Yb
        lineCheckY = (Ya <= resulty1 && resulty1 <= Yb) || (Ya <= resulty2 && resulty2 <= Yb)
    elseif Yb < Ya
        lineCheckY = (Ya >= resulty1 && resulty1 >= Yb) || (Ya >= resulty2 && resulty2 >= Yb)
    elseif Ya == Yb
        lineCheckY = true
    end
    end
    %% Calculation
    
    if realCheck && lineCheckX && lineCheckY
        if sqrt((Xb - resultx1)^2+(Yb - resulty1)^2) < sqrt((Xb - resultx2)^2+(Yb - resulty2)^2)
                Xw = resultx1;
                Yw = resulty1;
                break
        else
                Xw = resultx2;
                Yw = resulty2;
                break
        end
    else
        r = r + Rb*0.2 ;
        %Xw = Xb
        %Yw = Yb
        %disp('Boat is too far from route, LOS guidance DEACTIVATED')
    end

end
%% Compass
waypointAngle = atan((Yw - Yc)/(Xw-Xc));
if waypointAngle < 0
    waypointAngle = waypointAngle + 2*pi;
end

if (Yw - Yc) > 0 && pi < waypointAngle && waypointAngle < 2*pi
    waypointAngle = waypointAngle - pi;
    
elseif (Yw - Yc) < 0 && 0 < waypointAngle && waypointAngle < pi
        waypointAngle = waypointAngle + pi;
end

corrAngle = waypointAngle - compassAngle;
if corrAngle > pi
    corrAngle = corrAngle - 2*pi;
elseif corrAngle < -pi
    corrAngle = corrAngle + 2*pi;
end


%%Motor Control
if corrAngle < 0
    leftMotorThrustRatio = 1;
    rightMotorThustRatio = 1 + (corrAngle/(pi));
elseif corrAngle > 0
    leftMotorThrustRatio = 1 - (corrAngle/(pi));
    rightMotorThustRatio = 1;
elseif corrAngle == 0
    leftMotorThrustRatio = 1;
    rightMotorThustRatio = 1;   
end

%plot punkter og linjer
plot(Xa,Ya,'*',Xb,Yb,'*',Xc,Yc,'*',Xw,Yw,'*',[Xa Xb], [Ya Yb])
hold on

%plot radius sirkel
th = 0:pi/50:2*pi;
xunit = 0 * cos(th) + Xc;
yunit = 0 * sin(th) + Yc;
plot(xunit, yunit)

%plot båt vektor
starts = [Xc,Yc];
[rx, ry] = pol2cart(compassAngle, boatSpeed);
ends = starts + [rx, ry];
xlist = [starts(:,1), ends(:,1), nan(size(starts,1),1)] .';
ylist = [starts(:,2), ends(:,2), nan(size(starts,1),1)] .';
plot( xlist(:), ylist(:) );

%%Påvirkninger på båten
Xc = Xc + boatSpeed*cos(compassAngle) + windSpeed*cos(windAngle);
Yc = Yc + boatSpeed*sin(compassAngle) + windSpeed*sin(windAngle);
compassAngle = compassAngle + corrAngle*0.3;

if compassAngle < 0
    compassAngle = compassAngle + 2*pi;
elseif compassAngle > 2*pi
    compassAngle = compassAngle - 2*pi;
end

if (sqrt((Xb-Xc)^2+(Yb-Yc)^2) < Rk)
    i = i + 1;
end
end
t