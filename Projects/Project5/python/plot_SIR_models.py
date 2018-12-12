import numpy as np 
import matplotlib.pyplot as plt 
import sys
import math
import glob
import copy

# Plotting style
plt.style.use('bmh')
font = {'size'   : 16}
plt.matplotlib.rc('text', usetex=True)
plt.matplotlib.rc('font', **font)

# example filename SIR_a_const_b_1_c_0.5_dt_0.001_N_400.bin

# TODO: Add expectation values along right y axis

def plottingSIR(timestep,finaltime,atype,exeFolder,simtype_,manual_filenames=False):
    """
    @ timestep - dt value in filename
    @ finaltime - T value in filename
    @ atype - a parameter type, either const or season
    @ manual filenames - skip the automatisation step of reading files, 
                         give list of 4 files to be read
    """
    # Set up axes and figure
    fig, axes = plt.subplots(2,2,figsize = (14,8))#,sharex='col')#,sharey='row')

    if manual_filenames:
        pass    # TODO add method for giving 4 filenames
    else:    
        # Reading files by globbing
        path = "../datafiles/" + exeFolder + "/"
        list_of_files = glob.glob(path + '*.bin')   # globbing all binary files in path

        list_of_correct_file = [] 

        string_simtype = "SIR_a"
        simulation_type = 'RK4'
        if simtype_ == 'MC':
            string_simtype = "SIR_MC_a"
            simulation_type = 'MC'




        string_dt = "dt_" + timestep + "_"
        string_T = "T_" + finaltime + "_"
        if simtype_ == 'both': #hack
            string_simtype = string_T
            simulation_type = ''
        list_of_parameters = {}
        mean_std = {}

        for filename in list_of_files:   # add files with correct dt and endtime
            if string_dt in filename and string_T in filename and atype in filename and string_simtype in filename:
                list_of_correct_file.append(filename)
        # User check that correct files are given
        def usercheck():
            for i,file in enumerate(list_of_correct_file):
                print ('File nr {:d}: '.format(i),file)
            if len(list_of_correct_file) == 0:
                print('Found no matching files')
                print('---Quiting---')
                sys.exit(1)

        list_of_correct_file.sort()

        usercheck()
        terminate = input('Continue with current files? y/n/edit ')

        if terminate == 'n':
            sys.exit(1)
        if terminate == 'edit':
            # user gives integer for file nr to be removed,
            removing = True
            while removing:
                filenr = (input('Give file nr you wish to remove: int/stop '))
                try:
                    filenr = int(filenr)
                    list_of_correct_file.pop(filenr)
                    usercheck()
                except:
                    pass
                if filenr == 'stop':
                    break

        if len(list_of_correct_file) > 4:
            for i in range(4): #rearange files a bit
                list_of_correct_file.append(list_of_correct_file[0])
                list_of_correct_file.remove(list_of_correct_file[0])
            people2 = ['S MC','I MC','R MC']

    #list_of_correct_file.sort()
    usercheck()


    sub = [[0,0],[0,1],[1,0],[1,1]]
    people = ['S','I','R']

    for f,filename in enumerate(list_of_correct_file):
        print ('Loading ', filename)
        data = np.fromfile(filename)   # array of S I R values 
        onesize = int(math.ceil(data.size)/3.0) # data is a flattened array
                                                # this size seperates the S I and R

        # Dictionary for handling parameters
        params = copy.deepcopy(parameters)  # creates copy of parameter dictionary 
        if atype == "const":
            params['a'] = 'a0'
        else:
            params['a'] = 'a(t)'
            
        
        # Temporary string for manipulating filename
        temp = filename.split('_')  # splitting filename for extracting param values
        temp[-1] = temp[-1].replace('.bin','')
        for i,ele in enumerate(temp):
            if ele == 'T':
                indexofT_ = i
                break

        for l,ele in enumerate(temp[indexofT_:]):   # fill dictionary with parameter values
            if l%2 == 0:
                if ele != 'N' and ele != 'dt' and ele != 'T':
                    if ele == 'sigS' or ele == 'sigI' or ele == 'sigR':
                        mean_std[ele] = float(temp[indexofT_+1+l])
                        continue
                    params[ele] = temp[indexofT_+1+l]

        paramstring = ""
        for key in paramlist:
            if params[key] != None:
                paramstring += key + '=' + params[key] + ', '
        # Plotting
        i = sub[f%4][0]
        j = sub[f%4][1]

        #time = np.linspace(0,float(finaltime),onesize)
        #if 'MC' in filename:

        time = np.linspace(0,int(math.ceil(onesize/365)),onesize)

        for k in range(3):
            thislabel = people[k]
            line = '-'
            if f >= 4:
                thislabel = people2[k]
                line = '--'

            axes[i,j].plot(time,data[k*onesize:(k+1)*onesize],label=thislabel,linestyle = line)
            size = 20 - (len(params) - 5)
            axes[i,j].set_title(paramstring, fontsize = size)
            axes[i,j].set_ylim(0,np.max(data)*1.2)
        
        if simtype == 'MC' or f>=4: # add average std in axes legend
            axes[i,j].legend([r'$\sigma_{:s} = {:.2f}$'.format(people[0],mean_std['sigS']),'$\sigma_{:s} = {:.2f}$'.format(people[1],mean_std['sigI']),'$\sigma_{:s} = {:.2f}$'.format(people[2],mean_std['sigR'])],loc = 'upper left',fontsize = 14,ncol = 3, columnspacing = 0.5)
                
    fig.suptitle('{:s} simulation of SIRS model, T = {:s}, dt = {:s}'.format(simulation_type,finaltime,timestep))
    axes[1,0].set_xlabel(r"Time, [Years]")
    axes[1,1].set_xlabel(r"Time, [Years]")
    axes[0,0].set_ylabel(r'NR People in category')
    axes[1,0].set_ylabel(r'NR People in category')

    ax = fig.gca()
    handles, labels = ax.get_legend_handles_labels()
    fig.legend(handles, labels)

    paramstring = paramstring.replace(' ', '_')
    paramstring = paramstring.replace(',', '')
    plotfilename = '../plots/plot_' + "{:s}_T={:s}_dt={:s}".format(simulation_type,finaltime,timestep)
    plotfilename += paramstring
    plotfilename += '.pdf'

    saving = input('Savefig? y/n ')
    if saving == 'y':
        plt.savefig(plotfilename)
    plt.show()
    
    #fig.tight_layout()

paramlist = ['a','b','c','d','dI','e','f']
parameters = {}
for param in paramlist: # setup parameter dictionary
    parameters[param] = None

try:
    dt = sys.argv[1]
    T = sys.argv[2]
    a = sys.argv[3]
    exe = sys.argv[4]
    simtype = sys.argv[5]
except IndexError:
    print ('Not correct number of cmd line arguments')
    print ('Need 5 arguments handled as strings')
    print ('1 - dt value')
    print ('2 - Endtime value')
    print ('3 - a type, const or season')
    print ('4 - exe, exeA exeB.. etc')
    print ('5 - MC or RK4')
    print ('---Quiting---')
    sys.exit(1)



plottingSIR(dt,T,a,exe,simtype)








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
