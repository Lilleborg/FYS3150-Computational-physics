import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D

pos1 = np.genfromtxt("../build/positions1.txt")
pos2 = np.genfromtxt("../build/positions2.txt")
pos3 = np.genfromtxt("../build/positions3.txt")

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.plot(pos1[:,0], pos1[:,1], pos1[:,2], label='sun', marker="o")
ax.plot(pos2[:,0], pos2[:,1], pos2[:,2], label='Earth')
ax.plot(pos3[:,0], pos3[:,1], pos3[:,2], label='Jupiter')
#ax.plot(earth[0,0], earth[0,1], earth[0,2], marker="o", label ="earth starting point")
ax.legend()
plt.show()