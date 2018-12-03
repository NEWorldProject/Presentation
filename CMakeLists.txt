nw_project_prepare(Core)

set(CMAKE_C_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

nwstd_add_library_slim(Presentation SHARED ${CMAKE_CURRENT_SOURCE_DIR}/Lib)

find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

target_include_directories(Presentation PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(Presentation PRIVATE Vulkan::Vulkan ${SDL2_LIBRARY})
target_link_libraries(Presentation PUBLIC Core Math task)

nwstd_add_executable_slim(PreTest ${CMAKE_CURRENT_SOURCE_DIR}/Test)
target_link_libraries(PreTest Presentation)
target_include_directories(PreTest PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(PreTest Vulkan::Vulkan ${SDL2_LIBRARY})
