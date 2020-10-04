#! /usr/bin/env python

from __future__ import print_function
import sys
from optparse import OptionParser
import random

def random_seed(seed):
    try:
        random.seed(seed, version=1)
    except:
        random.seed(seed)
    return

# finds the highest nonempty queue
# -1 if they are all empty
def FindQueue():
    q = hiQueue
    while q > 0:
        if len(queue[q]) > 0:
            return q
        q -= 1
    if len(queue[0]) > 0:
        return 0
    return -1

def Abort(str):
    sys.stderr.write(str + '\n')
    exit(1)

#Parse arguments

parser = OptionParser()
parser.add_option('-s', '--seed', help='the random seed', 
                  default=0, action='store', type='int', dest='seed')
parser.add_option('-n', '--numQueues',
                  help='number of queues in MLFQ (if not using -Q)', 
                  default=3, action='store', type='int', dest='numQueues')
parser.add_option('-q', '--quantum', help='length of time slice (if not using -Q)',
                  default=10, action='store', type='int', dest='quantum')
parser.add_option('-a', '--allotment', help='length of allotment (if not using -A)',
                  default=1, action='store', type='int', dest='allotment')
parser.add_option('-Q', '--quantumList',
                  help='length of time slice per queue level, specified as ' + \
                  'x,y,z,... where x is the quantum length for the highest ' + \
                  'priority queue, y the next highest, and so forth', 
                  default='', action='store', type='string', dest='quantumList')
parser.add_option('-A', '--allotmentList',
                  help='length of time allotment per queue level, specified as ' + \
                  'x,y,z,... where x is the # of time slices for the highest ' + \
                  'priority queue, y the next highest, and so forth', 
                  default='', action='store', type='string', dest='allotmentList')
parser.add_option('-j', '--numJobs', default=3, help='number of jobs in the system',
                  action='store', type='int', dest='numJobs')
parser.add_option('-m', '--maxlen', default=100, help='max run-time of a job ' +
                  '(if randomly generating)', action='store', type='int',
                  dest='maxlen')
parser.add_option('-M', '--maxio', default=10,
                  help='max I/O frequency of a job (if randomly generating)',
                  action='store', type='int', dest='maxio')
parser.add_option('-B', '--boost', default=0,
                  help='how often to boost the priority of all jobs back to ' +
                  'high priority', action='store', type='int', dest='boost')
parser.add_option('-i', '--iotime', default=5,
                  help='how long an I/O should last (fixed constant)',
                  action='store', type='int', dest='ioTime')
parser.add_option('-S', '--stay', default=False,
                  help='reset and stay at same priority level when issuing I/O',
                  action='store_true', dest='stay')
parser.add_option('-I', '--iobump', default=False,
                  help='if specified, jobs that finished I/O move immediately ' + \
                  'to front of current queue',
                  action='store_true', dest='iobump')
parser.add_option('-l', '--jlist', default='',
                  help='a comma-separated list of jobs to run, in the form ' + \
                  'x1,y1,z1:x2,y2,z2:... where x is start time, y is run ' + \
                  'time, and z is how often the job issues an I/O request',
                  action='store', type='string', dest='jlist')
parser.add_option('-c', help='compute answers for me', action='store_true',
                  default=False, dest='solve')

(options, args) = parser.parse_args()

random.seed(options.seed)

# MLFQ: How Many Queues
numQueues = options.numQueues

quantum = {}
if options.quantumList != '':
    # instead, extract number of queues and their time slic
    quantumLengths = options.quantumList.split(',')
    numQueues = len(quantumLengths)
    qc = numQueues - 1
    for i in range(numQueues):
        quantum[qc] = int(quantumLengths[i])
        qc -= 1
else:
    for i in range(numQueues):
        quantum[i] = int(options.quantum)

allotment = {}
if options.allotmentList != '':
    allotmentLengths = options.allotmentList.split(',')
    if numQueues != len(allotmentLengths):
        print('number of allotments specified must match number of quantums')
        exit(1)
    qc = numQueues - 1
    for i in range(numQueues):
        allotment[qc] = int(allotmentLengths[i])
        if qc != 0 and allotment[qc] <= 0:
            print('allotment must be positive integer')
            exit(1)
        qc -= 1
else:
    for i in range(numQueues):
        allotment[i] = int(options.allotment)

hiQueue = numQueues - 1

# MLFQ: I/O Model
ioTime = int(options.ioTime)

# This tracks when IOs and other interrupts are complete
ioDone = {}

# This stores all info about the jobs
job = {}

# seed the random generator
random_seed(options.seed)

# jlist 'startTime,runTime,ioFreq:startTime,runTime,ioFreq:...'
jobCnt = 0
if options.jlist != '':
    allJobs = options.jlist.split(':')
    for j in allJobs:
        jobInfo = j.split(',')
        if len(jobInfo) != 3:
            print('Badly formatted job string. Should be x1,y1,z1:x2,y2,z2:...')
            print('where x is the startTime, y is the runTime, and z is the I/O frequency.')
            exit(1)
        assert(len(jobInfo) == 3)
        startTime = int(jobInfo[0])
        runTime   = int(jobInfo[1])
        ioFreq    = int(jobInfo[2])
        job[jobCnt] = {'currPri':hiQueue, 'ticksLeft':quantum[hiQueue],
                       'allotLeft':allotment[hiQueue], 'startTime':startTime,
                       'runTime':runTime, 'timeLeft':runTime, 'ioFreq':ioFreq, 'doingIO':False,
                       'firstRun':-1}
        if startTime not in ioDone:
            ioDone[startTime] = []
        ioDone[startTime].append((jobCnt, ' El trabajo inicia'))
        jobCnt += 1
else:
    # randomness
    for j in range(options.numJobs):
        startTime = 0
        runTime   = int(random.random() * (options.maxlen - 1) + 1)
        ioFreq    = int(random.random() * (options.maxio - 1) + 1)
        
        job[jobCnt] = {'currPri':hiQueue, 'ticksLeft':quantum[hiQueue],
                       'allotLeft':allotment[hiQueue], 'startTime':startTime,
                       'runTime':runTime, 'timeLeft':runTime, 'ioFreq':ioFreq, 'doingIO':False,
                       'firstRun':-1}
        if startTime not in ioDone:
            ioDone[startTime] = []
        ioDone[startTime].append((jobCnt, 'El trabajo inicia'))
        jobCnt += 1


numJobs = len(job)

print('Here is the list of inputs:')
print('Options jobs',            numJobs)
print('Options queues',          numQueues)
for i in range(len(quantum)-1,-1,-1):
    print('Options allotments for queue %2d is %3d' % (i, allotment[i]))
    print('Options quantum length for queue %2d is %3d' % (i, quantum[i]))
print('Options boost',           options.boost)
print('Options ioTime',          options.ioTime)
print('Options stayAfterIO',     options.stay)
print('Options iobump',          options.iobump)

print('\n')
print('For each job, three defining characteristics are given:')
print('  startTime : at what time does the job enter the system')
print('  runTime   : the total CPU time needed by the job to finish')
print('  ioFreq    : every ioFreq time units, the job issues an I/O')
print('              (the I/O takes ioTime units to complete)\n')

print('Job List:')
for i in range(numJobs):
    print('  Job %2d: startTime %3d - runTime %3d - ioFreq %3d' % (i, job[i]['startTime'], job[i]['runTime'], job[i]['ioFreq']))
print('')

if options.solve == False:
    print('Compute the execution trace for the given workloads.')
    print('If you would like, also compute the response and turnaround')
    print('times for each of the jobs.')
    print('')
    print('Use the -c flag to get the exact results when you are finished.\n')
    exit(0)

# Initialize the MLFQ queues
queue = {}
for q in range(numQueues):
    queue[q] = []

# Time is central 
currTime = 0

# Use these to know when we're finished
totalJobs    = len(job)
finishedJobs = 0

print('\nExecution Trace:\n')

while finishedJobs < totalJobs:
    # Find highest priority job
    # run it until either
    # (a) the job uses up its time quantum
    # (b) the job performs an I/O

    # check for priority boost
    if options.boost > 0 and currTime != 0:
        if currTime % options.boost == 0:
            print('[ time %d ] boost ( every %d )' % (currTime, options.boost))
            # Remove all jobs from queues (except high queue) and put them in high queue
            for q in range(numQueues-1):
                for j in queue[q]:
                    if job[j]['doingIO'] == False:
                        queue[hiQueue].append(j)
                queue[q] = []

            # Change priority to high priority
            # reset number of ticks left for all jobs (just for lower jobs?)
            # add to highest run queue (if not doing I/O)
            for j in range(numJobs):
                if job[j]['timeLeft'] > 0:
                    job[j]['currPri']   = hiQueue
                    job[j]['ticksLeft'] = allotment[hiQueue]

    # Check for any I/Os done
    if currTime in ioDone:
        for (j, type) in ioDone[currTime]:
            q = job[j]['currPri']
            job[j]['doingIO'] = False
            print('[ time %d ] %s by job %d' % (currTime, type, j))
            if options.iobump == False or type == 'Job begins':
                queue[q].append(j)
            else:
                queue[q].insert(0, j)

    # Now find the highest priority job
    currQueue = FindQueue()
    if currQueue == -1:
        print('[ time %d ] IDLE' % (currTime))
        currTime += 1
        continue
            
    # There was at least one runnable job, and hence ...
    currJob = queue[currQueue][0]
    if job[currJob]['currPri'] != currQueue:
        Abort('CurrPri[%d] does not match currQueue[%d]' % (job[currJob]['currPri'], currQueue))

    job[currJob]['timeLeft']  -= 1
    job[currJob]['ticksLeft'] -= 1

    if job[currJob]['firstRun'] == -1:
        job[currJob]['firstRun'] = currTime

    runTime   = job[currJob]['runTime']
    ioFreq    = job[currJob]['ioFreq']
    ticksLeft = job[currJob]['ticksLeft']
    allotLeft = job[currJob]['allotLeft']
    timeLeft  = job[currJob]['timeLeft']

    print('[ time %d ] Run JOB %d at priority %d [ticks %d allot %d time %d (of %d) ]' % \
          (currTime, currJob, currQueue, ticksLeft, allotLeft, timeLeft, runTime))

    if timeLeft < 0:
        Abort('Error: should never have less than 0 time left to run')


    # Update time
    currTime += 1

    # Check for job ending
    if timeLeft == 0:
        print('[ time %d ] finished job %d' % (currTime, currJob))
        finishedJobs += 1
        job[currJob]['endTime'] = currTime
        # print('BEFORE POP', queue)
        done = queue[currQueue].pop(0)
        # print('AFTER POP', queue)
        assert(done == currJob)
        continue

    # Check for IO
    issuedIO = False
    if ioFreq > 0 and (((runTime - timeLeft) % ioFreq) == 0):
        # Time for an IO!
        print('[ time %d ] IO_START by job %d' % (currTime, currJob))
        issuedIO = True
        desched = queue[currQueue].pop(0)
        assert(desched == currJob)
        job[currJob]['doingIO'] = True
        # This does the bad rule -- reset your tick counter if you stay at the same level
        if options.stay == True:
            job[currJob]['ticksLeft'] = quantum[currQueue]
            job[currJob]['allotLeft'] = allotment[currQueue]
        # Add to IO Queue: but which queue?
        futureTime = currTime + ioTime
        if futureTime not in ioDone:
            ioDone[futureTime] = []
        print('IO DONE')
        ioDone[futureTime].append((currJob, 'IO_DONE'))
        
    # Check for quantum ending at this level(but, there still may be allotment left)
    if ticksLeft == 0:
        if issuedIO == False:
            # IO has not been issued (therefor pop from queue)'
            desched = queue[currQueue].pop(0)
        assert(desched == currJob)

        job[currJob]['allotLeft'] = job[currJob]['allotLeft'] - 1

        if job[currJob]['allotLeft'] == 0:
            # This job is DONE at this level, so move on
            if currQueue > 0:
                # In this case, have to change the priority of the job
                job[currJob]['currPri']   = currQueue - 1
                job[currJob]['ticksLeft'] = quantum[currQueue-1]
                job[currJob]['allotLeft'] = allotment[currQueue-1]
                if issuedIO == False:
                    queue[currQueue-1].append(currJob)
            else:
                job[currJob]['ticksLeft'] = quantum[currQueue]
                job[currJob]['allotLeft'] = allotment[currQueue]
                if issuedIO == False:
                    queue[currQueue].append(currJob)
        else:
            # This job has more time at this level, so just push it to end
            job[currJob]['ticksLeft'] = quantum[currQueue]
            if issuedIO == False:
                queue[currQueue].append(currJob)
        
# Print out statistics
print('')
print('Final statistics:')
responseSum   = 0
turnaroundSum = 0
for i in range(numJobs):
    response   = job[i]['firstRun'] - job[i]['startTime']
    turnaround = job[i]['endTime'] - job[i]['startTime']
    print('  Job %2d: startTime %3d - response %3d - turnaround %3d' % (i, job[i]['startTime'], response, turnaround))
    responseSum   += response
    turnaroundSum += turnaround

print('\n  Avg %2d: startTime n/a - response %.2f - turnaround %.2f' % (i, float(responseSum)/numJobs, float(turnaroundSum)/numJobs))
print('\n')
