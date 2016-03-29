SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( SOURCES_2_1 ${SOURCE_DIR}/condition_variable_2_1.cpp )
SET( SOURCES_4 ${SOURCE_DIR}/condition_variable_4.cpp )
SET( SOURCES_5_1 ${SOURCE_DIR}/condition_variable_5_1.cpp )
SET( SOURCES_5_2 ${SOURCE_DIR}/condition_variable_5_2.cpp )

# synchronization
ADD_EXECUTABLE( condition_variable_2_1 ${SOURCES_2_1} )

# n readers 1 writer
ADD_EXECUTABLE( condition_variable_4 ${SOURCES_4} )

# sleeping barber
ADD_EXECUTABLE( condition_variable_5_1 ${SOURCES_5_1} )  # deadlock
ADD_EXECUTABLE( condition_variable_5_2 ${SOURCES_5_2} )

