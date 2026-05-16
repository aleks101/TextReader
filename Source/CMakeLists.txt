file(GLOB_RECURSE SRC_FILES *.cpp)

add_executable(TextReader ${SRC_FILES})

add_library(GLEW::GLEW STATIC IMPORTED GLOBAL)

set_target_properties(GLEW::GLEW PROPERTIES
    IMPORTED_LOCATION "${GLEW_ROOT}/build/lib/libglew32.a"
)
target_compile_definitions(TextReader PRIVATE GLEW_STATIC STB_IMAGE_IMPLEMENTATION)

target_link_libraries(TextReader PRIVATE
    GLEW::GLEW
    glfw
    opengl32
    freetype
)