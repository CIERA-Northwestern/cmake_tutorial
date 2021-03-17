system-build:
	#module load mpi/openmpi-4.0.5-intel-19.0.5.281 
	mpicc example.c -lgsl -lgslcblas -lm -lhdf5 -lhdf5_hl -o example
module-build:
	#module load mpi/openmpi-4.0.5-intel-19.0.5.281 
	#module load hdf5/1.10.7-openmpi-4.0.5-intel-19.0.5.281 
	#module load gsl/2.5-intel-19.0.5.281
	# sometimes packages ship with package configuration files that let you know how to correctly linked against them.
	# cat /hpc/software/spack/opt/spack/linux-rhel7-x86_64/intel-19.0.5.281/gsl-2.5-ioov7cjw6tqqvtzuukzfkt3evh5odjkl/lib/pkgconfig/gsl.pc 
	# LDFLAGS=$(echo $LD_LIBRARY_PATH | echo "-L" $(sed 's/:/ -L /g'))
	GSL_CBLAS_LIB="-L/software/intel/2019.5/compilers_and_libraries_2019.5.281/linux/mkl/lib/intel64 -L/lib64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl"
	mpicc -I/hpc/software/spack/opt/spack/linux-rhel7-x86_64/intel-19.0.5.281/hdf5-1.10.7-slwfvnxqgb353tf4ltetdeka6ryccz7y/include -I/hpc/software/spack/opt/spack/linux-rhel7-x86_64/intel-19.0.5.281/gsl-2.5-ioov7cjw6tqqvtzuukzfkt3evh5odjkl/include example.c -L/hpc/software/spack/opt/spack/linux-rhel7-x86_64/intel-19.0.5.281/gsl-2.5-ioov7cjw6tqqvtzuukzfkt3evh5odjkl/lib -L/hpc/software/spack/opt/spack/linux-rhel7-x86_64/intel-19.0.5.281/hdf5-1.10.7-slwfvnxqgb353tf4ltetdeka6ryccz7y/lib/ -lgsl ${GSL_CBLAS_LIB} -lm -lhdf5 -lhdf5_hl -o example
clean:
	rm example *.h5
