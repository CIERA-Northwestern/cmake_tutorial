# QUEST

# Makefile

# Autoconf
```
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
