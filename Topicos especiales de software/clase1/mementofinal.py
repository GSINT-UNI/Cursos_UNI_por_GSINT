import tkinter as tk

class Memento:

	def __init__(self,colour):
		self.colour = colour

	def getColor(self):
		return self.colour

class Guardian:
	def __init__(self):
		self.mementos=[]

	def save_memento(self,memento):
		self.mementos.append(memento)

	def pop_memento(self):
		return self.mementos.pop()



class Aplicacion:
#Funciones para cambio de color
	def red_en(self):
		meme = Memento('red')
		self.medivh.save_memento(meme)
		self.ventana1.configure(background=meme.colour)
		self.label1.configure(text="opcion seleccionada="+meme.colour)

	def green_en(self):
		meme = Memento('green')		
		self.medivh.save_memento(meme)
		self.ventana1.configure(background=meme.colour)
		self.label1.configure(text="opcion seleccionada="+meme.colour)

	def blue_en(self):
		meme = Memento('blue')
		self.medivh.save_memento(meme)
		self.ventana1.configure(background=meme.colour)
		self.label1.configure(text="opcion seleccionada="+meme.colour)

	def yellow_en(self):
		meme = Memento('yellow')
		self.medivh.save_memento(meme)
		self.ventana1.configure(background=meme.colour)
		self.label1.configure(text="opcion seleccionada="+meme.colour)

	def __init__(self):
		#Guardian de ctrlZ
		self.medivh = Guardian()
		#Guardian de ctrlY
		self.maiev = Guardian()

		self.current_colour=''
		#configura ventana
		self.ventana1=tk.Tk()
		self.ventana1.title("mementos: CtrlZ + CtrlY")
		self.ventana1.geometry("300x200")

		#variables de los botones
		self.seleccion1=tk.IntVar()
		self.seleccion2=tk.IntVar()
		self.seleccion3=tk.IntVar()
		self.seleccion4=tk.IntVar()
		
		#botones de los colores
		self.radio1=tk.Checkbutton(self.ventana1,text="red", variable=self.seleccion1,command=self.red_en)
		self.radio1.grid(column=1, row=0)

		self.radio2=tk.Checkbutton(self.ventana1,text="green", variable=self.seleccion2, command=self.green_en)
		self.radio2.grid(column=1, row=1)

		self.radio3=tk.Checkbutton(self.ventana1,text="blue", variable=self.seleccion3,command=self.blue_en)
		self.radio3.grid(column=1, row=2)

		self.radio4=tk.Checkbutton(self.ventana1,text="yellow", variable=self.seleccion4,command=self.yellow_en)
		self.radio4.grid(column=1, row=3)
		
		#botonesCtrlZ+CtrlY
		self.boton2=tk.Button(self.ventana1, text="Ctrl_Y", command=self.ctrly)
		self.boton2.grid(column=1, row=4)

		self.boton2=tk.Button(self.ventana1, text="Ctrl_Z", command=self.ctrlz)
		self.boton2.grid(column=1, row=5)

		self.label1=tk.Label(text="opcion seleccionada= "+self.current_colour)
		self.label1.grid(column=1, row=6)

		self.ventana1.mainloop()

	#aplicacion de ctrlZ
	def ctrlz(self):
		try:
			self.maiev.save_memento(self.medivh.pop_memento())
			self.label1.configure(text="opcion seleccionada="+self.medivh.mementos[-1].colour)
			self.ventana1.configure(background=self.medivh.mementos[-1].colour)
		
		except IndexError:
			self.ventana1.configure(background='SystemButtonFace')
	#aplicacion de ctrlY
	def ctrly(self):
		try:
			self.medivh.save_memento(self.maiev.pop_memento())
			self.label1.configure(text="opcion seleccionada="+self.medivh.mementos[-1].colour)
			self.ventana1.configure(background=self.medivh.mementos[-1].colour)
		
		except IndexError:
			pass

aplicacion1=Aplicacion()
