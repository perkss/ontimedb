# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${OnTimeDb_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST "${OnTimeDb_SOURCE_DIR}/include/")

# Make an automatic library - will be static or dynamic based on user setting
add_library(collections hash_table.c ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(collections PUBLIC ../include)

# IDEs should put the headers in a nice place
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
