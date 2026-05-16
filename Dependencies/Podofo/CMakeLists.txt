include(FetchContent)

FetchContent_Declare(
    Podofo
    GIT_REPOSITORY https://github.com/podofo/podofo.git
    GIT_TAG 1.1.0
)

FetchContent_MakeAvailable(Podofo)