# QUEST

# Makefile
```
cd Makefile
# basic install that relies on the libraries existing on the system
make system-build

# Now load the modules so that you can build the hardcoded compilation for compiling with modules
module purge all
module load mpi/openmpi-4.0.5-intel-19.0.5.281
module load hdf5/1.10.7-openmpi-4.0.5-intel-19.0.5.281
module load gsl/2.5-intel-19.0.5.281

make module-build
```

# Autoconf
```
cd AutoConf
module purge all
module load mpi/openmpi-4.0.5-intel-19.0.5.281
module load hdf5/1.10.7-openmpi-4.0.5-intel-19.0.5.281
module load gsl/2.5-intel-19.0.5.281

autoconf && LDFLAGS=$(echo $LD_LIBRARY_PATH | echo "-L" $(sed 's/:/ -L /g')) ./configure && make
```

# cmake
To compile the example using cmake on QUEST. Please run the following commands from within the cmake folder

```
module purge all
module load cmake/3.15.4 
module load mpi/openmpi-4.0.5-intel-19.0.5.281 
module load hdf5/1.10.7-openmpi-4.0.5-intel-19.0.5.281 
module load gsl/2.5-intel-19.0.5.281

rm -rf build
mkdir build
cd build
CC=mpicc cmake .. -DCMAKE_INSTALL_PREFIX=.
make install
```

# Singularity
Instructions for building the example program into a singularity container using the provided recipe/defintion file.

```
module purge all
module load singularity
cd Singularity
singularity build --remote example.simg example.def
```
Singularity requires calling programs that were compiled with MPI within the container with an MPI executable that exists on the machine
that you are running on that has the same *major* release version as the MPI within the container. When we installed OpenMPI in the manner that we did, we installed version 4.0.3. On Quest, and we have OpenMPI 4.0.5 installed on Quest as modules. To this end, we show how you can call the program in the container when running on Quest.

## SLURM Example
```
#!/bin/bash
#SBATCH --account=a9009  ## YOUR ACCOUNT pXXXX or bXXXX
#SBATCH --partition=master  ### PARTITION (buyin, short, normal, etc)
#SBATCH --nodes=2 ## how many computers do you need
#SBATCH --ntasks-per-node=2 ## how many cpus or processors do you need on each computer
#SBATCH --time=00:10:00 ## how long does this need to run (remember different partitions have restrictions on this param)
#SBATCH --mem-per-cpu=1G ## how much RAM do you need per CPU (this effects your FairShare score so be careful to not ask for more than you need))
#SBATCH --job-name=sample_job  ## When you run squeue -u NETID this is how you can identify the job
#SBATCH --output=outlog ## standard out and standard error goes to this file

module purge all
module load mpi/openmpi-4.0.5-gcc-10.2.0 
module load singularity

mpirun -np ${SLURM_NTASKS} singularity exec -B /projects:/projects example.simg /opt/local/bin/example
```
