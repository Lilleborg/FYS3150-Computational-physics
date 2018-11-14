import numpy as np 
import matplotlib.pyplot as plt 
from math import sinh,exp

#path = "../build/txtfiles/"
T = 3.
B = 1/T
Z = 2*exp(-8.*B)+2*exp(8.*B)+12
E_exp = -32./Z*sinh(8.*B)
print (E_exp)

energies = np.fromfile("../build/energies_energies_3.000000.bin")
N = len(energies)
print (energies.shape)
#energy = np.loadtxt(path+"energy_temp.txt")


def polifyting(dataarray):
    N = range(len(dataarray))
    func = np.polyfit(N,dataarray,2)
    smuud = np.poly1d(func)
    return smuud(N)

plt.plot(np.arange(0,N,100),energies[::100],'.')
plt.plot(polifyting(energies[::100])) 
plt.show()