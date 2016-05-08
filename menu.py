#!/usr/bin/env python
from escribirSerial import *
from conf import *
import os
from time import sleep
N = None
conf = conf(None,None,None)

#pide un input al usuario
def setN(n,mensaje):
		global N
		if n == None:
		#manejo de errores(si no es un numero, lop pide de nuevo)
				try:
						N = int(raw_input(mensaje))
				except ValueError:	
						setN(None,"no es un numero, intentelo de nuevo.")
		else: 
				N = n

#devuelve el input del usuario
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

#Hace una lista con opciones numeradas para cada entrada de la lista
def opciones_menu(lista):	
		for item in lista:	
				print str(lista.index(item)+1)+"."+item
		setN(None,"\nSeleccione una opcion:")

#Define que es lo que se hace al seleccionar algo en el menu principal
def seleccion_principal(opcion):
		if(opcion == 1 ):
			configurar_servidor()
		elif(opcion == 2):
			tomarFotos()
		elif(opcion ==3):
				es = escribirSerial(conf.Config.get("ArduinoUno","puerto"),conf.Config.get("ArduinoDos","puerto"))
		elif(opcion ==4):
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

#permite al usuario tomar una foto y escoger el nombre de esta
def tomarFotos():
		n = raw_input("Nombre de la imagen")
		os.system("fswebcam -r 1920x1080 " + str(n) +".jpg")
		principal()

#funcion principal
def principal():
		#ensena el banner de bienvenido por medio segundo
		banner("Bienvenido/a a la casa inteligente")
		sleep(0.5)
		#ensena el banner de el menu principal
		banner("Que desea hacer?")
		print "-Si es la primera vez que usa el programa, escoger la opcion 1\n"
		#estas son las opciones del menu principal, se dan como un vector a opciones_menu para que las despliegue
		opciones_menu_principal = ["Configurar servidor","Tomar foto","Escribir a arduino", "Salir"]
		opciones_menu(opciones_menu_principal)
		seleccion_principal(getN())

#corre la funcion principal en un ciclo infinito
while True:
		principal()
		

