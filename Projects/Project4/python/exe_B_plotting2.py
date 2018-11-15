import numpy as np 
import matplotlib.pyplot as plt 
from math import sinh,exp,cosh
import sys

path = "../datafiles/ExerciseB"


T = 1.
B = 1/T
Z = 2*exp(-8.*B)+2*exp(8.*B)+12
E_exp = -32./Z*sinh(8.*B)/4
Cv = 16.0**2/Z*cosh(8./T)
absM_exp = (16.+4*exp(8))/Z

print("Expectation values 2x2 lattice with T = 1")
print ("Energy: ",E_exp)
print ("Heat cap: ",Cv)
print ("Magnetic: ", 0)
print ("Absolut magnetic: ",absM_exp)
print ("Susceptibility: ",0)

energies = np.loadtxt(path+"Exp_E_diffing_16_elements.dat")
absmagnetic = np.loadtxt(path+"Exp_absM_diffing_16_elements.dat")
N = len(energies)


def polifyting(dataarray):
    N = range(len(dataarray))
    func = np.polyfit(N,dataarray,2)
    smuud = np.poly1d(func)
    return smuud(N)

plt.plot(np.arange(0,N,100),energies[::100])
plt.plot(polifyting(energies[::100])) 
plt.show()