import os
from time import sleep

def header(opcion):
	os.system('clear')
	opcion = str(opcion)
	l = len(opcion)	
	print (l+4)*"*"
	print 2*"*" +  str(opcion) + 2*"*"
	print (l+4)*"*"

def menu(lista):
	for item in lista:	
		print str(lista.index(item)+1)+"."+item
	x = raw_input("\nSeleccione una opcion\n")
	x = int(x)
	print "Se selecciono:"
	print lista[x]


header("Bienvenido a la casa inteligente")
sleep(1)
header("Que desea hacer?")
opciones_menu_principal = ["Configurar servidor","Ver informacion de sensores","Controlar actuador", "Salir"]
menu(opciones_menu_principal)
