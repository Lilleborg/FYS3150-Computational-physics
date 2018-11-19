import numpy as np 
from math import sinh,exp,cosh
import matplotlib.pyplot as plt 
import sys

# Plotting style
plt.style.use('bmh')
font = {'size'   : 16}
plt.matplotlib.rc('text', usetex=True)
plt.matplotlib.rc('font', **font)

try:
    MC = int(sys.argv[1])
except IndexError:
    print ('Number of MC cycles given, first cmd argument. Defaulting to \n %d'%int(1e5))
    MC = int(1e5)
except ValueError:
    print ('Number of MC cycles not understood, second cmd argument. Defaulting to \n %d'%int(1e5))
    MC = int(1e5)
try:
    filename1 = str(sys.argv[2])
except IndexError:
    print ('First filenamestart not given, second cmd argument. Defaulting to \n Jakob_file')
    filename1 = 'Jakob_file'
except ValueError:
    print ('First filenamestart not understood, second cmd argument. Defaulting to \n Jakob_file')
    filename1 = 'Jakob_file'
try:
    filename2 = str(sys.argv[3])
except IndexError:
    print ('Only one datafile given, no third cmd argument.')
    filename2 = None
except ValueError:
    print ('Second filenamestart not understood, third cmd argument. Defaulting to \n None')
    filename2 = None
try:
    filename3 = str(sys.argv[4])
except IndexError:
    print ('Only two datafile given, no fourth cmd argument.')
    filename3 = None
except ValueError:
    print ('Third filenamestart not understood, fourth cmd argument. Defaulting to \n None')
    filename3 = None
try:
    filename4 = str(sys.argv[5])
except IndexError:
    print ('Only three datafile given, no fifth cmd argument.')
    filename4 = None
except ValueError:
    print ('Fourth filenamestart not understood, fifth cmd argument. Defaulting to \n None')
    filename4 = None

figE = plt.figure("Expectation_E")
axE = plt.gca()
figC = plt.figure("Heat_cap")
axC = plt.gca()
figM = plt.figure("Expectation_abs_M")
axM = plt.gca()
figX = plt.figure("Susceptitbility")
axX = plt.gca()

axE.set_title(r"Mean energy")
axE.set_xlabel(r"$T$",fontsize = 15)
axE.set_ylabel(r'$\langle E \rangle(MC)$',fontsize = 15)

axM.set_title("Mean abs magnetisation")
axM.set_xlabel(r"$T$",fontsize = 15)
axM.set_ylabel(r'$\langle |M|  \rangle (MC)$',fontsize = 15)

axC.set_title("Heat capacity")
axC.set_xlabel(r"$T$",fontsize = 15)
axC.set_ylabel(r'$C_v$',fontsize = 15)

axX.set_title("Susceptitbility")
axX.set_xlabel(r"$T$",fontsize = 15)
axX.set_ylabel(r'$\chi$',fontsize = 15)

filenames = [filename1,filename2,filename3,filename4]
print (filenames)
Ls = [40,60,80,100]

for L in Ls:
    totq = np.zeros((6,31))
    q = np.zeros((6,31)) # q = T , E , Cv , M , X , absM
    nrfiles = 0
    for f in filenames:
        if f != None:
            nrfiles += 1
            filename = "../letsMPI/" + f + "_L_" + str(L) + "_effectiveMC_" + str(MC) + ".txt"
            print("Loading:\n" + filename)
            q[0,:],q[1,:],q[2,:],q[3,:],q[4,:],q[5,:] = np.loadtxt(filename,unpack=True)
            for i in range(len(q[:,0])):
                totq[i,:] += q[i,:]
        
    if nrfiles != 0:                
        totq /= nrfiles
        axE.plot(totq[0,:],totq[1,:],label="L = %d"%L)
        axC.plot(totq[0,:],totq[2,:],label="L = %d"%L)
        axX.plot(totq[0,:],totq[4,:],label="L = %d"%L)
        axM.plot(totq[0,:],totq[5,:],label="L = %d"%L)

figs = [figE,figC,figM,figX]
axes = [axE,axC,axM,axX]
fignames = ["../plots/plot_E_exp_E_MC","../plots/plot_E_Heat_cap_MC","../plots/plot_E_exp_abs_M_MC","../plots/plot_E_susc_MC"]

for i in range(len(figs)):
    fignames[i] += (str(MC)+".pdf")
    axes[i].legend()
    figs[i].tight_layout()
    figs[i].savefig(fignames[i])
plt.show()

