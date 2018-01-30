import numpy as np
import matplotlib.pyplot as plt

def pause(message):
    print(message)
    programPause = raw_input("Press <ENTER> to continue...")


def generatorSingleStretch(coords, Ip0, Ip7, currentLevel, goalLevel):
    (x0,y0)=coords[Ip0,:]
    (x7,y7)=coords[Ip7,:]

    if   x0<x7  and y0==y7:
        delta=(x7-x0)/4
        Rxx=1
        Ryy=1
        Rxy=0
        Ryx=0
    elif x0==x7 and y0>y7:
        delta=(y0-y7)/4
        Rxx=0
        Ryy=0
        Rxy=-1
        Ryx=1
    elif x0>x7  and y0==y7:
        delta=(x0-x7)/4
        Rxx=-1
        Ryy=-1
        Rxy=0
        Ryx=0
    elif x0==x7 and y0<y7:
        delta=(y7-y0)/4
        Rxx=0
        Ryy=0
        Rxy=1
        Ryx=-1
    else:
        print('Error: Unexpected coordinates recieved in generator.')

    deltaIndex = (Ip7-Ip0)/7
    Ip1=Ip0+  deltaIndex
    Ip2=Ip0+2*deltaIndex
    Ip3=Ip0+3*deltaIndex
    Ip4=Ip0+4*deltaIndex
    Ip5=Ip0+5*deltaIndex
    Ip6=Ip0+6*deltaIndex

    coords[Ip1,0] = x0+  Rxx*delta
    coords[Ip2,0] = x0+  Rxx*delta+Ryx*delta
    coords[Ip3,0] = x0+2*Rxx*delta+Ryx*delta
    coords[Ip4,0] = x0+2*Rxx*delta-Ryx*delta
    coords[Ip5,0] = x0+3*Rxx*delta-Ryx*delta
    coords[Ip6,0] = x0+3*Rxx*delta

    coords[Ip1,1] = y0          +  Rxy*delta
    coords[Ip2,1] = y0+Ryy*delta+  Rxy*delta
    coords[Ip3,1] = y0+Ryy*delta+2*Rxy*delta
    coords[Ip4,1] = y0-Ryy*delta+2*Rxy*delta
    coords[Ip5,1] = y0-Ryy*delta+3*Rxy*delta
    coords[Ip6,1] = y0          +3*Rxy*delta

    if currentLevel < goalLevel:
        currentLevel+=1
        generator(coords,Ip0,Ip1,currentLevel,goalLevel,0)
        generator(coords,Ip1,Ip2,currentLevel,goalLevel,0)
        generator(coords,Ip2,Ip3,currentLevel,goalLevel,0)
        #generator(coords,Ip3,Ip4,currentLevel,goalLevel,1)
        generator(coords,Ip4,Ip5,currentLevel,goalLevel,0)
        generator(coords,Ip5,Ip6,currentLevel,goalLevel,0)
        generator(coords,Ip6,Ip7,currentLevel,goalLevel,0)

def generatorDoubleStretch(coords, Ip0, Ip7, currentLevel, goalLevel):
    print 'Empty'

def generator(coords, Ip0, Ip7, currentLevel, goalLevel,isDoubleStretch):
    if isDoubleStretch:
        generatorDoubleStretch(coords, Ip0, Ip7, currentLevel, goalLevel)
    else:
        generatorSingleStretch(coords, Ip0, Ip7, currentLevel, goalLevel)



coords = np.ones((50,2))
coords[0,:]=[0,5]
coords[49,:]=[100,5]
generator(coords,0,49,0,1,0)


fig =plt.figure()
ax = fig.add_subplot(111)
ax.plot(coords[:,0],coords[:,1])
plt.show(block=False)
pause('Showing plot.')
