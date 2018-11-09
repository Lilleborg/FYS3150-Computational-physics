import numpy as np 
import matplotlib.pyplot as plt 

path = "../build/txtfiles/"

energies = np.fromfile("../build2/energies_energies_2.400000.bin")
print energies.shape
#energy = np.loadtxt(path+"energy_temp.txt")

plt.plot(energies)
plt.show()