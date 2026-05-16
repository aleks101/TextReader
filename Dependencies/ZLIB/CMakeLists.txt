include(FetchContent)

FetchContent_Declare(
    ZLIB
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.3.1
)

FetchContent_MakeAvailable(ZLIB)