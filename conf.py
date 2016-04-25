import ConfigParser
class conf:
		def __init__(self,a,b,c):
				self.Config = ConfigParser.ConfigParser()
				self.Config.read("config.ini")
				self.set(a,b,c)
				file = open("config.ini","w") 
				self.Config.write(file)
				file.close()
		def set(self,a,b,c):
				self.Config.set(str(a),str(b),str(c))
				print "se cambio el estado del " + str(a)
		
