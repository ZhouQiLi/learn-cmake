AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/hello2 SRC_LIST)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

ADD_LIBRARY(hello STATIC ${SRC_LIST})

FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION ${PROJECT_SOURCE_DIR}/include
        FILES_MATCHING PATTERN "*.h"
        )