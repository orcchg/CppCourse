SET( TARGET protocol_mc )  # mc - stands for 'multi-channel'
SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )
SET( SOURCES ${SOURCE_DIR}/protocol_1.cpp )
ADD_LIBRARY( ${TARGET} SHARED ${SOURCES} )

SET( SOURCES_TEST ${SOURCE_DIR}/protocol_mc_test.cpp )
ADD_EXECUTABLE( protocol_mc_test ${SOURCES_TEST} )
TARGET_LINK_LIBRARIES( protocol_mc_test protocol protocol_mc )

