#!/usr/bin/env python
import os
from time import sleep

def header(opcion):
		opcion = str(opcion)
		l = len(opcion)	
		print "\n"
		print (l+4)*"*"
		print 2*"*" +  str(opcion) + 2*"*"
		print (l+4)*"*"

def opciones_menu(lista):
		print "\n"
		for item in lista:	
				print str(lista.index(item)+1)+"."+item
		x = raw_input("\nSeleccione una opcion\n")
		x = int(x)
		print "Se selecciono:"
		print lista[x]
								


header("Bienvenido/a a la casa inteligente")
sleep(1)
header("Que desea hacer?")
opciones_opciones_menu_principal = ["Configurar servidor","Ver info de sensores","Controlar actuador", "Salir"]
opciones_menu(opciones_menu_principal)
