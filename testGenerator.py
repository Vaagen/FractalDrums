import numpy as np
import matplotlib.pyplot as plt

def pause(message):
    print(message)
    programPause = raw_input("Press <ENTER> to continue...")


def generator(coords, Ip0, Ip8, currentLevel, goalLevel):
    (x0,y0)=coords[Ip0,:]
    (x8,y8)=coords[Ip8,:]

    if   x0<x8  and y0==y8:
        delta=(x8-x0)/4
        Rxx=1
        Ryy=1
        Rxy=0
        Ryx=0
    elif x0==x8 and y0>y8:
        delta=(y0-y8)/4
        Rxx=0
        Ryy=0
        Rxy=-1
        Ryx=1
    elif x0>x8  and y0==y8:
        delta=(x0-x8)/4
        Rxx=-1
        Ryy=-1
        Rxy=0
        Ryx=0
    elif x0==x8 and y0<y8:
        delta=(y8-y0)/4
        Rxx=0
        Ryy=0
        Rxy=1
        Ryx=-1
    else:
        print('Error: Unexpected coordinates recieved in generator.')

    deltaIndex = (Ip8-Ip0)/8
    Ip1=Ip0+  deltaIndex
    Ip2=Ip0+2*deltaIndex
    Ip3=Ip0+3*deltaIndex
    Ip4=Ip0+4*deltaIndex
    Ip5=Ip0+5*deltaIndex
    Ip6=Ip0+6*deltaIndex
    Ip7=Ip0+7*deltaIndex

    coords[Ip1,0] = x0+  Rxx*delta
    coords[Ip2,0] = x0+  Rxx*delta+Ryx*delta
    coords[Ip3,0] = x0+2*Rxx*delta+Ryx*delta
    coords[Ip4,0] = x0+2*Rxx*delta
    coords[Ip5,0] = x0+2*Rxx*delta-Ryx*delta
    coords[Ip6,0] = x0+3*Rxx*delta-Ryx*delta
    coords[Ip7,0] = x0+3*Rxx*delta

    coords[Ip1,1] = y0          +  Rxy*delta
    coords[Ip2,1] = y0+Ryy*delta+  Rxy*delta
    coords[Ip3,1] = y0+Ryy*delta+2*Rxy*delta
    coords[Ip4,1] = y0          +2*Rxy*delta
    coords[Ip5,1] = y0-Ryy*delta+2*Rxy*delta
    coords[Ip6,1] = y0-Ryy*delta+3*Rxy*delta
    coords[Ip7,1] = y0          +3*Rxy*delta

    if currentLevel < goalLevel:
        currentLevel+=1
        generator(coords,Ip0,Ip1,currentLevel,goalLevel)
        generator(coords,Ip1,Ip2,currentLevel,goalLevel)
        generator(coords,Ip2,Ip3,currentLevel,goalLevel)
        generator(coords,Ip3,Ip4,currentLevel,goalLevel)
        generator(coords,Ip4,Ip5,currentLevel,goalLevel)
        generator(coords,Ip5,Ip6,currentLevel,goalLevel)
        generator(coords,Ip6,Ip7,currentLevel,goalLevel)
        generator(coords,Ip7,Ip8,currentLevel,goalLevel)

def genCoords(x0,y0,x1, goalLevel):
    # Generates coordinates for corners along horizontal line from (x0,y0) to (x1,y0)
    coords = np.zeros((8**goalLevel+1,2))
    coords[0,:]=[x0,y0]
    coords[8**goalLevel,:]=[x1,y0]
    generator(coords,0,8**goalLevel,1,goalLevel)
    return coords

def plotSquare(handle, coords):
    handle.plot(coords[:,0],coords[:,1])
    handle.plot(coords[:,1]+coords[-1,0]-coords[-1,1],-coords[:,0]+coords[-1,1])
    handle.plot(-coords[:,0]+coords[-1,0],-coords[:,1]+2*coords[-1,1]-coords[-1,0])
    handle.plot(-coords[:,1]+coords[-1,1],coords[:,0]-coords[-1,0]+coords[-1,1])

def getSquareCoords(coords):
    vec2 = np.array([coords[:,1]+coords[-1,0]-coords[-1,1],-coords[:,0]+coords[-1,1]])
    vec3 =np.array([-coords[:,0]+coords[-1,0],-coords[:,1]+2*coords[-1,1]-coords[-1,0]])
    vec4 =np.array([-coords[:,1]+coords[-1,1],coords[:,0]-coords[-1,0]+coords[-1,1]])
    vec2 = np.transpose(vec2)
    vec3 = np.transpose(vec3)
    vec4 = np.transpose(vec4)
    return np.row_stack((coords,vec2,vec3,vec4))

def rotateCoords45deg(coords):
    temp = 1./np.sqrt(2.)*(coords[:,0]+coords[:,1])
    coords[:,1] = 1./np.sqrt(2.)*(coords[:,1]-coords[:,0])
    coords[:,0] = temp

def rotateCoords(coords,angle):
    angle = angle*np.pi/180.
    temp = np.cos(angle)*coords[:,0]+np.sin(angle)*coords[:,1]
    coords[:,1] = np.cos(angle)*coords[:,1]-np.sin(angle)*coords[:,0]
    coords[:,0] = temp


fig =plt.figure()

coords = genCoords(0,0,100,5)



plt.show(block=False)
pause('Showing plot.')
