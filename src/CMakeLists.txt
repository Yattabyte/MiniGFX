###################
### MiniGFX Lib ###
###################
set(Module MiniGFXCore)

# Configure and acquire files
set(FILES
    # Header files
    ${PROJECT_SOURCE_DIR}/external/glad/glad.h
    Buffer/glBuffer.hpp
    Buffer/glDynamicBuffer.hpp
    Buffer/glStaticBuffer.hpp
    Buffer/glVector.hpp
    Multibuffer/glMultiBuffer.hpp
    Multibuffer/glDynamicMultiBuffer.hpp
    Multibuffer/glStaticMultiBuffer.hpp
    Multibuffer/glMultiVector.hpp
    Model/model.hpp
    Model/modelGroup.hpp
    Texture/image.hpp
    Texture/texture1D.hpp
    Texture/texture2D.hpp
    Texture/texture3D.hpp
    Utility/indirectDraw.hpp
    Utility/mat.hpp
    Utility/shader.hpp
    Utility/vec.hpp

    # Source files
    ${PROJECT_SOURCE_DIR}/external/glad/glad.c
    Buffer/glDynamicBuffer.cpp
    Buffer/glStaticBuffer.cpp
    Model/model.cpp
    Model/modelGroup.cpp
    Texture/image.cpp
    Texture/texture1D.cpp
    Texture/texture2D.cpp
    Texture/texture3D.cpp
    Utility/indirectDraw.cpp
    Utility/shader.cpp
)

# Create Library using the supplied files
add_library(${Module} STATIC ${FILES})
target_include_directories(${Module}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add library dependencies
target_compile_features(${Module} PRIVATE cxx_std_17)
target_link_libraries(${Module} PUBLIC glfw OpenGL::GL)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CXX_COMPILER_VERSION}" LESS_EQUAL "9.0")
    target_link_libraries(${Module} PRIVATE c++experimental stdc++fs>)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_link_libraries(${Module} PRIVATE stdc++fs)
endif()

# Set all project settings
target_compile_Definitions(${Module} PRIVATE $<$<CONFIG:DEBUG>:DEBUG>)
set_target_properties(${Module} PROPERTIES VERSION ${PROJECT_VERSION})