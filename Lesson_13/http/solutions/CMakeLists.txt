SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( SOURCES_1_3 ${SOURCE_DIR}/http_1_3.cpp )
SET( SOURCES_2_2 ${SOURCE_DIR}/http_2_2.cpp )
SET( SOURCES_2_3 ${SOURCE_DIR}/http_2_3.cpp )
SET( SOURCES_4_1 ${SOURCE_DIR}/http_4_1.cpp )
SET( SOURCES_4_2 ${SOURCE_DIR}/http_4_2.cpp )

# GET XML response
ADD_EXECUTABLE( http_1_3 ${SOURCES_1_3} )
TARGET_LINK_LIBRARIES( http_1_3 tinyxml curl curlpp )

# GET Json response
ADD_EXECUTABLE( http_2_2 ${SOURCES_2_2} )
TARGET_LINK_LIBRARIES( http_2_2 curl curlpp )
ADD_EXECUTABLE( http_2_3 ${SOURCES_2_3} )
TARGET_LINK_LIBRARIES( http_2_3 curl curlpp )

# POST, PUT, DELETE Json response
ADD_EXECUTABLE( http_4_1 ${SOURCES_4_1} )
TARGET_LINK_LIBRARIES( http_4_1 curl curlpp )
ADD_EXECUTABLE( http_4_2 ${SOURCES_4_2} )
TARGET_LINK_LIBRARIES( http_4_2 curl curlpp )

