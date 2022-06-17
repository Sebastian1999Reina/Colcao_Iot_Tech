import pandas as pd
import numpy as np
from sklearn import linear_model


def getDifference(then, now, interval = "secs"):

    duration = now - then
    duration_in_s = duration.total_seconds() 
    
    #Date and Time constants
    yr_ct = 365 * 24 * 60 * 60 #31536000
    day_ct = 24 * 60 * 60 			#86400
    hour_ct = 60 * 60 					#3600
    minute_ct = 60 
    
    def yrs():
      return divmod(duration_in_s, yr_ct)[0]

    def days():
      return divmod(duration_in_s, day_ct)[0]

    def hrs():
      return divmod(duration_in_s, hour_ct)[0]

    def mins():
      return divmod(duration_in_s, minute_ct)[0]

    def secs(): 
      return duration_in_s

    return {
        'yrs': int(yrs()),
        'days': int(days()),
        'hrs': int(hrs()),
        'mins': int(mins()),
        'secs': int(secs())
    }[interval]

def archiveCSVSerial():
    ##Procesamiento de los datos de curva patron
    curvaDATA=pd.read_csv('registroCacao.csv',delimiter=',')
    curvaDATA=curvaDATA.fillna(0);

    #Seleccionamos solanente la columna 0 del dataset(Tiempo)
    date=pd.to_datetime(np.array(curvaDATA.iloc[:, 0])) # Primera columna
    global minutes
    minutes=np.zeros([np.size(date)])
    
    
    for i in range(np.size(date)):
        secToMinutes=(getDifference(date[0], date[i], 'secs'))/60
        minutes[i]=secToMinutes
    minutes=minutes.reshape(-1,1)


    #Seleccionamos solanente la columna 1 del dataset(Temperatura)
    global temp_p
    temp_p = np.array(curvaDATA.iloc[:, 1]) # Segunda columna
    return minutes
    

def iaCurveData():
    archiveCSVSerial()
    
    ###IMPLEMENTACIÓN DE REGRESION POLINOMIAL 
    from sklearn.model_selection import train_test_split
    #Separo los datos de "train" en entrenamiento y prueba para probar los algoritmos
    X_train_p, X_test_p, y_train_p, y_test_p = train_test_split (minutes, temp_p, test_size=0.2)

    from sklearn.preprocessing import PolynomialFeatures
    #Se define el grado del polinomio
    poli_reg = PolynomialFeatures (degree = 3) 


    #Se transforma las características existentes en características de mayor grado
    X_train_poli = poli_reg.fit_transform(X_train_p)
    X_test_poli = poli_reg.fit_transform(X_test_p)

    #Defino el algoritmo a utilizar
    global prCurveData
    prCurveData = linear_model.LinearRegression()

    #Entreno el modelo
    prCurveData.fit(X_train_poli, y_train_p)

    return prCurveData