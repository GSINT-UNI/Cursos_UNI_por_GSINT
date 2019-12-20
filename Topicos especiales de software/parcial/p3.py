import tkinter as tk

class Puerta:

	def __init__(self):
		self.estado = None

	def apagado(self): 
		return self.estado.prender()    

	def enfriando(self):        
		return self.estado.apagar() 

	def detectando(self):
		return self.estado.detectaron()    

	def listo(self):
		return self.estado.detectaroff()

	def cambiar_estado(self,state):
		self.estado=state                     


class Estado_abstracto:

	def prender(self): 
		pass

	def apagar(self):        
		pass

	def detectaron(self):
		pass

	def detectaroff(self):
		pass

class Estado_Apagado(Estado_abstracto):
	def __init__(self,door):
		self.puerta = door
		self.nombre_estado = "abierto"

	def prender(self): 
        self.puerta.cambiar_estado(Estado_Detectado_señal(self.puerta))
		return True

	def apagar(self): 		
		return False

	def detectaron(self):
		return False

	def detectaroff(self):
		return False



class Estado_Enfriando(Estado_abstracto):
	def __init__(self,door):
		self.puerta = door
		self.nombre_estado = "cerrado"

	def prender(self):		
		return False

	def apagar(self): 
        self.puerta.cambiar_estado(Estado_Apagado(self.puerta))       
		return False

	def detectaron(self):		
		return False
    
	def detectaroff(self):
		return False




class Estado_Detectado_señal(Estado_abstracto):
	def __init__(self,door):
		self.puerta=door
		self.nombre_estado = "armado"

	def prender(self):
		return True

	def apagar(self):        
		return Falset

	def detectaron(self):
        self.puerta.cambiar_estado(Estado_Detectado_señal(self.puerta)) 
		return False

	def detectaroff(self):
		self.puerta.cambiar_estado(Estado_listo(self.puerta))		
		return True

class Estado_listo(Estado_abstracto):
	def __init__(self,door):
		self.puerta=door
		self.nombre_estado = "desarmado"

	def prender(self): 
		return False

    def apagar(self):
        self.puerta.cambiar_estado(Estado_Apagado(self.puerta))	
        return False
	def detectaron(self):        
		return False

	def detectaroff(self):
		return False

	



class Aplicacion:
	def __init__(self):

		self.backdoor = Puerta()
		self.backdoor.estado = Estado_Apagado(self.backdoor)
		self.ventana1=tk.Tk()
		self.ventana1.title("Controles Button y Label")


		self.label1=tk.Label(self.ventana1, text="Estado:")
		self.label1.grid(column=0, row=0)
		self.label1.configure(foreground="red")

		self.label2=tk.Label(self.ventana1, text=self.backdoor.estado.nombre_estado)
		self.label2.grid(column=0, row=1)

		self.boton1=tk.Button(self.ventana1, text="Encender", command=self.encender)
		self.boton1.grid(column=1, row=2)

		self.boton2=tk.Button(self.ventana1, text="Apagar", command=self.apagar)
		self.boton2.grid(column=1, row=3)

		self.boton3=tk.Button(self.ventana1, text="detectar", command=self.detectar_señal)
		self.boton3.grid(column=1, row=4)

		self.boton4=tk.Button(self.ventana1, text="no detectar", command=self.no_detectar)
		self.boton4.grid(column=1, row=5)
    

		self.ventana1.mainloop()


	def encender(self):
		self.backdoor.prender()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)

	def apagar(self):
		self.backdoor.apagado()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)


	def detectar_señal(self):
		self.backdoor.detectaron()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)

	def no_detectar(self):
		self.backdoor.detectaroff()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)

	
aplicacion1=Aplicacion()