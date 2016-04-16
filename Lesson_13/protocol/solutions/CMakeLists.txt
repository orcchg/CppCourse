SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( TARGET protocol_mc )  # mc - stands for 'multi-channel'
SET( SOURCES ${SOURCE_DIR}/protocol_1.cpp )
ADD_LIBRARY( ${TARGET} SHARED ${SOURCES} )

SET( SOURCES_TEST ${SOURCE_DIR}/protocol_mc_test.cpp )
ADD_EXECUTABLE( protocol_mc_test ${SOURCES_TEST} )
TARGET_LINK_LIBRARIES( protocol_mc_test protocol protocol_mc )

SET( TARGET_CONVERT_JSON convert_json )
SET( SOURCES_CONVERT_JSON ${SOURCE_DIR}/convert_json.cpp )
ADD_LIBRARY( ${TARGET_CONVERT_JSON} SHARED ${SOURCES_CONVERT_JSON} )
TARGET_LINK_LIBRARIES( ${TARGET_CONVERT_JSON} protocol protocol_mc )

SET( SOURCES_CONVERT_JSON_TEST ${SOURCE_DIR}/convert_json_test.cpp )
ADD_EXECUTABLE( convert_json_test ${SOURCES_CONVERT_JSON_TEST} )
TARGET_LINK_LIBRARIES( convert_json_test convert_json protocol protocol_mc )

