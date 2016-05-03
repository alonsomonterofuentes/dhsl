#!/usr/bin/env python
from escribirSerial import *
from lectura import *
from conf import *
import os
from time import sleep
N = None
conf = conf(None,None,None)
def setN(n,mensaje):
		global N
		if n == None:
				try:
						N = int(raw_input(mensaje))
				except ValueError:	
						setN(None,"no es un numero, intentelo de nuevo.")
		else: 
				N = n
def getN():
		global N	
		return N
#crea un "banner" donde se pone un mensaje de manera que llame la atencion del usuario
def banner(opcion):
		os.system("clear")
		opcion = str(opcion)
		l = len(opcion)	
		#print "\n"
		print (l+4)*"*"
		print 2*"*" +  str(opcion) + 2*"*"
		print (l+4)*"*"
#Hace una lista con numeros para cada opcion de la lista
def opciones_menu(lista):	
		for item in lista:	
				print str(lista.index(item)+1)+"."+item
		setN(None,"\nSeleccione una opcion:")
#Define que es lo que se hace al seleccionar algo en el menu principal
def seleccion_principal(opcion):
		if(opcion == 1 ):
			configurar_servidor()
		elif(opcion ==2):
				controlarBombillo()	
		elif(opcion == 3):
				contrloarVentilador
		elif(opcion == 4):
			tomarFotos()
		elif(opcion ==4):
			os.system("clear")
			exit()
#menu de configurar servidor
def configurar_servidor():
		banner("Configurar Servidor")
		secciones = conf.Config.sections()
		secciones2 = secciones
		secciones2.append("Salir")
		opciones_menu(secciones2)
		if(getN()!= 9):
				configurar_sec(secciones,getN()-1)
		else:
				principal()		
	
#menu de configurar una seccion del config.ini
def configurar_sec(secciones,seccion):
		banner("Configurar "+secciones[seccion])	
		opciones_menu(conf.Config.options(secciones[seccion]))
		seccionElegida = conf.Config.options(secciones[seccion])
		opcionElegida =  seccionElegida[getN()-1]
		print("Se eligio: " + str(opcionElegida))
		print ("Valor actural configuracion manual de : " + str(conf.Config.get(secciones[seccion],opcionElegida)))
		setN(None,"Nuevo valor de configuracion manual de " + opcionElegida + " ")
		conf.set(str(secciones[seccion]),str(opcionElegida),getN())
		principal()
#muestra los valores de los sensores por aparte
def tomarFotos():
		n = raw_input("Nombre de la imagen")
		os.system("fswebcam -r 1920x1080 " + str(n) +".jpg")
		principal()
def controlarBombillo():
		banner("Desea activar el control manual del Bombillo?")
		siono = ["si","no"]
		apagaroEncender=["Apagar","Encender"]
		opciones_menu(siono)
		if(getN()==1):
				banner("Desea apagar o encender el bombillo?")
				opciones_menu(apagaroEncender)
				if getN()==1:
						conf.Config.set("Iluminacion","Control Manual","1")
						conf.Config.set("Bombillo","estado","0")
				elif getN() == 2:
						conf.Config.set("Iluminacion","Control Manual","1")
						conf.Config.set("Bombillo","estado","1")
		else: principal()
def controlarVentilador():
		banner("Desea activar el control manual del Ventilador?")
		siono = ["si","no"]
		apagaroEncender=["Apagar","Encender"]
		opciones_menu(siono)
		if(getN()==1):
				banner("Desea apagar o encender el ventilador?")
				opciones_menu(apagaroEncender)
				if getN()==1:
						conf.Config.set("Temperatura","Control Manual","1")
						conf.Config.set("Abanico","estado","0")
				elif getN() == 2:
						conf.Config.set("Temperatura","Control Manual","1")
						conf.Config.set("Abanico","estado","1")
		else: principal()
def principal():
		#ensena el banner de bienvenido por medio segundo
		banner("Bienvenido/a a la casa inteligente")
		sleep(0.5)
		#ensena el banner de el menu principal
		banner("Que desea hacer?")
		print "-Si es la primera vez que usa el programa, escoger la opcion 1\n"
		#estas son las opciones del menu principal, se dan como un vector a opciones_menu para que las despliegue
		opciones_menu_principal = ["Configurar servidor","Controlar Bombillo","Controlar Ventilador","Tomar foto", "Salir"]
		opciones_menu(opciones_menu_principal)
		seleccion_principal(getN())
		eS = escribirSerial()
principal()
		

