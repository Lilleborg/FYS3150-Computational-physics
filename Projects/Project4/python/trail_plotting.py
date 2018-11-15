import numpy as np 
import matplotlib.pyplot as plt 
from math import sinh,exp,cosh
import sys

#path = "../build/txtfiles/"
T = 1.
B = 1/T
Z = 2*exp(-8.*B)+2*exp(8.*B)+12
E_exp = -32./Z*sinh(8.*B)/4
Cv = 16.0**2/Z*cosh(8./T)
print (Cv)
print (E_exp)


sys.exit()
energies = np.fromfile("../build/energies_energies_1.000000.bin")
N = len(energies)
print (energies.shape)
#energy = np.loadtxt(path+"energy_temp.txt")


def polifyting(dataarray):
    N = range(len(dataarray))
    func = np.polyfit(N,dataarray,2)
    smuud = np.poly1d(func)
    return smuud(N)

plt.plot(np.arange(0,N,100),energies[::100])
plt.plot(polifyting(energies[::100])) 
plt.show()