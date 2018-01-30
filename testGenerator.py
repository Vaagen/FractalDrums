import numpy as np
import matplotlib.pyplot as plt

def pause(message):
    print(message)
    programPause = raw_input("Press <ENTER> to continue...")

def generator(coords, Ip0, Ip7):
    (x0,y0)=coords[Ip0,:]
    (x7,y7)=coords[Ip7,:]

    if   x0<x7  and y0==y7:
        delta=(x7-x0)/4
        print delta
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
    coords[Ip0+  deltaIndex,0] = x0+  Rxx*delta
    coords[Ip0+2*deltaIndex,0] = x0+  Rxx*delta+Ryx*delta
    coords[Ip0+3*deltaIndex,0] = x0+2*Rxx*delta+Ryx*delta
    coords[Ip0+4*deltaIndex,0] = x0+2*Rxx*delta-Ryx*delta
    coords[Ip0+5*deltaIndex,0] = x0+3*Rxx*delta-Ryx*delta
    coords[Ip0+6*deltaIndex,0] = x0+3*Rxx*delta

    coords[Ip0+  deltaIndex,1] = y0          +  Rxy*delta
    coords[Ip0+2*deltaIndex,1] = y0+Ryy*delta+  Rxy*delta
    coords[Ip0+3*deltaIndex,1] = y0+Ryy*delta+2*Rxy*delta
    coords[Ip0+4*deltaIndex,1] = y0-Ryy*delta+2*Rxy*delta
    coords[Ip0+5*deltaIndex,1] = y0-Ryy*delta+3*Rxy*delta
    coords[Ip0+6*deltaIndex,1] = y0          +3*Rxy*delta



coords = np.zeros((8,2))
coords[0,:]=[1,2]
coords[7,:]=[8,2]
generator(coords,0,7)


fig =plt.figure()
ax = fig.add_subplot(111)
ax.plot(coords[:,0],coords[:,1])
plt.show(block=False)
pause('Showing plot.')
