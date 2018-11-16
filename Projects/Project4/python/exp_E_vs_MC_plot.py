import numpy as np 
from math import sinh,exp,cosh
import matplotlib.pyplot as plt 

path = "../datafiles/ExerciseB/"


T = 1.
B = 1/T
Z = 2*exp(-8.*B)+2*exp(8.*B)+12
E_exp = -32./Z*sinh(8.*B)/4
Cv = 16.0**2/Z*cosh(8./T)/4
absM_exp = (32.*exp(8.)+8)/Z/4

print ("Expectation values 2x2 lattice with T = 1")
print ("Energy: ",E_exp)
print ("Heat cap: ",Cv)
print ("Magnetic: ", 0)
print ("Absolut magnetic: ",absM_exp)
print ("Susceptibility: ",0)

energies = np.loadtxt(path + "Exp_E_diffing_16_elements.dat")
absmagnetic = np.loadtxt(path + "Exp_absM_diffing_16_elements.dat")

N = len(energies)
cycles = np.zeros(N)
for i in range(N):
    cycles[i] = 2**(i+8)

plt.figure("Energy_difference")
plt.loglog(cycles,energies,'-o',label='Datapoints')
plt.title("Difference in calculated vs exact mean energy")
plt.xlabel("Number of MC cycles")
plt.ylabel(r'$|\langle E_{exact} \rangle - \langle E_{calc} \rangle|$')
plt.tight_layout()
plt.legend()

plt.figure("Abs_Magnetic_difference")
plt.semilogx(cycles,absmagnetic,'-o',label='Datapoints')
plt.title("Difference in calculated vs exact mean absolut magnetization")
plt.xlabel("Number of MC cycles")
plt.ylabel(r'$|\langle |M_{exact}| \rangle - \langle |M_{calc}| \rangle|$')
plt.tight_layout()
plt.legend()

plt.show()