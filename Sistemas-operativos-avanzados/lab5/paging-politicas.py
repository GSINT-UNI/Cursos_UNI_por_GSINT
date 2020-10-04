#! /usr/bin/env python

from __future__ import print_function
import sys
from optparse import OptionParser
import random
import math

def random_seed(seed):
    try:
        random.seed(seed, version=1)
    except:
        random.seed(seed)
    return

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

def hfunc(index):
    if index == -1:
        return 'MISS'
    else:
        return 'HIT '

def vfunc(victim):
    if victim == -1:
        return '-'
    else:
        return str(victim)

#
# main program
#
parser = OptionParser()
parser.add_option('-a', '--addresses', default='-1',help='a set of comma-separated pages to access; -1 means randomly generate',action='store', type='string', dest='addresses')
parser.add_option('-f', '--addressfile', default='',help='a file with a bunch of addresses in it',action='store', type='string', dest='addressfile')
parser.add_option('-n', '--numaddrs', default='10',help='if -a (--addresses) is -1, this is the number of addrs to generate', action='store', type='string', dest='numaddrs')
parser.add_option('-p', '--policy', default='FIFO',help='replacement policy: FIFO, LRU, OPT, UNOPT, RAND, CLOCK',action='store', type='string', dest='policy')
parser.add_option('-b', '--clockbits', default=2,  help='for CLOCK policy, how many clock bits to use',action='store', type='int', dest='clockbits')
parser.add_option('-C', '--cachesize', default='3',help='size of the page cache, in pages', action='store', type='string', dest='cachesize')
parser.add_option('-m', '--maxpage', default='10', help='if randomly generating page accesses, this is the max page number',     action='store', type='string', dest='maxpage')
parser.add_option('-s', '--seed', default='0',  help='random number seed', action='store', type='string', dest='seed')
parser.add_option('-N', '--notrace', default=False, help='do not print out a detailed trace', action='store_true', dest='notrace')
parser.add_option('-c', '--compute', default=False, help='compute answers for me', action='store_true', dest='solve')

(options, args) = parser.parse_args()

print('Argument addresses', options.addresses)
print('Argument addressfile', options.addressfile)
print('Argument numaddrs', options.numaddrs)
print('Argument policy', options.policy)
print('Argument clockbits', options.clockbits)
print('Argument cachesize', options.cachesize)
print('Argument maxpage', options.maxpage)
print('Argument seed', options.seed)
print('Argument notrace', options.notrace)
print('')

addresses   = str(options.addresses)
addressFile = str(options.addressfile)
numaddrs    = int(options.numaddrs)
cachesize   = int(options.cachesize)
seed        = int(options.seed)
maxpage     = int(options.maxpage)
policy      = str(options.policy)
notrace     = options.notrace
clockbits   = int(options.clockbits)

random_seed(seed)

addrList = []
if addressFile != '':
    fd = open(addressFile)
    for line in fd:
        addrList.append(int(line))
    fd.close()
else:
    if addresses == '-1':
        for i in range(0,numaddrs):
            n = int(maxpage * random.random())
            addrList.append(n)
    else:
        addrList = addresses.split(',')

if options.solve == False:
    print('Asumiendo una politica de reemplazo de %s, y un cache de %d paginas,' % (policy, cachesize))
    print('averigua si cada una de las referencias de páginas es un acierto o falla')
    print('en el cache de la pagina.\n')

    for n in addrList:
        print('Acceso: %d  Acierto/Fallo? Estado de memoria?' % int(n))
    print('')

else:
    if notrace == False:
        print('Resolviendo...\n')

    count = 0
    memory = []
    hits = 0
    miss = 0

    if policy == 'FIFO':
        leftStr = 'FirstIn'
        riteStr = 'Lastin '
    elif policy == 'LRU':
        leftStr = 'LRU'
        riteStr = 'MRU'
    elif policy == 'MRU':
        leftStr = 'LRU'
        riteStr = 'MRU'
    elif policy == 'OPT' or policy == 'RAND' or policy == 'UNOPT' or policy == 'CLOCK':
        leftStr = 'Left '
        riteStr = 'Right'
    else:
        print('Politica %s todavia no implementada' % policy)
        exit(1)

    ref   = {}

    cdebug = False

    addrIndex = 0
    for nStr in addrList:
        n = int(nStr)
        try:
            idx = memory.index(n)
            hits = hits + 1
            if policy == 'LRU' or policy == 'MRU':
                update = memory.remove(n)
                memory.append(n) 
        except:
            idx = -1
            miss = miss + 1

        victim = -1        
        if idx == -1:
            if count == cachesize:
                if policy == 'FIFO' or policy == 'LRU':
                    victim = memory.pop(0)
                elif policy == 'MRU':
                    victim = memory.pop(count-1)
                elif policy == 'RAND':
                    victim = memory.pop(int(random.random() * count))
                elif policy == 'CLOCK':
                    if cdebug:
                        print('Referencia a una pagina', n)
                        print('Memoria ', memory)
                        print('REF (b)', ref)

                    victim = -1
                    while victim == -1:
                        page = memory[int(random.random() * count)]
                        if cdebug:
                            print('Escanear pagina:', page, ref[page])
                        if ref[page] >= 1:
                            ref[page] -= 1
                        else:
                            # esta es nuestra victima 
                            victim = page
                            memory.remove(page)
                            break

                    if page in memory:
                        assert('BROKEN')
                    del ref[victim]
                    if cdebug:
                        print('VICTIMA', page)
                        print('LEN', len(memory))
                        print('MEM', memory)
                        print('REF (a)', ref)

                elif policy == 'OPT':
                    maxReplace  = -1
                    replaceIdx  = -1
                    replacePage = -1
                    for pageIndex in range(0,count):
                        page = memory[pageIndex]
                        whenReferenced = len(addrList)
                        for futureIdx in range(addrIndex+1,len(addrList)):
                            futurePage = int(addrList[futureIdx])
                            if page == futurePage:
                                whenReferenced = futureIdx
                                break
                        if whenReferenced >= maxReplace:
                            replaceIdx  = pageIndex
                            replacePage = page
                            maxReplace  = whenReferenced
                    victim = memory.pop(replaceIdx)
                elif policy == 'UNOPT':
                    minReplace  = len(addrList) + 1
                    replaceIdx  = -1
                    replacePage = -1
                    for pageIndex in range(0,count):
                        page = memory[pageIndex]
                        whenReferenced = len(addrList)
                        for futureIdx in range(addrIndex+1,len(addrList)):
                            futurePage = int(addrList[futureIdx])
                            if page == futurePage:
                                whenReferenced = futureIdx
                                break
                        if whenReferenced < minReplace:
                            replaceIdx  = pageIndex
                            replacePage = page
                            minReplace  = whenReferenced
                    victim = memory.pop(replaceIdx)
            else:
                victim = -1
                count = count + 1

            memory.append(n)
            if cdebug:
                print('LEN (a)', len(memory))
            if victim != -1:
                assert(victim not in memory)

        if n not in ref:
            ref[n] = 1
        else:
            ref[n] += 1
            if ref[n] > clockbits:
                ref[n] = clockbits
        
        if cdebug:
            print('REF (a)', ref)

        if notrace == False:
            print('Acceso: %d  %s %s -> %12s <- %s Reemplazado:%s [Hits:%d Misses:%d]' % (n, hfunc(idx), leftStr, memory, riteStr, vfunc(victim), hits, miss))
        addrIndex = addrIndex + 1
        
    print('')
    print('Estadisticas hits %d misses %d  tasa_hit %.2f' % (hits, miss, (100.0*float(hits))/(float(hits)+float(miss))))
    print('')



    
    
    







