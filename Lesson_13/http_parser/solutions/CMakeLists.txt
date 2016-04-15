SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( TARGET_X_MY x_my_parser )
SET( SOURCES_X_MY ${SOURCE_DIR}/x_my_parser.cpp )
ADD_LIBRARY( ${TARGET_X_MY} SHARED ${SOURCES_X_MY} )

SET( SOURCES_X_MY_TEST ${SOURCE_DIR}/x_my_parser_test.cpp )
ADD_EXECUTABLE( x_my_parser_test ${SOURCES_X_MY_TEST} )
TARGET_LINK_LIBRARIES( x_my_parser_test x_my_parser my_parser )

