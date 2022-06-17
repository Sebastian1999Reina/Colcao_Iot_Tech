import pandas as pd
import numpy as np
from sklearn import linear_model

def archiveCSVbase():
    ##Procesamiento de los datos de curva patron
    curvaPatron=pd.read_csv('curveOriginal.csv',delimiter=';')

    #Seleccionamos solanente la columna 0 del dataset(Tiempo)
    global X_p
    X_p = np.array(curvaPatron.iloc[:, 0]) # Primera columna
    X_p=X_p.reshape(-1,1)
    print(type(X_p))

    #Seleccionamos solanente la columna 1 del dataset(Temperatura)
    global y_p
    y_p = np.array(curvaPatron.iloc[:, 1]) # Segunda columna
    

def iaCurveOriginal():
    archiveCSVbase()
    ###IMPLEMENTACIÓN DE REGRESION POLINOMIAL 
    from sklearn.model_selection import train_test_split
    #Separo los datos de "train" en entrenamiento y prueba para probar los algoritmos
    X_train_p, X_test_p, y_train_p, y_test_p = train_test_split (X_p, y_p, test_size=0.2)

    from sklearn.preprocessing import PolynomialFeatures
    #Se define el grado del polinomio
    poli_reg = PolynomialFeatures (degree = 3) 


    #Se transforma las características existentes en características de mayor grado
    X_train_poli = poli_reg.fit_transform(X_train_p)
    X_test_poli = poli_reg.fit_transform(X_test_p)

    #Defino el algoritmo a utilizar
    global prCurveOriginal
    prCurveOriginal = linear_model.LinearRegression()

    #Entreno el modelo
    prCurveOriginal.fit(X_train_poli, y_train_p)

    return prCurveOriginal
    

    