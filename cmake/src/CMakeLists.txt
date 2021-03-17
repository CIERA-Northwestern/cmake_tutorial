# add the executable
add_executable(make_hdf5_table example.c)
include_directories(SYSTEM ${HDF5_INCLUDE_DIRS})
include_directories(SYSTEM ${MPI_INCLUDE_DIRS})
include_directories(SYSTEM ${GSL_INCLUDE_DIRS})

target_link_libraries(make_hdf5_table ${HDF5_LIBRARIES})
target_link_libraries(make_hdf5_table ${HDF5_HL_LIBRARIES})
target_link_libraries(make_hdf5_table ${GSL_LIBRARIES})
target_link_libraries(make_hdf5_table ${MPI_LIBRARIES} ${MPI_LINK_FLAGS})

install(TARGETS make_hdf5_table DESTINATION bin)
