import ConfigParser
class conf:
		def __init__(self):
				self.Config = ConfigParser.ConfigParser()
				self.Config.read("config.ini")
				self.setAbanico("Abanico","Estado","hola")
				file = open("config.ini","w") 
				self.Config.write(file)
				file.close()
		def setAbanico(self,a,b,c):
				self.Config.set(str(a),str(b),str(c))
				print "se cambio el estado del " + str(a)
		
