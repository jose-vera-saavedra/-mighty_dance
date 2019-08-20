#Universidad del Valle
#Curso: Tecnologías Geomáticas
#Docente: Ing. Carlos Quiroga
#Hecho por: 
#Jose Miguel Vera Saavedra y Vanessa Hernandez Bedoya

import serial #se importa la libreria serial
import time #Se importa la libreria time
import pandas as pd #Se importa la libreria pandas
ser = serial.Serial("COM3",9600,timeout=0) #se lee el puerto COM del pc y se tiene en cuenta los baudios


while 1: #Se inicia el ciclo para la lectura de los datos de los sensores
    time.sleep(3) #se determina el tiempo en segundos de la lectura de los sensores
    info = ser.readline() #Se lee la variable ser
    var=[] #Se crea una lista nueva donde se guardarán los datos
    var.append(str(info)) #Se agregan los datos en fortamo str en la lsita ya que los datos de los sensores vienen en byte
    df=pd.DataFrame(var)
    df.to_csv("C://Users//Usuario.Usuario-PC//Desktop//lab7.csv",sep=',',header=False, index=False, mode="a") #Se cera el archivo csv en la dirección determinada
    #guardar.write(var)
    print(info) # se imprime los datos en la terminal de python


