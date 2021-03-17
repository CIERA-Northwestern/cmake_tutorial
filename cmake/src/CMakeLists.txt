# add the executable
add_executable(example example.c)
include_directories(SYSTEM ${HDF5_INCLUDE_DIRS})
include_directories(SYSTEM ${MPI_INCLUDE_DIRS})
include_directories(SYSTEM ${GSL_INCLUDE_DIRS})

target_link_libraries(example ${HDF5_LIBRARIES})
target_link_libraries(example ${HDF5_HL_LIBRARIES})
target_link_libraries(example ${GSL_LIBRARIES})
target_link_libraries(example ${MPI_LIBRARIES} ${MPI_LINK_FLAGS})

install(TARGETS example DESTINATION bin)
