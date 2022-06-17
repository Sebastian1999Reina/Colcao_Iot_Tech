import curveOriginal
import dataLoad

enableMotor=0

def iaColcao():
    #IA for data
    prCurveOriginal=curveOriginal.iaCurveOriginal() #Llamamos IA de la curva patron
    print('Ecuación del modelo patron: ')
    print('y = ', prCurveOriginal.coef_[3], 'x^3 +', prCurveOriginal.coef_[2], 'x^2 +', prCurveOriginal.coef_[1], 'x +', prCurveOriginal.intercept_)
    prCurveData=dataLoad.iaCurveData()              #Llamamos IA de la curva datos obtenida
    print('Ecuación del modelo obtenido: ')
    print('y = ', prCurveData.coef_[3], 'x^3 +', prCurveData.coef_[2], 'x^2 +', prCurveData.coef_[1], 'x +', prCurveData.intercept_)
    #Prediction of valors
    minutes=dataLoad.archiveCSVSerial()
    timeMinutes=minutes[-1]+10
    print(timeMinutes)
    yOriginal=(prCurveOriginal.coef_[3]*(timeMinutes*timeMinutes*timeMinutes))+(prCurveOriginal.coef_[2]*(timeMinutes*timeMinutes))+(prCurveOriginal.coef_[1]*(timeMinutes))+(prCurveOriginal.intercept_)
    yIA=(prCurveData.coef_[3]*(timeMinutes*timeMinutes*timeMinutes))+(prCurveData.coef_[2]*(timeMinutes*timeMinutes))+(prCurveData.coef_[1]*(timeMinutes))+(prCurveData.intercept_)
    print(yOriginal)
    print(yIA)
    #Conditionals
    global enableMotor
    if(yIA<yOriginal):
        print('Motor enable')
        enableMotor=1
    else:
        print('Motor desenable')
        enableMotor=0

    return enableMotor

    
