SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( SOURCES_0 ${SOURCE_DIR}/http_0.cpp )
SET( SOURCES_0_1 ${SOURCE_DIR}/http_0_1.cpp )
SET( SOURCES_0_2 ${SOURCE_DIR}/http_0_2.cpp )
SET( SOURCES_1 ${SOURCE_DIR}/http_1.cpp )
SET( SOURCES_1_1 ${SOURCE_DIR}/http_1_1.cpp )
SET( SOURCES_1_2 ${SOURCE_DIR}/http_1_2.cpp )
SET( SOURCES_2 ${SOURCE_DIR}/http_2.cpp )
SET( SOURCES_2_1 ${SOURCE_DIR}/http_2_1.cpp )
SET( SOURCES_3 ${SOURCE_DIR}/http_3.cpp )
SET( SOURCES_3_1 ${SOURCE_DIR}/http_3_1.cpp )
SET( SOURCES_4 ${SOURCE_DIR}/http_4.cpp )
SET( SOURCES_5 ${SOURCE_DIR}/http_5.cpp )
SET( SOURCES_6 ${SOURCE_DIR}/http_6.cpp )
SET( SOURCES_7 ${SOURCE_DIR}/http_7.cpp )
SET( SOURCES_8 ${SOURCE_DIR}/http_8.cpp )
SET( SOURCES_9 ${SOURCE_DIR}/http_9.cpp )

# Http request
ADD_EXECUTABLE( http_0 ${SOURCES_0} )
TARGET_LINK_LIBRARIES( http_0 curl curlpp )
ADD_EXECUTABLE( http_0_1 ${SOURCES_0_1} )
TARGET_LINK_LIBRARIES( http_0_1 curl curlpp )
ADD_EXECUTABLE( http_0_2 ${SOURCES_0_2} )
TARGET_LINK_LIBRARIES( http_0_2 curl curlpp )

# GET XML response
ADD_EXECUTABLE( http_1 ${SOURCES_1} )
TARGET_LINK_LIBRARIES( http_1 curl curlpp )
ADD_EXECUTABLE( http_1_1 ${SOURCES_1_1} )
TARGET_LINK_LIBRARIES( http_1_1 tinyxml curl curlpp )
ADD_EXECUTABLE( http_1_2 ${SOURCES_1_2} )
TARGET_LINK_LIBRARIES( http_1_2 tinyxml curl curlpp )

# GET Json response
ADD_EXECUTABLE( http_2 ${SOURCES_2} )
TARGET_LINK_LIBRARIES( http_2 curl curlpp )
ADD_EXECUTABLE( http_2_1 ${SOURCES_2_1} )
TARGET_LINK_LIBRARIES( http_2_1 curl curlpp )

# http sample exchange
ADD_EXECUTABLE( http_3 ${SOURCES_3} )
TARGET_LINK_LIBRARIES( http_3 )
ADD_EXECUTABLE( http_3_1 ${SOURCES_3_1} )
TARGET_LINK_LIBRARIES( http_3_1 http_parser )

# POST, PUT, DELETE Json response
ADD_EXECUTABLE( http_4 ${SOURCES_4} )
TARGET_LINK_LIBRARIES( http_4 curl curlpp )

ADD_EXECUTABLE( http_5 ${SOURCES_5} )
TARGET_LINK_LIBRARIES( http_5 curl curlpp )

ADD_EXECUTABLE( http_6 ${SOURCES_6} )
TARGET_LINK_LIBRARIES( http_6 curl curlpp )

ADD_EXECUTABLE( http_7 ${SOURCES_7} )
TARGET_LINK_LIBRARIES( http_7 curl curlpp )

ADD_EXECUTABLE( http_8 ${SOURCES_8} )
TARGET_LINK_LIBRARIES( http_8 curl curlpp )

ADD_EXECUTABLE( http_9 ${SOURCES_9} )
TARGET_LINK_LIBRARIES( http_9 curl curlpp )

ADD_SUBDIRECTORY( solutions )

