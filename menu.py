#!/usr/bin/env python
from conf import *
import os
from time import sleep

#crea un "banner" donde se pone un mensaje de manera que llame la atencion del usuario
def banner(opcion):
		os.system("clear")
		opcion = str(opcion)
		l = len(opcion)	
		print "\n"
		print (l+4)*"*"
		print 2*"*" +  str(opcion) + 2*"*"
		print (l+4)*"*"
#Hace una lista con numeros para cada opcion de la lista
def opciones_menu(lista):
		print "\n"
		for item in lista:	
				print str(lista.index(item)+1)+"."+item
		x = raw_input("\nSeleccione una opcion:\n-Si es la primera vez que usa el programa, escoger la opcion 1\n")
		x = int(x)
		print "Se selecciono:"
		print lista[x-1]
								


banner("Bienvenido/a a la casa inteligente")
sleep(1)
banner("Que desea hacer?")
opciones_menu_principal = ["Configurar servidor","Ver info de sensores","Controlar actuador", "Salir"]
opciones_menu(opciones_menu_principal)
x = conf()

