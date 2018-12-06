import numpy as np 
import matplotlib.pyplot as plt 
import sys
import math
import glob

# Plotting style
plt.style.use('bmh')
font = {'size'   : 16}
plt.matplotlib.rc('text', usetex=True)
plt.matplotlib.rc('font', **font)

# example filename SIR_a_const_b_1_c_0.5_dt_0.001_N_400.bin

def plottingSIR(timestep,finaltime,atype,exeFolder,debug = True):
    """
    @ timestep - dt value in filename
    @ finaltime - T value in filename
    @ atype - a parameter type, either const or season
    """
    path = "../datafiles/" + exeFolder + "/"
    list_of_files = glob.glob(path + '*.bin')   # globbing all binary files in path
    list_of_correct_file = [] 
    paramlist = ['a','b','c','d','dI','e','f']
    params = {}
    for param in paramlist:
        params[param] = 0
    params['a'] = atype

    string_dt = "dt_" + str(timestep) + "_"
    string_T = "T_" + str(finaltime) + "_"

    for filename in list_of_files:   # add files with correct dt and endtime
        if string_dt in filename and string_T in filename:
            list_of_correct_file.append(filename)
            
    if debug:
        for file in list_of_correct_file:
            print (file)
        terminate = input('Continue with current files? y/n ')
        if terminate != 'y':
            sys.exit(1)

    fig, axes = plt.subplots(2,2)#,sharex='col')#,sharey='row')
    fig.suptitle('Simulation of SIRS model, T = {:.0f} dt = {:.5f}'.format(finaltime,timestep))
    axes[1,0].set_xlabel(r"Time, [days]")
    axes[1,1].set_xlabel(r"Time, [days]")
    axes[0,0].set_ylabel(r'NR People in category')
    axes[1,0].set_ylabel(r'NR People in category')

    sub = [[0,0],[0,1],[1,0],[1,1]]
    people = ['S','I','R']
    for f,filename in enumerate(list_of_correct_file):
        print ('Loading ', filename)
        data = np.fromfile(filename)
        temp = filename.split('_')  # parameters from temp[5:]
        temp[-1] = temp[-1].replace('.bin','')
        for l,ele in enumerate(temp[5:]):   # fill dictionary with parameter values
            if l%2 == 0:
                params[ele] = temp[6+l]

        onesize = int(math.ceil(data.size)/3.0)

        i = sub[f][0]
        j = sub[f][1]
        for k in range(3):
            axes[i,j].plot(data[k*onesize:(k+1)*onesize],label=people[k])
            axes[i,j].set_title('Testtitle holding parameters')
    ax = fig.gca()
    handles, labels = ax.get_legend_handles_labels()
    fig.legend(handles, labels)
    #fig.tight_layout()
    #fig.subplots_adjust(top=0.88)



plottingSIR(0.0001,20,'season','exeA')
plt.show()







sys.exit(1)
# -----------------------------------
# TEST OF FILESIZES ETC
# -----------------------------------


files = np.fromfile('../datafiles/exeA/SIR_a_const_T_1_b_1_c_0.5_dt_0.001_N_400.bin')
#txt = np.fromfile('../datafiles/exeA/SIR_a_const_T_1_b_1_c_0.5_dt_0.001_N_400.bin')
txt = np.loadtxt('../datafiles/exeA/SIR_a_const_T_1_b_1_c_0.5_dt_0.001_N_400.txt',unpack = True)


print (files.shape)
print (txt.shape)

onesize = int(math.ceil(files.size/3.0))
plt.figure()
for i in range(3):
    plt.plot(files[i*onesize:(i+1)*onesize])

plt.figure()
for i in range(3):
    plt.plot(txt[i],label=str(i))

plt.legend()
plt.show()
