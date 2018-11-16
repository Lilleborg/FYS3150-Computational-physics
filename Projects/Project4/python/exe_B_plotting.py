import numpy as np 
from math import sinh,exp,cosh
import matplotlib.pyplot as plt 

path = "../datafiles/ExerciseB/"

# Plotting style
plt.style.use('bmh')
font = {'size'   : 16}
plt.matplotlib.rc('text', usetex=True)
plt.matplotlib.rc('font', **font)

T = 1.
B = 1/T
Z = 2*exp(-8.*B)+2*exp(8.*B)+12
E_exp = -32./Z*sinh(8.*B)/4
Susp = 32*(exp(8.*B)+1)/(Z*T**2)/4
Cv = (256.*cosh(8*B)/(Z*T**2)-(32**2*sinh(8*B)*sinh(8*B))/(Z**2*T**2))/4
absM_exp = (16+8.*exp(8.)+8)/Z/4

print ("Expectation values 2x2 lattice with T = 1")
print ("Energy: ",E_exp)
print ("Heat cap: ",Cv)
print ("Magnetic: ", 0)
print ("Absolut magnetic: ",absM_exp)
print ("Susceptibility: ",Susp)

energies = np.loadtxt(path + "Exp_E_diffing_16_elements.dat")
absmagnetic = np.loadtxt(path + "Exp_absM_diffing_16_elements.dat")

Energylevels = np.fromfile(path + "Energies8388608.bin")

N = len(energies)
cycles = np.zeros(N)
for i in range(N):
    cycles[i] = 2**(i+8)
plt.figure("Test")
plt.plot(range(len(Energylevels)),Energylevels,'o')
plt.figure("Energy_difference")
plt.loglog(cycles,energies,'-o',label='Datapoints')
plt.title("Relative error mean energy")
plt.xlabel("Number of MC cycles")
plt.ylabel(r'$\frac{|\langle E_{calc} \rangle - \langle E_{exact} \rangle|}{|\langle E_{exact} \rangle|}$',fontsize = 16)
plt.tight_layout()
plt.legend()

plt.figure("Abs_Magnetic_difference")
plt.loglog(cycles,absmagnetic,'-o',label='Datapoints')
plt.title("Relative error mean absolute magnetization")
plt.xlabel("Number of MC cycles")
plt.ylabel(r'$\frac{|\langle |M_{calc}| \rangle - \langle |M_{exact}| \rangle|}{\langle |M_{exact}| \rangle}$',fontsize = 16)
plt.tight_layout()
plt.legend()

plt.show()


#plt.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
