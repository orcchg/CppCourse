SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )
SET( SOURCES_1 ${SOURCE_DIR}/condition_variable_1.cpp )
SET( SOURCES_1_0 ${SOURCE_DIR}/condition_variable_1_0.cpp )
SET( SOURCES_1_1 ${SOURCE_DIR}/condition_variable_1_1.cpp )
SET( SOURCES_2 ${SOURCE_DIR}/condition_variable_2.cpp )
SET( SOURCES_2_1 ${SOURCE_DIR}/condition_variable_2_1.cpp )
SET( SOURCES_3 ${SOURCE_DIR}/condition_variable_3.cpp )
SET( SOURCES_3_1 ${SOURCE_DIR}/condition_variable_3_1.cpp )
SET( SOURCES_3_2 ${SOURCE_DIR}/condition_variable_3_2.cpp )
SET( SOURCES_4 ${SOURCE_DIR}/condition_variable_4.cpp )
SET( SOURCES_5 ${SOURCE_DIR}/condition_variable_5.cpp )
SET( SOURCES_5_1 ${SOURCE_DIR}/condition_variable_5_1.cpp )
SET( SOURCES_5_2 ${SOURCE_DIR}/condition_variable_5_2.cpp )

# sleep vs wait
ADD_EXECUTABLE( condition_variable_1 ${SOURCES_1} )
ADD_EXECUTABLE( condition_variable_1_0 ${SOURCES_1_0} )
ADD_EXECUTABLE( condition_variable_1_1 ${SOURCES_1_1} )

# synchronization
ADD_EXECUTABLE( condition_variable_2 ${SOURCES_2} )
ADD_EXECUTABLE( condition_variable_2_1 ${SOURCES_2_1} )

# dinning philosophers
ADD_EXECUTABLE( condition_variable_3 ${SOURCES_3} )  # deadlock
ADD_EXECUTABLE( condition_variable_3_1 ${SOURCES_3_1} )  # deadlock
ADD_EXECUTABLE( condition_variable_3_2 ${SOURCES_3_2} )

# n readers 1 writer
ADD_EXECUTABLE( condition_variable_4 ${SOURCES_4} )

# sleeping barber
ADD_EXECUTABLE( condition_variable_5 ${SOURCES_5} )
ADD_EXECUTABLE( condition_variable_5_1 ${SOURCES_5_1} )  # deadlock
ADD_EXECUTABLE( condition_variable_5_2 ${SOURCES_5_2} )

