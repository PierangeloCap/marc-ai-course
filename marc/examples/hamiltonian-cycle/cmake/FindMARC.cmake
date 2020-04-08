set(FIND_MARC_LIB ../../build)

find_library(MARC_LIBRARY NAMES MARC HINTS ${FIND_MARC_LIB})

set(MARC_INCLUDE ../../header)
