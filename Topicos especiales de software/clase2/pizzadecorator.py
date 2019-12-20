from tkinter import *

class Pizza(object):	
	def get_price(self):
		pass
	
class BaseJamon(Pizza):	
	def get_price(self):
		return 10

class Base2(Pizza):
	def get_price(self):
		return 15

class Base3(Pizza):
	def get_price(self):
		return 13

class AbstractDecorator(Pizza):	
	def __init__(self,decorated_pizza):
		self._decorated_pizza = decorated_pizza	

	def get_price(self):
		self._decorated_pizza.get_price()

class Chorizo(AbstractDecorator):
	def __init__(self,decorated_pizza):
		AbstractDecorator.__init__(self,decorated_pizza)

	def get_price(self):
		return self._decorated_pizza.get_price() + 2

class Jalapeño(AbstractDecorator):
	def __init__(self,decorated_pizza):
		AbstractDecorator.__init__(self,decorated_pizza)

	def get_price(self):
		return self._decorated_pizza.get_price() + 3

class Queso(AbstractDecorator):
	def __init__(self,decorated_pizza):
		AbstractDecorator.__init__(self,decorated_pizza)

	def get_price(self):
		return self._decorated_pizza.get_price() + 4
		
class Pepperoni(AbstractDecorator):
	def __init__(self,decorated_pizza):
		AbstractDecorator.__init__(self,decorated_pizza)

	def get_price(self):
		return self._decorated_pizza.get_price() + 1
		
class Piña(AbstractDecorator):
	def __init__(self,decorated_pizza):
		AbstractDecorator.__init__(self,decorated_pizza)

	def get_price(self):
		return self._decorated_pizza.get_price() + 0.5

class Descuento(AbstractDecorator):
	def __init__(self,decorated_pizza):
		AbstractDecorator.__init__(self,decorated_pizza)

	def get_price(self):
		return self._decorated_pizza.get_price() * 0.2

class App:

	def __init__(self):
		#configuracion de ventana
		self.ventana = Tk()		
		self.ventana.title("Pizza: Decorator")
		self.ventana.geometry("250x150")		
		
		#variables para los botones
		self.chorizobuttonvar = IntVar()
		self.jalapenobuttonvar = IntVar()
		self.quesobuttonvar = IntVar()
		self.pepperonibuttonvar = IntVar()
		self.pinabuttonvar = IntVar()		

		#botones para el cambio de precio
		self.chorizobutton = Checkbutton(self.ventana,text="chorizo", variable=self.chorizobuttonvar,command=self.chorizoaction)
		self.chorizobutton.grid(row=0)
		
		self.jalapenobutton = Checkbutton(self.ventana,text="jalapeno", variable=self.jalapenobuttonvar,command=self.jalapenoaction)
		self.jalapenobutton.grid(row=1)
		
		self.quesobutton = Checkbutton(self.ventana,text="queso", variable=self.quesobuttonvar,command=self.quesoaction)
		self.quesobutton.grid(row=2)
		
		self.pepperonibutton = Checkbutton(self.ventana,text="pepperoni", variable=self.pepperonibuttonvar,command=self.pepperoniaction)
		self.pepperonibutton.grid(row=3)
		
		self.pinabutton = Checkbutton(self.ventana,text="pina", variable=self.pinabuttonvar,command=self.pinaaction)
		self.pinabutton.grid(row=4)
		
		#botones para Crear pizza, precio
		self.buttonz = Button(self.ventana, text="Crear Pizza", command=self.CREAR)
		self.buttonz.grid(row=1,column=2)
		self.buttony = Button(self.ventana, text="Precio", command=self.precio)
		self.buttony.grid(row=2,column=2)
		
		#texto precio total
		self.label = Label(text="Precio total"  )
		self.label.grid(row=3,column=2)
		
		self.ventana.mainloop()
	
	#acciones para los botones	
	
	def chorizoaction(self):		
		try:
			self.la_pizza = Chorizo(self.la_pizza)
			self.label.configure(text="Precio total = " + str( self.la_pizza.get_price() ) )			
		except AttributeError:
			self.label.configure(text="Crea una pizza primero."  )

	def jalapenoaction(self):		
		try:
			self.la_pizza = Jalapeño(self.la_pizza)	
			self.label.configure(text="Precio total = " + str( self.la_pizza.get_price() ) )			
		except AttributeError:
			self.label.configure(text="Crea una pizza primero."  )

	def quesoaction(self):
		try:
			self.la_pizza = Queso(self.la_pizza)
			self.label.configure(text="Precio total = " + str( self.la_pizza.get_price() ) )			
		except AttributeError:
			self.label.configure(text="Crea una pizza primero."  )

	def pepperoniaction(self):		
		try:
			self.la_pizza = Pepperoni(self.la_pizza)
			self.label.configure(text="Precio total = " + str( self.la_pizza.get_price() ) )			
		except AttributeError:
			self.label.configure(text="Crea una pizza primero."  )

	def pinaaction(self):		
		try:
			self.la_pizza = Piña(self.la_pizza)
			self.label.configure(text="Precio total = " + str( self.la_pizza.get_price() ) )			
		except AttributeError:
			self.label.configure(text="Crea una pizza primero."  )
			
	def CREAR(self):
		self.la_pizza = BaseJamon()
					
	def precio(self):		
		try:
			self.label.configure(text="Precio total = " + str( self.la_pizza.get_price() ) )			
		except AttributeError:
			self.label.configure(text="Crea una pizza primero."  )


App()

