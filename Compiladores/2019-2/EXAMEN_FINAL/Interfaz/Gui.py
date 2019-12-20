# -*- coding: utf-8 -*-
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from tkinter import scrolledtext
import sys, os


class App():
    def __init__(self):

        self.code = ''
        self.output = ''

        self.mainWindow = tk.Tk()
        self.mainWindow.title("Compiler GAA")
        self.mainWindow.geometry('900x650')
        
        s = ttk.Style()
        s.configure('W.TButton',background="#5AFF57", foreground="#047A00", font=("Arial Bold", 9))
        sLabel = ttk.Style()
        sLabel.configure('W.TLabel', foreground="#4070FF", font=("Arial Bold", 14))


        tab_control = ttk.Notebook(self.mainWindow)
        tab_main = ttk.Frame(tab_control)
        tab_help = ttk.Frame(tab_control)
        tab_credit = ttk.Frame(tab_control)
        tab_control.add(tab_main, text='Principal')
        tab_control.add(tab_help, text='Ayuda')
        tab_control.add(tab_credit, text='Creditos')

        self.frameCode = tk.Frame(tab_main)

        self.frameInput = tk.Frame(self.frameCode) 
        frameDescriptInput = tk.Frame(self.frameInput)
        lab_code = ttk.Label(frameDescriptInput, text='Editor', style='W.TLabel')
        lab_code.grid(row=0,sticky='W')
        saveCode = ttk.Button(frameDescriptInput, text='Guardar Codigo', command = self.saveCode, style = 'W.TButton')
        saveCode.grid(column=1, row=0,sticky='E',padx=100)
        compiler = ttk.Button(frameDescriptInput, text='Compilar', command = self.compilerCode, style = 'W.TButton')
        compiler.grid(column=2, row=0,padx=40)
        frameDescriptInput.grid(column=0, row=0, sticky='W',pady=5)
        self.spaceCode = scrolledtext.ScrolledText(self.frameInput,width=60,height=20)
        self.spaceCode.grid(column=0,row=1)
        self.frameInput.grid(column=0,row=0,sticky='W',padx=10)


        self.frameOutput = tk.Frame(self.frameCode)
        lab_output = ttk.Label(self.frameOutput, text='Salida Programa', style='W.TLabel')
        lab_output.grid(column=0,row=0,sticky='W')
        self.spaceOutput = scrolledtext.ScrolledText(self.frameOutput,width=40,height=20)
        self.spaceOutput.grid(column=0,row=1)
        self.frameOutput.grid(column=1,row=0)

        self.frameCode.grid(column=0, row=0,pady=10)


        self.frameTable = tk.Frame(tab_main)

        self.frameTableCode = tk.Frame(self.frameTable)
        fDesTableCode = tk.Frame(self.frameTableCode)
        lab_TableCode = ttk.Label(fDesTableCode, text='Tabla de Codigo', style='W.TLabel')
        lab_TableCode.grid(column=0,row=0,sticky='W')
        showTableCode = ttk.Button(fDesTableCode, text='Mostrar', command = self.showTableCode, style = 'W.TButton')
        showTableCode.grid(column=1, row=0,padx=90)
        fDesTableCode.grid(column=0, row=0)
        self.spaceTableCode = scrolledtext.ScrolledText(self.frameTableCode,width=50,height=12)
        self.spaceTableCode.grid(column=0,row=1)
        self.frameTableCode.grid(column=0,row=0,sticky='W',padx=10)

        self.frameTableSymbol = tk.Frame(self.frameTable)
        fDesTableSimbol = tk.Frame(self.frameTableSymbol)
        lab_TableSimbol = ttk.Label(fDesTableSimbol, text='Tabla de Simbolos', style='W.TLabel')
        lab_TableSimbol.grid(column=0,row=0,sticky='W')
        showTableSymbol = ttk.Button(fDesTableSimbol, text='Mostrar', command = self.showTableSymbol, style = 'W.TButton')
        showTableSymbol.grid(column=1, row=0, padx=90)
        fDesTableSimbol.grid(column=0,row=0)
        self.spaceTableSymbol = scrolledtext.ScrolledText(self.frameTableSymbol,width=50,height=12)
        self.spaceTableSymbol.grid(column=0,row=1)
        self.frameTableSymbol.grid(column=1,row=0,sticky='W',padx=10)

        self.frameTable.grid(column=0, row=1)
        #-----------------------------------------------------------------------------------

        #Mostrar salida
        f = open('ayuda_codigo.txt',"r")
        help_text = f.read()
        f.close()
        spaceAyuda = scrolledtext.ScrolledText(tab_help,width=120,height=40)
        spaceAyuda.insert(tk.INSERT, help_text)
        spaceAyuda.grid(column=0,row=0)
        
        #-----------------------------------------------------------------------------------
        #Mostrar salida
        f = open('creditos.txt',"r")
        creditos_text = f.read()
        f.close()
        spaceAyuda = scrolledtext.ScrolledText(tab_credit,width=120,height=40)
        spaceAyuda.insert(tk.INSERT, creditos_text)
        spaceAyuda.grid(column=0,row=0)

        tab_control.pack(expand=1, fill='both')
        self.mainWindow.mainloop()

    def saveCode(self):
        self.code = self.spaceCode.get("0.0", tk.END)
        #Guardar el codigo en un archivo code
        f = open("input.txt", "w")
        f.write(self.code)
        f.close()


    def showTableCode(self):
        self.spaceTableCode.delete(0.0, tk.END)
        init_tableCode = self.output.index('tabla de codigos')
        init_tableSymbol = self.output.index('tabla de simbolos')
        self.spaceTableCode.insert(tk.INSERT, self.output[init_tableCode:init_tableSymbol])
        

    def showTableSymbol(self):  
        self.spaceTableSymbol.delete(0.0, tk.END)
        init_tableSymbol = self.output.index('tabla de simbolos')
        self.spaceTableSymbol.insert(tk.INSERT, self.output[init_tableSymbol:])
    
    def showOutput(self):
        #Mostrar salida
        f = open('output.txt',"r")
        self.output=f.read()
        f.close()

        if 'ERROR' in self.output:
            #Mostra mensaje error
            messagebox.showerror('Error', 'Error en el codigo')
        
        else:
            self.spaceOutput.delete(0.0, tk.END)
            init_tableCode = self.output.index('tabla de codigos')
            self.spaceOutput.insert(tk.INSERT, self.output[:init_tableCode])

    def compilerCode(self):
        
        # Compilar - leer el archivo sh
        os.system("./prog < input.txt > output.txt")
        self.showOutput()


if __name__ == '__main__':
    Apx = App()