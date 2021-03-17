AC_INIT(example, 1.0)

# Check if C compiler works
AC_PROG_CC([mpicc])

# Ensure existence of external libraries and headers
AC_CHECK_HEADERS(hdf5.h)
AC_CHECK_HEADERS(gsl/gsl_sf_bessel.h)

AC_CHECK_LIB(hdf5, H5open)
AC_CHECK_LIB(hdf5_hl, H5TBread_table)
AC_CHECK_LIB(gsl, gsl_sf_bessel_J0)

# Process Makefile.in to create Makefile
AC_OUTPUT(Makefile)
