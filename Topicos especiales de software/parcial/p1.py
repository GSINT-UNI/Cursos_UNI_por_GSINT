import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext as st
import re
from abc import ABC, abstractmethod



class Alumno:
    def __init__(self,sexo,nivel):
        self.sexo = sexo
        self.nivel = nivel
class IUtiles:      
    def siguiente_manejador(self, handler) :
        self._next_handler = handler
        return handler

    @abstractmethod
    def obtenerLista(self, alumno) :
        if self._next_handler:
            return self._next_handler.obtenerLista(alumno)

        return None

class Nivel_1(IUtiles):
    def obtenerLista(self,alumno):
        if(alumno.sexo == 1 and alumno.nivel == 1):
            return "Zapatillas, buzo, soga de saltar"
        if(alumno.sexo == 0 and alumno.nivel == 1):
            return "Zapatillas, buzo, 6m de elástico"
        else:
            return self._next_handler.obtenerLista(alumno)
            
class Nivel_2(IUtiles):
    def obtenerLista(self,alumno):
        if(alumno.sexo == 1 and alumno.nivel == 2):
            return "Zapatillas, buzo, pelota de fútbol Nro. 4"
        if(alumno.sexo == 0 and alumno.nivel == 2):
            return "Zapatillas, buzo, pelota de voléybol Nro. 4"
        else:
            return self._next_handler.obtenerLista(alumno)

class Nivel_3(IUtiles):
    def obtenerLista(self,alumno):
        if(alumno.sexo == 1 and alumno.nivel == 3):
            return "Bate, pelota, guante"
        if(alumno.sexo == 0 and alumno.nivel == 3):
            return "Bate, pelota, guante"
        else:
            return self._next_handler.obtenerLista(alumno)

class Nivel_4(IUtiles):
    def obtenerLista(self,alumno):
        if(alumno.sexo == 1 and alumno.nivel == 4):
            return "Ropa de baño, gorro, goggles, chimpunes"
        if(alumno.sexo == 0 and alumno.nivel == 4):
            return "Ropa de baño, gorro, goggles, tutú"
        else:
            return self._next_handler.obtenerLista(alumno)

class Nivel_5(IUtiles):
    def obtenerLista(self,alumno):
        if(alumno.sexo == 1 and alumno.nivel == 5):
            return "Ropa de baño, gorro, goggles, chimpunes, skateboard"
        if(alumno.sexo == 0 and alumno.nivel == 5):
            return "Ropa de baño, gorro, goggles, stepper" 
        else:
            return self._next_handler.obtenerLista(alumno)                       


class App:

	def __init__(self):
		#configuracion de ventana
		self.ventana = tk.Tk()		
		self.ventana.title("GUI")
		self.ventana.geometry("460x200")		
		
		#variables         
		self.checkbuttonvar = tk.IntVar()
		self.nivel1 = Nivel_1()
		self.nivel2 = Nivel_2()
		self.nivel3 = Nivel_3()
		self.nivel4 = Nivel_4()
		self.nivel5 = Nivel_5()
		self.nivel1.siguiente_manejador(self.nivel2).siguiente_manejador(self.nivel3).siguiente_manejador(self.nivel4).siguiente_manejador(self.nivel5)
		self.alumno = Alumno(1,1)
		self.alumnosexo = 0

		#texto
		self.label = tk.Label(text="texto1")
		self.label.grid(row=0,column=0)

		self.cuadrotexto = st.ScrolledText(self.ventana,width=30, height=10)
		self.cuadrotexto.grid(row=1,column=0,rowspan=6)	
		self.cuadrotexto.insert('1.0',"Seleccione el sexo del alumno, luego su nivel.")
		#self.cuadrotexto.delete('1.0',tk.END)	
		#obtenertexto = self.cuadrotexto.get('1.0',tk.END)

		#boton		
		self.boton1 = tk.Button(self.ventana,text="Nivel 1", command=self.accion1 )
		self.boton1.grid(row=1,column=1)
		self.boton2 = tk.Button(self.ventana,text="Nivel 2", command=self.accion2 )
		self.boton2.grid(row=2,column=1)
		self.boton3 = tk.Button(self.ventana,text="Nivel 3", command=self.accion3 )
		self.boton3.grid(row=3,column=1)
		self.boton4 = tk.Button(self.ventana,text="Nivel 4 ", command=self.accion4 )
		self.boton4.grid(row=4,column=1)
		self.boton5 = tk.Button(self.ventana,text="Nivel 5", command=self.accion5 )
		self.boton5.grid(row=5,column=1)

		self.botonins = tk.Button(self.ventana,text="Instrucciones", command=self.ins )
		self.botonins.grid(row=3,column=2)

		self.varon = tk.Button(self.ventana,text="varón", command=self.varonact )
		self.varon.grid(row=2,column=2)
		self.mujer = tk.Button(self.ventana,text="mujer", command=self.mujeract )
		self.mujer.grid(row=4,column=2)

		#checkbutton
		#self.checkbutton1 = tk.Checkbutton(self.ventana,text="Checkbutton1", variable=self.checkbuttonvar,command=self.accion1)	
		#self.checkbutton1.grid(row=0,column=1)

		

		self.ventana.mainloop()
	
	#acciones para los botones	
	def ins(self):
		self.cuadrotexto.delete('1.0',tk.END)
		self.cuadrotexto.insert('1.0',"Seleccione el sexo del alumno, luego su nivel.")
        
	def varonact(self):
		self.alumnosexo = 1

	def mujeract(self):
		self.alumnosexo = 0    

	def accion1(self):
		self.cuadrotexto.delete('1.0',tk.END)
		self.alumno = Alumno(self.alumnosexo,1)
		self.cuadrotexto.insert('1.0',self.nivel1.obtenerLista(self.alumno))
		
	def accion2(self):
		self.cuadrotexto.delete('1.0',tk.END)
		self.alumno = Alumno(self.alumnosexo,2)
		self.cuadrotexto.insert('1.0',self.nivel1.obtenerLista(self.alumno))

	def accion3(self):
		self.cuadrotexto.delete('1.0',tk.END)
		self.alumno = Alumno(self.alumnosexo,3)
		self.cuadrotexto.insert('1.0',self.nivel1.obtenerLista(self.alumno))

	def accion4(self):
		self.cuadrotexto.delete('1.0',tk.END)
		self.alumno = Alumno(self.alumnosexo,4)
		self.cuadrotexto.insert('1.0',self.nivel1.obtenerLista(self.alumno))

	def accion5(self):
		self.cuadrotexto.delete('1.0',tk.END)
		self.alumno = Alumno(self.alumnosexo,5)
		self.cuadrotexto.insert('1.0',self.nivel1.obtenerLista(self.alumno))

App()