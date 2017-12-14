#include header and source files for builing a shared library
include_directories(
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/src
)

#generate dictionaries for STARWARE
ROOT_GENERATE_DICTIONARY(STARDict
${CMAKE_SOURCE_DIR}/include/STAR.h
)

ROOT_GENERATE_DICTIONARY(STARGuiDict
${CMAKE_SOURCE_DIR}/include/STARGui.h
)

ROOT_GENERATE_DICTIONARY(STARAnaDict
${CMAKE_SOURCE_DIR}/include/STARAnaGG.h
${CMAKE_SOURCE_DIR}/include/STARAnaTG.h
${CMAKE_SOURCE_DIR}/include/STARAnaDC.h
${CMAKE_SOURCE_DIR}/include/STARAnaDis.h
)

#ROOT_GENERATE_DICTIONARY(STARCalDict
#${CMAKE_SOURCE_DIR}/include/STARCal.h
#)

#generate a shared library including dictionaries
add_library(STARWARE SHARED
${CMAKE_SOURCE_DIR}/src/STAR.cc
STARDict.cxx

${CMAKE_SOURCE_DIR}/src/STARGui.cc
STARGuiDict.cxx

${CMAKE_SOURCE_DIR}/src/STARAnaGG.cc
${CMAKE_SOURCE_DIR}/src/STARAnaTG.cc
${CMAKE_SOURCE_DIR}/src/STARAnaDC.cc
${CMAKE_SOURCE_DIR}/src/STARAnaDis.cc
STARAnaDict.cxx

#${CMAKE_SOURCE_DIR}/src/STARCal.cc
#STARCalDict.cxx
)

target_link_libraries(STARWARE ${ROOT_LIBRARIES})
