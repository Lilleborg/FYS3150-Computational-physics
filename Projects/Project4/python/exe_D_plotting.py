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
    Ename = "_Energy_levels_"
    initial = ["Up","Random"]


    figE,axes = plt.subplots(2,2,sharex='col',sharey='row')
    figE.suptitle(r"Histogram energy levels after equi.")

    #axes[1,0].set_xlabel(r"Energy levels")
    #axes.set_ylabel(r'Normalized frequency')
    
    for i,T in enumerate(temps):
        for j,init in enumerate(initial):
            Efile = path + init + "_T_" + T + Ename + str(MCcycles) + ".bin"    
            print("Loading ", Efile)
            energies = np.fromfile(Efile)

            hist_energy,bins_energy = np.histogram(energies, bins = 'auto')

            axes[i,j].bar(bins_energy[:-1],hist_energy)

    figE.tight_layout()
    figE.subplots_adjust(top=0.88)

energies = np.fromfile("../Datafiles/ExerciseD/Up_T_2.400000_Energy_levels_999000.bin")
#energies /= energies.shape
print(energies.max())
def boltzmann_T_1(E,Z):
    return np.exp(-E)/Z

def boltzmann_T_2(E,Z):
    return np.exp(-E/2.4)/Z

hist_energy,bins_energy = np.histogram(energies, bins = 'auto',density =True)
hist_energy = np.asarray(hist_energy)
bins_energy = np.asarray(bins_energy)
print (bins_energy)
# bins_energy = energies.shape
# print (bins_energy)
print (hist_energy)
print(np.exp(-bins_energy[0])/hist_energy[0])


# MinE = np.min(bins_energy)
# MaxE = np.max(bins_energy)
# Earray = np.linspace(MinE+MinE/100.,MaxE-MaxE/100.,100)
# tempbins = np.zeros(bins_energy.shape)
# tempnumbers = np.zeros_like(tempbins)
# tempbins[1:] = bins_energy[:-1]
# tempbins[0] = bins_energy[0]-([bins_energy[1]-bins_energy[0]])
# tempnumbers[1:] = hist_energy
# print(tempbins)
# print(tempnumbers)
#param,paramcov = curve_fit(boltzmann_T_1,bins_energy[:-1],hist_energy)

#print (param)
#y = boltzmann_T_1(bins_energy[:-1],*param)
#print(np.max(y),np.argmax(y),np.min(y),np.argmin(y))
plt.figure(2)
plt.bar(bins_energy[:-1],hist_energy)
#plt.plot(bins_energy[:-1],y)


plt.show()
#plotting(999000)