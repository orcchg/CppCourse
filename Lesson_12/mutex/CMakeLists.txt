SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( SOURCES_1 ${SOURCE_DIR}/mutex_1.cpp )
SET( SOURCES_1_1 ${SOURCE_DIR}/mutex_1_1.cpp )
SET( SOURCES_1_2 ${SOURCE_DIR}/mutex_1_2.cpp )
SET( SOURCES_1_3 ${SOURCE_DIR}/mutex_1_3.cpp )
SET( SOURCES_1_4 ${SOURCE_DIR}/mutex_1_4.cpp )
SET( SOURCES_1_5 ${SOURCE_DIR}/mutex_1_5.cpp )
SET( SOURCES_1_5_1 ${SOURCE_DIR}/mutex_1_5_1.cpp )
SET( SOURCES_1_5_2 ${SOURCE_DIR}/mutex_1_5_2.cpp )
SET( SOURCES_1_6 ${SOURCE_DIR}/mutex_1_6.cpp )
SET( SOURCES_1_7 ${SOURCE_DIR}/mutex_1_7.cpp )
SET( SOURCES_1_8 ${SOURCE_DIR}/mutex_1_8.cpp )
SET( SOURCES_1_9 ${SOURCE_DIR}/mutex_1_9.cpp )
SET( SOURCES_1_10 ${SOURCE_DIR}/mutex_1_10.cpp )
SET( SOURCES_3 ${SOURCE_DIR}/mutex_3.cpp )
SET( SOURCES_4 ${SOURCE_DIR}/mutex_4.cpp )
SET( SOURCES_5 ${SOURCE_DIR}/mutex_5.cpp )

# Mutex: concurrent output, critical section, sleep_for and yield
ADD_EXECUTABLE( mutex_1 ${SOURCES_1} )
ADD_EXECUTABLE( mutex_1_1 ${SOURCES_1_1} )
ADD_EXECUTABLE( mutex_1_2 ${SOURCES_1_2} )
ADD_EXECUTABLE( mutex_1_3 ${SOURCES_1_3} )
ADD_EXECUTABLE( mutex_1_4 ${SOURCES_1_4} )
# Exception safety
ADD_EXECUTABLE( mutex_1_5 ${SOURCES_1_5} )
ADD_EXECUTABLE( mutex_1_5_1 ${SOURCES_1_5_1} )
ADD_EXECUTABLE( mutex_1_5_2 ${SOURCES_1_5_2} )
ADD_EXECUTABLE( mutex_1_6 ${SOURCES_1_6} )
ADD_EXECUTABLE( mutex_1_7 ${SOURCES_1_7} )
ADD_EXECUTABLE( mutex_1_8 ${SOURCES_1_8} )
ADD_EXECUTABLE( mutex_1_9 ${SOURCES_1_9} )
# Try lock
ADD_EXECUTABLE( mutex_1_10 ${SOURCES_1_10} )

# Try lock by time or condition, re-lock mutex
ADD_EXECUTABLE( mutex_3 ${SOURCES_3} )

# Readers-Writers problem
ADD_EXECUTABLE( mutex_4 ${SOURCES_4} )
ADD_EXECUTABLE( mutex_5 ${SOURCES_5} )

