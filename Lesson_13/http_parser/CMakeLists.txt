SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( TARGET_HTTP http_parser )
SET( SOURCES_HTTP ${SOURCE_DIR}/http_parser.c )
ADD_LIBRARY( ${TARGET_HTTP} SHARED ${SOURCES_HTTP} )

SET( TARGET_PICO pico_parser )
SET( SOURCES_PICO ${SOURCE_DIR}/picohttpparser.c )
ADD_LIBRARY( ${TARGET_PICO} SHARED ${SOURCES_PICO} )

SET( TARGET_MY my_parser )
SET( SOURCES_MY ${SOURCE_DIR}/my_parser.cpp )
ADD_LIBRARY( ${TARGET_MY} SHARED ${SOURCES_MY} )

SET( SOURCES_MY_TEST ${SOURCE_DIR}/my_parser_test.cpp )
ADD_EXECUTABLE( my_parser_test ${SOURCES_MY_TEST} )
TARGET_LINK_LIBRARIES( my_parser_test my_parser )

ADD_SUBDIRECTORY( solutions )

