
from tkinter import *

class Memento:

	def __init__(self,color):
		self.color = color
		
	def getcolor(self):
		return self.color
		
class Guardian:

	def __init__(self):
		self.state=[]
		
	def save_state(self,memento):
		self.state.append(memento)
		
	def	pop_state(self):
		return self.state.pop()

class tarea:
	
	def __init__(self):
	
		#configuracion de ventana
		self.ventana=Tk()		
		self.ventana.title("mementos: CtrlZ + CtrlY")
		self.ventana.geometry("400x200")
		self.bg_color=''
		
		#variables para los botones
		self.redbuttonvar = IntVar()
		self.greenbuttonvar = IntVar()
		self.bluebuttonvar = IntVar()
		
		#Guardian de ctrlz
		self.guardianZ = Guardian()
		#Guardian de ctrly
		self.guardianY = Guardian()
		
		#botones para el cambio de color
		self.redbutton = Checkbutton(self.ventana,text="red", variable=self.redbuttonvar,command=self.redbuttonaction)
		self.redbutton.grid(row=0)
		self.greenbutton = Checkbutton(self.ventana,text="green", variable=self.greenbuttonvar,command=self.greenbuttonaction)
		self.greenbutton.grid(row=1)
		self.bluebutton = Checkbutton(self.ventana,text="blue", variable=self.bluebuttonvar,command=self.bluebuttonaction)
		self.bluebutton.grid(row=2)
		
		#botones para CtrlZ. CtrlY
		self.buttonz = Button(self.ventana, text="CtrlZ", command=self.ctrlz)
		self.buttonz.grid(row=3)
		self.buttony = Button(self.ventana, text="CtrlY", command=self.ctrly)
		self.buttony.grid(row=4)
		
		#texto nombre del color
		self.label = Label(text="COLOR = " + self.bg_color)
		self.buttony.grid(row=5)
		
		self.ventana.mainloop()
	
	#acciones para los botones	
	def redbuttonaction(self):
	
		estado = Memento('red')
		self.guardianZ.save_state(estado)
		self.ventana.configure(background=estado.color)
		self.label.configure(text="COLOR = " + self.bg_color)
		
	def greenbuttonaction(self):
	
		estado = Memento('green')
		self.guardianZ.save_state(estado)
		self.ventana.configure(background=estado.color)
		self.label.configure(text="COLOR = " + self.bg_color)
		
	def bluebuttonaction(self):
	
		estado = Memento('blue')
		self.guardianZ.save_state(estado)
		self.ventana.configure(background=estado.color)
		self.label.configure(text="COLOR = " + self.bg_color)
		
	def ctrlz(self):
		try:
			self.guardianY.save_state(self.guardianZ.pop_state())
			self.label.configure(text="COLOR = " + self.guardianZ.state[-1].color)
			self.ventana.configure(background=self.guardianZ.state[-1].color)
		except IndexError:
			self.ventana.configure(background='#F0F0F0')
			
	def ctrly(self):
		try:
			self.guardianZ.save_state(self.guardianY.pop_state())
			self.label.configure(text="COLOR = " + self.guardianZ.state[-1].color)
			self.ventana.configure(background=self.guardianZ.state[-1].color)
		except IndexError:
			pass

tarea()

