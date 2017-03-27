Taken from README of HFRS simulator, K. Greenan, http://www.kaymgee.com/Kevin_Greenan/Software.html
 

MARKOV MODEL LANGUAGE AND SOLVER
The HFRS is packaged with a custom Markov model solver: mm_solve.py.  
The solver has the ability to both simulate and analytically solve Markov models.  
For usage, type 'python mm_solver.py -h'.
The solver relies on a custom modeling language.  
Simply drop a model into ./models and run the utility to solve the model.  
I have placed a bunch of models in that directory.

FORMAT OF MARKOV MODEL FILES
There are 3 main tags in a model file: [num states], [assign] and [END].  
A tag must be placed on its own line and defines a section of a model.

[num states] : this defines the beginning of the state and transition description

[assign] : defines values to assign to variables given in the state and transition description.

[END] : the end of the model



Example (RAID4 model with an 8 disk array):
[num states]
3
0 1 a failure
1 0 b repair
1 2 c failure
[assign]
a=N*lam_d
b=mu
c=(N-1)*lam_d
lam_d=(1/461386.)
mu=(1/12.)
N=8
[END]



The number of states in this case is 3: 0, 1 and 2 devices failed.  
There are 3 transitions in this model: transition from 0 to 1 disks failed, 
transition from 1 disk failed to 0 failed and transition from 1 disk failed 
to 2 failed (data loss).
The disk failure rate is 1/461386 and repair rate is 1/12.

Note the use of variables to make creating/updating a model easy.  
For example, lam_d represents the failure rate.  
In addition, arithmetic expressions can also be placed in 
this section.  

