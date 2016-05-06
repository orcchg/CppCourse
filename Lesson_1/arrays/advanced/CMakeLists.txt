SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )
SET( SOURCES
    ${SOURCE_DIR}/cache/cache.cpp
    ${SOURCE_DIR}/cache/cache_estimate.cpp
)
INCLUDE_DIRECTORIES( ${SOURCE_DIR}/include )
ADD_EXECUTABLE( cache_estimate ${SOURCES} )

