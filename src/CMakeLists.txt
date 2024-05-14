file(GLOB_RECURSE DIR_LIB_SRCS *.cpp *.h *.hpp)
add_library(${PROJECT_NAME} SHARED ${DIR_LIB_SRCS} ${CINATRA})