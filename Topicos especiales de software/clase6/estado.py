import tkinter as tk

class Puerta:

	def __init__(self):
		self.estado = None

	def open(self): 
		return self.estado.abrir()    

	def close(self):        
		return self.estado.cerrar() 

	def arm(self):
		return self.estado.armar()    

	def disarm(self):
		return self.estado.desarmar()

	def fix(self):
		return self.estado.reparar()

	def testear(self):
		return self.estado.test()

	def end_testear(self):
		return self.estado.end_test()

	def cambiar_estado(self,state):
		self.estado=state                     


class Estado_abstracto:


	def abrir(self): 
		pass

	def cerrar(self):        
		pass

	def armar(self):
		pass

	def desarmar(self):
		pass

	def reparar(self):
		pass

	def test(self):
		pass

	def end_test(self):
		pass     


class Estado_Apagado(Estado_abstracto):
	def __init__(self,door):
		self.puerta = door
		self.nombre_estado = "abierto"

	def abrir(self): 
		return False

	def cerrar(self): 
		print("Llamando a cerrado desde abierto")       
		self.puerta.cambiar_estado(Estado_Cerrar(self.puerta))
		return True

	def armar(self):
		return False

	def desarmar(self):
		return False

	def reparar(self):
		return False

	def test(self):
		return False

	def end_test(self):
		return False

class Estado_Enfriando(Estado_abstracto):
	def __init__(self,door):
		self.puerta = door
		self.nombre_estado = "cerrado"

	def abrir(self):
		self.puerta.cambiar_estado(Estado_Abrir(self.puerta))
		return True

	def cerrar(self):        
		return False

	def armar(self):
		self.puerta.cambiar_estado(Estado_Armar(self.puerta))
		return True

	def desarmar(self):
		return False

	def reparar(self):
		return False

	def test(self):
		self.puerta.cambiar_estado(Estado_Test(self.puerta))
		return True

	def end_test(self):
		return False


class Estado_Detectado_señal(Estado_abstracto):
	def __init__(self,door):
		self.puerta=door
		self.nombre_estado = "armado"

	def abrir(self): 
		self.puerta.cambiar_estado(Estado_Desarmar(self.puerta))
		return True

	def cerrar(self):        
		return Falset

	def armar(self):
		return False

	def desarmar(self):
		self.puerta.cambiar_estado(Estado_Cerrar(self.puerta))		
		return True

	def reparar(self):
		return False

	def test(self):
		return False

	def end_test(self):
		return False


class Estado_listo(Estado_abstracto):
	def __init__(self,door):
		self.puerta=door
		self.nombre_estado = "desarmado"

	def abrir(self): 
		return False

	def cerrar(self):        
		return False

	def armar(self):
		return False

	def desarmar(self):
		return False

	def reparar(self):
		self.puerta.cambiar_estado(Estado_Cerrar(self.puerta))
		return True

	def test(self):
		return False

	def end_test(self):
		self.puerta.cambiar_estado(self.__class__)
		return False


class Estado_Test(Estado_abstracto):
	def __init__(self,door):
		self.puerta=door
		self.nombre_estado = "Testeado"

	def abrir(self): 
		return False

	def cerrar(self):        
		return False

	def armar(self):
		return False

	def desarmar(self):
		return False

	def reparar(self):
		return False

	def test(self):
		return False

	def end_test(self):
		self.puerta.cambiar_estado(Estado_Cerrar(self.puerta))
		return True



class Aplicacion:
	def __init__(self):

		self.backdoor = Puerta()
		self.backdoor.estado = Estado_Cerrar(self.backdoor)
		self.ventana1=tk.Tk()
		self.ventana1.title("Controles Button y Label")


		self.label1=tk.Label(self.ventana1, text="Estado:")
		self.label1.grid(column=0, row=0)
		self.label1.configure(foreground="red")

		self.label2=tk.Label(self.ventana1, text=self.backdoor.estado.nombre_estado)
		self.label2.grid(column=0, row=1)

		self.boton1=tk.Button(self.ventana1, text="Abierto", command=self.abrir)
		self.boton1.grid(column=1, row=2)

		self.boton2=tk.Button(self.ventana1, text="Cerrado", command=self.cerrar)
		self.boton2.grid(column=1, row=3)

		self.boton3=tk.Button(self.ventana1, text="Armar", command=self.armar)
		self.boton3.grid(column=1, row=4)

		self.boton4=tk.Button(self.ventana1, text="Desarmar", command=self.desarmar)
		self.boton4.grid(column=1, row=5)

		self.boton5=tk.Button(self.ventana1, text="Reparar", command=self.reparar)
		self.boton5.grid(column=1, row=6)

		self.boton6=tk.Button(self.ventana1, text="Test", command=self.test)
		self.boton6.grid(column=1, row=7)

		self.boton6=tk.Button(self.ventana1, text="End_Test", command=self.end_test)
		self.boton6.grid(column=1, row=8)            

		self.ventana1.mainloop()


	def abrir(self):
		self.backdoor.open()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)

	def cerrar(self):
		self.backdoor.close()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)


	def armar(self):
		self.backdoor.arm()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)

	def desarmar(self):
		self.backdoor.disarm()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)

	def reparar(self):
		self.backdoor.fix()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)

	def test(self):
		self.backdoor.testear()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)

	def end_test(self):
		self.backdoor.end_testear()
		self.label2.configure(text=self.backdoor.estado.nombre_estado)



aplicacion1=Aplicacion()