SET( TARGET tinyxml )
SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )
SET( SOURCES
    ${SOURCE_DIR}/tinystr.cpp
    ${SOURCE_DIR}/tinyxml.cpp
    ${SOURCE_DIR}/tinyxmlerror.cpp
    ${SOURCE_DIR}/tinyxmlparser.cpp
)
ADD_LIBRARY( ${TARGET} SHARED ${SOURCES} )

