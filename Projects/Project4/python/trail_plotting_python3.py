import numpy as np 
import matplotlib.pyplot as plt 
from math import sinh,exp

#path = "../build/txtfiles/"
T = 1.
B = 1/T
Z = 2*exp(-8.*B)+2*exp(8.*B)+12
E_exp = -32./Z*sinh(8.*B)
print(E_exp)

energies = np.fromfile("../build/energies_energies_1.000000.bin")
print(energies.shape)
#energy = np.loadtxt(path+"energy_temp.txt")

plt.plot(energies)
plt.show()