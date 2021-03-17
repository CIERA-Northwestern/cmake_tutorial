#include <mpi.h>
#include "hdf5.h"
#include "hdf5_hl.h"
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_sf_bessel.h>

/*-------------------------------------------------------------------------
 * Table API example
 *
 * H5TBmake_table
 * H5TBread_table
 *
 *-------------------------------------------------------------------------
 */

#define NFIELDS  (hsize_t)  5
#define NRECORDS (hsize_t)  8
#define TABLE_NAME "table"

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

// run a GSL function
    double x = 5.0;
    double y = gsl_sf_bessel_J0 (x);
    printf ("J0(%g) = %.18e\n", x, y);

// Write an HDF5 Table
    typedef struct Particle
    {
    char   name[16];
    int    lati;
    int    longi;
    float  pressure;
    double temperature;
    } Particle;

    Particle  dst_buf[NRECORDS];

    /* Calculate the size and the offsets of our struct members in memory */
    size_t dst_size =  sizeof( Particle );
    size_t dst_offset[NFIELDS] = { HOFFSET( Particle, name ),
                                HOFFSET( Particle, lati ),
                                HOFFSET( Particle, longi ),
                                HOFFSET( Particle, pressure ),
                                HOFFSET( Particle, temperature )};

    size_t dst_sizes[NFIELDS] = { sizeof( dst_buf[0].name),
                               sizeof( dst_buf[0].lati),
                               sizeof( dst_buf[0].longi),
                               sizeof( dst_buf[0].pressure),
                               sizeof( dst_buf[0].temperature)};


    /* Define an array of Particles */
    Particle  p_data[NRECORDS] = {
    {"zero",0,0, 0.0f, 0.0},
    {"one",10,10, 1.0f, 10.0},
    {"two",  20,20, 2.0f, 20.0},
    {"three",30,30, 3.0f, 30.0},
    {"four", 40,40, 4.0f, 40.0},
    {"five", 50,50, 5.0f, 50.0},
    {"six",  60,60, 6.0f, 60.0},
    {"seven",70,70, 7.0f, 70.0}
    };

    /* Define field information */
    const char *field_names[NFIELDS]  =
    { "Name","Latitude", "Longitude", "Pressure", "Temperature" };
    hid_t      field_type[NFIELDS];
    hid_t      string_type;
    hid_t      file_id;
    hsize_t    chunk_size = 10;
    int        *fill_data = NULL;
    int        compress  = 0;
    int        i;

    /* Initialize field_type */
    string_type = H5Tcopy( H5T_C_S1 );
    H5Tset_size( string_type, 16 );
    field_type[0] = string_type;
    field_type[1] = H5T_NATIVE_INT;
    field_type[2] = H5T_NATIVE_INT;
    field_type[3] = H5T_NATIVE_FLOAT;
    field_type[4] = H5T_NATIVE_DOUBLE;

    /* Create a new file using default properties. */
    char outfile[100];

    sprintf(outfile, "hdf5_table_%d.h5", world_rank);
    file_id = H5Fcreate( outfile, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT );

    /*-------------------------------------------------------------------------
    * H5TBmake_table
    *-------------------------------------------------------------------------
    */

    H5TBmake_table( "Table Title", file_id, TABLE_NAME,NFIELDS,NRECORDS,
                         dst_size,field_names, dst_offset, field_type,
                         chunk_size, fill_data, compress, p_data  );

    /*-------------------------------------------------------------------------
    * H5TBread_table
    *-------------------------------------------------------------------------
    */

    H5TBread_table( file_id, TABLE_NAME, dst_size, dst_offset, dst_sizes, dst_buf );

    /* print it by rows */
    for (i=0; i<NRECORDS; i++) {
    printf ("%-5s %-5d %-5d %-5f %-5f",
    dst_buf[i].name,
    dst_buf[i].lati,
    dst_buf[i].longi,
    dst_buf[i].pressure,
    dst_buf[i].temperature);
    printf ("\n");
    }

    /*-------------------------------------------------------------------------
    * end
    *-------------------------------------------------------------------------
    */

    /* close type */
    H5Tclose( string_type );

    /* close the file */
    H5Fclose( file_id );

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}

