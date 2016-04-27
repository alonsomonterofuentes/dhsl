#!/usr/bin/env python

from conf import *
import os
from time import sleep

conf = conf(None,None,None)
N = None
def setN(n,mensaje):
	global N
	#manejo de errores, si lo que ingresa al usuario no puede ser convertido en un int vuelve a pedir que ingrese la opcion 
	if n == None:
		try:
			N = int(raw_input(mensaje))
		except ValueError:	
			print "no es un numero, intentelo de nuevo."
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
		#x = raw_input("\nSeleccione una opcion:")
		#x = int(x)
		setN(None,"\nSeleccione una opcion:")
#Definq que es lo que se hace al seleccionar algo en el menu principal
def seleccion_principal(opcion):
		if(opcion == 1 ):
				configurar_servidor()
		elif(opcion ==2):
			os.system("vim config.ini")
def configurar_servidor():
	banner("Configurar Servidor")
	secciones = conf.Config.sections()
	opciones_menu(secciones)
	configurar_sec(secciones,getN()-1)

def configurar_sec(secciones,seccion):
	banner("Configurar "+secciones[seccion])	
	print "debe ingresar el nombre"
	opciones_menu(conf.Config.options(secciones[seccion]))
def principal():
	#ensena el banner de bienvenido por medio segundo
	banner("Bienvenido/a a la casa inteligente")
	sleep(0.5)
	#ensena el banner de el menu principal
	banner("Que desea hacer?")
	print "-Si es la primera vez que usa el programa, escoger la opcion 1\n"
	#estas son las opciones del menu principal, se dan como un vector a opciones_menu para que las despliegue
	opciones_menu_principal = ["Configurar servidor(Menu)","Configurar servidor(vim)","Ver info de sensores","Controlar actuador", "Volver"]
	opciones_menu(opciones_menu_principal)
	seleccion_principal(getN())
	#confWrite.set("Abanico","estado","2")
	#print confWrite.Config.get("Abanico","estado")
principal()

