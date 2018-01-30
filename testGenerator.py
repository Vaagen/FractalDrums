import numpy as np
import matplotlib.pyplot as plt

def pause(message):
    print(message)
    programPause = raw_input("Press <ENTER> to continue...")

case =3
if case==0:
    Rxx=1
    Ryy=1
    Rxy=0
    Ryx=0
elif case==1:
    Rxx=0
    Ryy=0
    Rxy=-1
    Ryx=1
elif case==2:
    Rxx=-1
    Ryy=-1
    Rxy=0
    Ryx=0
else:
    Rxx=0
    Ryy=0
    Rxy=1
    Ryx=-1


delta=1
x0=3
y0=5

coords = np.zeros((8,2))
coords[0,0] = x0
coords[1,0] = x0+  Rxx*delta
coords[2,0] = x0+  Rxx*delta+Ryx*delta
coords[3,0] = x0+2*Rxx*delta+Ryx*delta
coords[4,0] = x0+2*Rxx*delta-Ryx*delta
coords[5,0] = x0+3*Rxx      -Ryx*delta
coords[6,0] = x0+3*Rxx
coords[7,0] = x0+4*Rxx

coords[0,1] = y0
coords[1,1] = y0          +  Rxy*delta
coords[2,1] = y0+Ryy*delta+  Rxy*delta
coords[3,1] = y0+Ryy*delta+2*Rxy*delta
coords[4,1] = y0-Ryy*delta+2*Rxy*delta
coords[5,1] = y0-Ryy*delta+3*Rxy*delta
coords[6,1] = y0          +3*Rxy*delta
coords[7,1] = y0          +4*Rxy*delta

fig =plt.figure()
ax = fig.add_subplot(111)
ax.plot(coords[:,0],coords[:,1])
plt.show(block=False)
pause('Showing plot.')
