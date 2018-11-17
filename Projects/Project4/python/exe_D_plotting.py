import numpy as np 
from math import sinh,exp,cosh
from scipy.optimize import curve_fit
from scipy.stats import boltzmann
import matplotlib.pyplot as plt 
import sys

# Plotting style
plt.style.use('bmh')
font = {'size'   : 16}
plt.matplotlib.rc('text', usetex=True)
plt.matplotlib.rc('font', **font)

def plotting(MCcycles):
    path = "../datafiles/ExerciseD/"
    temps = ["1.000000"]#,"2.400000"]
    mcbefore = [1e3,1e4]
    Ename = "_Energy_levels_"
    initial = ["Up"]#,"Random"]

    figE,axes = plt.subplots(2,2)#,sharex='col')#,sharey='row')
    figE.suptitle(r"Histogram of energy levels after equilibrium is reached")

    axes[1,0].set_xlabel(r"Energy levels")
    axes[1,1].set_xlabel(r"Energy levels")
    axes[0,0].set_ylabel(r'Normalized frequency')
    axes[1,0].set_ylabel(r'Normalized frequency')
    
    for i,T in enumerate(temps):
        for j,init in enumerate(initial):
            Efile = path + init + "_T_" + T + Ename + str(int(MCcycles-mcbefore[i])) + ".bin"    
            print("Loading ", Efile)
            energies = np.fromfile(Efile)

            hist_energy,bins_energy = np.histogram(energies, bins = 'auto',density=True)

            axes[i,j].bar(bins_energy[:-1],hist_energy,width=2)
            axes[i,j].set_title('T = {:.1f}, {:s} initial state'.format(float(T),init))

    #figE.tight_layout()
    #figE.subplots_adjust(top=0.88)
plotting(1e6)
plt.show()

# energies = np.fromfile("../Datafiles/ExerciseD/Up_T_2.400000_Energy_levels_999000.bin")
# #nergies = np.max(energies)
# print(energies.max())
# def boltzmann_T_1(E,Z):
#     return np.exp(-E)/Z


# def boltzmann_T_2(E,Z):
#     return np.exp(-E/2.4)/Z

# hist_energy,bins_energy = np.histogram(energies, bins = 'auto',density =True)

# plt.figure(1)
# plt.bar(bins_energy[:-1],hist_energy)
# #plt.plot(bins_energy[:-1],y)


