SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( SOURCES_LINK_0 ${SOURCE_DIR}/link_server_0.cpp )
SET( SOURCES_LINK_1 ${SOURCE_DIR}/link_server_1.cpp )
SET( SOURCES_LINK_2 ${SOURCE_DIR}/link_server_2.cpp )
SET( SOURCES_LINK_3 ${SOURCE_DIR}/link_server_3.cpp )
SET( SOURCES_0 ${SOURCE_DIR}/server_0.cpp )
SET( SOURCES_1 ${SOURCE_DIR}/server_1.cpp )
SET( SOURCES_2 ${SOURCE_DIR}/server_2.cpp )
SET( SOURCES_3 ${SOURCE_DIR}/server_3.cpp )
SET( SOURCES_3_1 ${SOURCE_DIR}/server_3_1.cpp )
SET( SOURCES_3_1_pico ${SOURCE_DIR}/server_3_1_pico.cpp )
SET( SOURCES_3_1_my ${SOURCE_DIR}/server_3_1_my.cpp )

ADD_EXECUTABLE( link_server_real ${SOURCES_LINK_0} )
ADD_EXECUTABLE( link_server_anketa ${SOURCES_LINK_1} )
ADD_EXECUTABLE( link_server_branchio ${SOURCES_LINK_2} )
ADD_EXECUTABLE( link_server_mailstat ${SOURCES_LINK_3} )
ADD_EXECUTABLE( server_0 ${SOURCES_0} )
ADD_EXECUTABLE( server_1 ${SOURCES_1} )
ADD_EXECUTABLE( server_2 ${SOURCES_2} )
TARGET_LINK_LIBRARIES( server_2 protocol )

# http Server
ADD_EXECUTABLE( server_3 ${SOURCES_3} )
TARGET_LINK_LIBRARIES( server_3 )
ADD_EXECUTABLE( server_3_1 ${SOURCES_3_1} )
TARGET_LINK_LIBRARIES( server_3_1 http_parser )
ADD_EXECUTABLE( server_3_1_pico ${SOURCES_3_1_pico} )
TARGET_LINK_LIBRARIES( server_3_1_pico pico_parser )
ADD_EXECUTABLE( server_3_1_my ${SOURCES_3_1_my} )
TARGET_LINK_LIBRARIES( server_3_1_my my_parser )

ADD_SUBDIRECTORY( solutions )

