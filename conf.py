import ConfigParser
Config = ConfigParser.ConfigParser()
Config.read("config.ini")
def setAbanico(a,b,c):
		Config.set(str(a),str(b),str(c))
		print "se cambio el estado del " + str(a)
setAbanico("Abanico","Estado","0")
file = open("config.ini","w") #abre config.ini, si no existe la crea
Config.write(file)#cierra el archivo
file.close()
