SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( SOURCES_1 ${SOURCE_DIR}/mutex_1.cpp )
SET( SOURCES_1_1 ${SOURCE_DIR}/mutex_1_1.cpp )
SET( SOURCES_1_2 ${SOURCE_DIR}/mutex_1_2.cpp )
SET( SOURCES_1_3 ${SOURCE_DIR}/mutex_1_3.cpp )
SET( SOURCES_1_4 ${SOURCE_DIR}/mutex_1_4.cpp )
SET( SOURCES_1_5 ${SOURCE_DIR}/mutex_1_5.cpp )
SET( SOURCES_1_6 ${SOURCE_DIR}/mutex_1_6.cpp )
SET( SOURCES_2 ${SOURCE_DIR}/mutex_2.cpp )
SET( SOURCES_3 ${SOURCE_DIR}/mutex_3.cpp )
SET( SOURCES_4 ${SOURCE_DIR}/mutex_4.cpp )
SET( SOURCES_5 ${SOURCE_DIR}/mutex_5.cpp )

# Mutex: concurrent output, critical section, sleep_for and yield
ADD_EXECUTABLE( mutex_1 ${SOURCES_1} )
ADD_EXECUTABLE( mutex_1_1 ${SOURCES_1_1} )
ADD_EXECUTABLE( mutex_1_2 ${SOURCES_1_2} )
ADD_EXECUTABLE( mutex_1_3 ${SOURCES_1_3} )
ADD_EXECUTABLE( mutex_1_4 ${SOURCES_1_4} )
ADD_EXECUTABLE( mutex_1_5 ${SOURCES_1_5} )
ADD_EXECUTABLE( mutex_1_6 ${SOURCES_1_6} )

ADD_EXECUTABLE( mutex_2 ${SOURCES_2} )
ADD_EXECUTABLE( mutex_3 ${SOURCES_3} )
ADD_EXECUTABLE( mutex_4 ${SOURCES_4} )
ADD_EXECUTABLE( mutex_5 ${SOURCES_5} )

