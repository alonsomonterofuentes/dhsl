import ConfigParser

class conf:
		#inicializa el archivo config.ini, si tiene argumentos corre la funcion set
		def __init__(self,a,b,c):
				self.Config = ConfigParser.ConfigParser()
				self.Config.read("config.ini")
				if(a != None):
						self.set(a,b,c)
						file = open("config.ini","w") 
						self.Config.write(file)
						file.close()
		#escribe al archivo config.ini
		
		def set(self,a,b,c):
				self.Config.set(str(a),str(b),str(c))
				file = open("config.ini","w") 
				self.Config.write(file)
				print "se cambio el estado del " + str(a)
