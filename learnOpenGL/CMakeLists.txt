add_executable (learnOpenGL
    "main.cpp"
    "../external/Glad/src/glad.c"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET learnOpenGL PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(learnOpenGL PRIVATE
    "../external/glfw/include"
    "../external/Glad/include"
    "../external/glm"
)

target_link_libraries(learnOpenGL PRIVATE
    "${CMAKE_SOURCE_DIR}/external/glfw/lib-vc2022/glfw3.lib"
    opengl32
)
