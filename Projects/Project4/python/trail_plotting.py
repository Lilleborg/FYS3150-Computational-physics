import numpy as np 
import matplotlib.pyplot as plt 

path = "../build/txtfiles/"

energy = np.loadtxt(path+"energy_temp.txt")

plt.plot(energy)
plt.show()