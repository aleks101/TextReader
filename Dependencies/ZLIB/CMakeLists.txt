include(FetchContent)

FetchContent_Declare(
    ZLIB
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.3.1
)

FetchContent_MakeAvailable(ZLIB)

# Help find_package(ZLIB) inside PoDoFo
set(ZLIB_INCLUDE_DIR "${zlib_SOURCE_DIR}" CACHE PATH "")
set(ZLIB_LIBRARY zlibstatic CACHE STRING "")