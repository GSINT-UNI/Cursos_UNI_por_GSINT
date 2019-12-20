import tkinter as tk

class Puerta:

    def __init__(self):
        self.estado = Estado_Cerrar()

    def abrir(self): 
        if self.estado.abrir():
            mi_estado = self.estado.abrir()
            self.estado = Estado_Abrir() 
            return mi_estado

        return False    

    def cerrar(self):        
        if self.estado.cerrar():
            mi_estado = self.estado.cerrar()
            self.estado = Estado_Cerrar() 
            return mi_estado

        return False 

    def armar(self):
        if self.estado.armar():
            mi_estado = self.estado.armar()
            self.estado = Estado_Armar() 
            return mi_estado

        return False    

    def desarmar(self):
        if self.estado.desarmar():
            mi_estado = self.estado.desarmar()            
            self.estado = Estado_Desarmar() 
            return mi_estado

        
        return False

    def reparar(self):
        if self.estado.reparar():
            mi_estado = self.estado.reparar()            
            self.estado = Estado_Cerrar() 
            return mi_estado

        return False


    def test(self):
        if self.estado.test():
            mi_estado = self.estado.test()            
            self.estado = Estado_Test() 
            return mi_estado

        return False

    def end_test(self):
        if self.estado.end_test():
            mi_estado = self.estado.cerrar()            
            self.estado = Estado_Cerrar() 
            return mi_estado

        return False                     


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
        return False

    def end_test(self):
        return False     


class Estado_Abrir(Estado_abstracto):
    def abrir(self): 
        return False

    def cerrar(self):        
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

class Estado_Cerrar(Estado_abstracto):
    def abrir(self): 
        return True

    def cerrar(self):        
        return False

    def armar(self):
        return True

    def desarmar(self):
        return False

    def reparar(self):
        return False

    def test(self):
        return False

    def end_test(self):
        return False


class Estado_Armar(Estado_abstracto):
    def abrir(self): 
        return True

    def cerrar(self):        
        return True

    def armar(self):
        return False

    def desarmar(self):
        return True

    def reparar(self):
        return False

    def test(self):
        return False

    def end_test(self):
        return False


class Estado_Desarmar(Estado_abstracto):
    def abrir(self): 
        return False

    def cerrar(self):        
        return False

    def armar(self):
        return False

    def desarmar(self):
        return False

    def reparar(self):
        return True

    def test(self):
        return False

    def end_test(self):
        return False


class Estado_Test(Estado_abstracto):
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
        return True



class Aplicacion:
    def __init__(self):

        self.backdoor = Puerta()
        self.ventana1=tk.Tk()
        self.ventana1.title("Controles Button y Label")
        

        self.label1=tk.Label(self.ventana1, text="Estado:")
        self.label1.grid(column=0, row=0)
        self.label1.configure(foreground="red")

        self.label2=tk.Label(self.ventana1, text="Cerrado")
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
        new_State = self.backdoor.abrir()
        if new_State:
            self.label2.configure(text="Abierto")

    def cerrar(self):
        new_State = self.backdoor.cerrar()
        if new_State:
            self.label2.configure(text="Cerrado")


    def armar(self):
        new_State = self.backdoor.armar()
        if new_State:
            self.label2.configure(text="Abierto")

    def desarmar(self):
        new_State = self.backdoor.desarmar()
        if new_State:
            self.label2.configure(text="Desarmado")

    def reparar(self):
        new_State = self.backdoor.reparar()
        if new_State:
            self.label2.configure(text="Cerrado")

    def test(self):
        new_State = self.backdoor.test()
        if new_State:
            self.label2.configure(text="Testeando")

    def end_test(self):
        new_State = self.backdoor.end_test()
        if new_State:
            self.label2.configure(text="Cerrado")                        



aplicacion1=Aplicacion()