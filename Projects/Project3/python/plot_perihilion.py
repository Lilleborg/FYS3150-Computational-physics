import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

from matplotlib import rcParams
import sys

path = "../build/Verlet_perihelion/"
plotpos = False

angles = np.loadtxt(path+"perihelion.txt")
time = np.linspace(0,100,np.size(angles))

x = np.cos(angles) * 0.3075
y = np.sin(angles) * 0.3075
coeffs = np.polyfit(time,angles,1)
line = np.poly1d(coeffs)

# Plotting
font = {'size'   : 12}
plt.matplotlib.rc('font', **font)
rcParams.update({'figure.autolayout': True})

plt.figure()
plt.title("Position of periheilion")
plt.plot(x,y)

plt.ylabel("y [AU]")
plt.xlabel("x [AU]")
plt.tight_layout()
plt.savefig("plot_position_periangle.pdf")


plt.figure()
plt.title("Angle to perihelion")
plt.plot(time,angles, label = "Computed angles")
plt.plot(time,line(time), label= "Polyfit")
plt.ylabel("Perihelion angle [radians]")
plt.xlabel("Time [yr]")
plt.legend()
plt.tight_layout()
plt.savefig("plot_angle_vs_time.pdf")

print "max difference in angles ", np.max(angles)-np.min(angles)
print "Difference in polyfit ", line(time[-1])-line(time[0])  

if plotpos:
    mercury = np.loadtxt(path + "positions_Mercury.txt",unpack = True)
    sun = np.zeros(2)
    r_mercury = np.linalg.norm(mercury[:,0])

    plt.figure()
    plt.plot(x,y,label = "Perihelion point")
    plt.plot(sun[0],sun[1],'o',label="Sun")
    plt.plot(mercury[0],mercury[1],label="Mercury")
    plt.title("Perihelion precession of Mercury over a century")
    plt.ylabel("y [AU]")
    plt.xlabel("x [AU]")
    plt.legend(loc="best")
    plt.savefig("plot_perihelion_with_pos.pdf")
plt.show()