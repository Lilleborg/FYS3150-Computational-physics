import numpy as np 
import matplotlib.pyplot as plt 

pathtodata = "../datafiles/"

energies = np.loadtxt(pathtodata + "Exp_E_diffing_16_elements.dat")
print(energies[0])
N = len(energies)
cycles = np.zeros(N)
for i in range(N):
    cycles[i] = 2**(i+8)
plt.loglog(cycles,energies,'-o',label='Datapoints') #,markevery = [0,-1]
plt.title("Difference in calculated vs exact mean energy")
plt.xlabel("Number of MC cycles")
plt.ylabel(r'$|\langle E_{exact} \rangle - \langle E_{calc} \rangle|$')
plt.tight_layout()
plt.legend()

plt.show()