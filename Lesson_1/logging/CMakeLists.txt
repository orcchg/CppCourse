SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )
SET( SOURCES_1 ${SOURCE_DIR}/logging_sample_1.cpp )
SET( SOURCES_2 ${SOURCE_DIR}/logging_sample_2.cpp )
SET( SOURCES_3 ${SOURCE_DIR}/logging_sample_3.cpp )
ADD_EXECUTABLE( logging_sample_1 ${SOURCES_1} )
ADD_EXECUTABLE( logging_sample_2 ${SOURCES_2} )
ADD_EXECUTABLE( logging_sample_3 ${SOURCES_3} )

