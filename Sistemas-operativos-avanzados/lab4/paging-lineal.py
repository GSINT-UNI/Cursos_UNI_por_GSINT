#! /usr/bin/env python

from __future__ import print_function
import sys
from optparse import OptionParser
import random
import math

def mustbepowerof2(bits, size, msg):
    if math.pow(2,bits) != size:
        print('Error en el argumento: %s' % msg)
        sys.exit(1)

def mustbemultipleof(bignum, num, msg):
    if (int(float(bignum)/float(num)) != (int(bignum) / int(num))):
        print('Error en el argumento: %s' % msg)
        sys.exit(1)

def convert(size):
    length = len(size)
    lastchar = size[length-1]
    if (lastchar == 'k') or (lastchar == 'K'):
        m = 1024
        nsize = int(size[0:length-1]) * m
    elif (lastchar == 'm') or (lastchar == 'M'):
        m = 1024*1024
        nsize = int(size[0:length-1]) * m
    elif (lastchar == 'g') or (lastchar == 'G'):
        m = 1024*1024*1024
        nsize = int(size[0:length-1]) * m
    else:
        nsize = int(size)
    return nsize

# Programa principal

parser = OptionParser()
parser.add_option('-A', '--addresses', default='-1',help='a set of comma-separated pages to access; -1 means randomly generate', action='store', type='string', dest='addresses')
parser.add_option('-s', '--seed', default=0, help='the random seed', action='store', type='int', dest='seed')
parser.add_option('-a', '--asize', default='16k', help='address space size (e.g., 16, 64k, 32m, 1g)',   action='store', type='string', dest='asize')
parser.add_option('-p', '--physmem', default='64k', help='physical memory size (e.g., 16, 64k, 32m, 1g)', action='store', type='string', dest='psize')
parser.add_option('-P', '--pagesize', default='4k', help='page size (e.g., 4k, 8k, whatever)', action='store', type='string', dest='pagesize')
parser.add_option('-n', '--numaddrs', default=5,  help='number of virtual addresses to generate',       action='store', type='int', dest='num')
parser.add_option('-u', '--used', default=50, help='percent of virtual address space that is used', action='store', type='int', dest='used')
parser.add_option('-v', help='verbose mode', action='store_true', default=False, dest='verbose')
parser.add_option('-c', help='compute answers for me', action='store_true', default=False, dest='solve')

(options, args) = parser.parse_args()

print('Argument seed',               options.seed)
print('Argument address space size', options.asize)
print('Argument phys mem size',      options.psize)
print('Argument page size',          options.pagesize)
print('Argument verbose',            options.verbose)
print('Argument addresses',          options.addresses)
print('')

random.seed(options.seed)

asize    = convert(options.asize)
psize    = convert(options.psize)
pagesize = convert(options.pagesize)
addresses = str(options.addresses)

if psize <= 1:
    print('Error:debes especificar un size de memoria fisica que no sea cero.')
    exit(1)

if asize < 1:
    print('Error:debe especificar un size de memoria fisica que no sea cero.')
    exit(1)

if psize <= asize:
    print('Error: el size de la memoria fisica debe ser MAYOR que el size del espacio de direcciones (para esta simulacion).')
    exit(1)

if psize >= convert('1g') or asize >= convert('1g'):
    print('Error: debe usar sizes de menos de 1 GB para esta simulacion.')
    exit(1)

mustbemultipleof(asize, pagesize, 'el espacio de direcciones debe ser multiplo del size de pagina.')
mustbemultipleof(psize, pagesize, 'la memoria fisica debe ser multiplo del size de pagina.')

# Util info
pages = psize // pagesize;
import array
used = array.array('i')
pt   = array.array('i')
for i in range(0,pages):
    used.insert(i,0)
vpages = asize // pagesize

# Asignamos algunas paginas del VA

vabits   = int(math.log(float(asize))/math.log(2.0))
mustbepowerof2(vabits, asize, 'el espacio de direcciones debe ser potencia de 2')
pagebits = int(math.log(float(pagesize))/math.log(2.0))
mustbepowerof2(pagebits, pagesize, 'el size de pagina debe ser potencia de 2')
vpnbits  = vabits - pagebits
pagemask = (1 << pagebits) - 1

vpnmask = 0xFFFFFFFF & ~pagemask

print('')
print('El formato de la tabla de pagina es simple:')
print('El bit de orden superior es el bit VALIDO.')
print('Si el bit es 1, el restro de la entrada es el PFN.')
print('Si el bit es 0, la pagina no es valida.')
print('Usa (-v) si quieres imprimir el # VPN por ')
print('cada entrada de la tabla de pagina.')
print('')

print('Tabla de paginas (desde la entrada 0 hasta el max size)')
for v in range(0,vpages):
    done = 0
    while done == 0:
        if ((random.random() * 100.0) > (100.0 - float(options.used))):
            u = int(pages * random.random())
            if used[u] == 0:
                used[u] = 1
                done = 1
                if options.verbose == True:
                    print('  [%8d]  ' % v, end='')
                else:
                    print('  ', end='')
                print('0x%08x' % (0x80000000 | u))
                pt.insert(v,u)
        else:
            if options.verbose == True:
                print('  [%8d]  ' % v, end='')
            else:
                print('  ', end='')
            print('0x%08x' % 0)
            pt.insert(v,-1)
            done = 1
print(''  )

# Generamos seguimiento de la direccion virtual

addrList = []
if addresses == '-1':
    for i in range(0, options.num):
        n = int(asize * random.random())
        addrList.append(n)
else:
    addrList = addresses.split(',')


print('Seguimiento de direccion virtual')
for vStr in addrList:
    # vaddr = int(asize * random.random())
    vaddr = int(vStr)
    if options.solve == False:
        print('  VA 0x%08x (decimal: %8d) --> PA o direccion invalida?' % (vaddr, vaddr))
    else:
        paddr = 0
        # split vaddr en VPN | offset
        vpn = (vaddr & vpnmask) >> pagebits
        if pt[vpn] < 0:
            print('  VA 0x%08x (decimal: %8d) -->  Invalido (VPN %d no valido)' % (vaddr, vaddr, vpn))
        else:
            pfn    = pt[vpn]
            offset = vaddr & pagemask
            paddr  = (pfn << pagebits) | offset
            print('  VA 0x%08x (decimal: %8d) --> %08x (decimal %8d) [VPN %d]' % (vaddr, vaddr, paddr, paddr, vpn))
print('')

if options.solve == False:
    print('Para cada direccion virtual, escribe la dirección fisica a la que se traduce')
    print('O escribe que es una direccion fuera de los limites(ejemplo: segfault.')
    print('')







