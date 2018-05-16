%Denne koden er ikke fullstendig kommentert, kildekode til reel kjøring av
%båt er kommenter fullstendig

%% Initial parameters
windSpeed = 0;
windAngle = 0;
% Position Matrix
pos = [
475462 6464789;
475489 6464730;
475550 6464685;
475622 6464717;
475629 6464785;
475588 6464833;
475516 6464822;
475465 6464798]

Xc = pos(1,1);
Yc = pos(1,2);

Rb = 10;
Rk = 10;
boatSpeed = 1.5;
i = 1;

t = 0;
compassAngle = 1/4*pi;
%% Main code
while(t < 600 && ((pos(i,1) ~= pos(end,1)) || (pos(i,2) ~= pos(end,2))))
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
    
    realCheck1 = isreal(resultx1) && isreal(resulty1)
    realCheck2 = isreal(resultx2) && isreal(resulty2)
    
    %% Check if LOS waypoint is bettween way points
    if realCheck1
        if Xa < Xb && Ya < Yb
            lineCheck1 = (Xa <= resultx1 && resultx1 <= Xb) && (Ya <= resulty1 && resulty1 <= Yb)
        elseif Xa < Xb && Ya > Yb
            lineCheck1 = (Xa <= resultx1 && resultx1 <= Xb) && (Ya >= resulty1 && resulty1 >= Yb)
        elseif Xa > Xb && Ya < Yb
            lineCheck1 = (Xa >= resultx1 && resultx1 >= Xb) && (Ya <= resulty1 && resulty1 <= Yb)
        elseif Xa > Xb && Ya > Yb
            lineCheck1 = (Xa >= resultx1 && resultx1 >= Xb) && (Ya >= resulty1 && resulty1 >= Yb)
        end
    end
    
    if realCheck2
        if Xa < Xb && Ya < Yb
            lineCheck2 = (Xa <= resultx2 && resultx2 <= Xb) && (Ya <= resulty2 && resulty2 <= Yb)
        elseif Xa < Xb && Ya > Yb
            lineCheck2 = (Xa <= resultx2 && resultx2 <= Xb) && (Ya >= resulty2 && resulty2 >= Yb)
        elseif Xa > Xb && Ya < Yb
            lineCheck2 = (Xa >= resultx2 && resultx2 >= Xb) && (Ya <= resulty2 && resulty2 <= Yb)
        elseif Xa > Xb && Ya > Yb
            lineCheck2 = (Xa >= resultx2 && resultx2 >= Xb) && (Ya >= resulty2 && resulty2 >= Yb)
        end
    end
    
    if (realCheck1 == false) && (realCheck2 == false)
        lineCheck1 = false
        lineCheck2 = false
    end
    
    if lineCheck1 &&  lineCheck2
        if sqrt((Xb - resultx1)^2+(Yb - resulty1)^2) < sqrt((Xb - resultx2)^2+(Yb - resulty2)^2)
                Xw = resultx1
                Yw = resulty1
                break
        else
                Xw = resultx2
                Yw = resulty2
                break
        end
    elseif (lineCheck1 == true) && (lineCheck2 == false)
        Xw = resultx1
        Yw = resulty1
        break
    elseif (lineCheck1 == false) && (lineCheck2 == true)
        Xw = resultx2
        Yw = resulty2
        break
    else
        r = r + Rb*0.2 
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
    rightMotorThustRatio = 1 + (corrAngle/(2*pi));
elseif corrAngle > 0
    leftMotorThrustRatio = 1 - (corrAngle/(2*pi));
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