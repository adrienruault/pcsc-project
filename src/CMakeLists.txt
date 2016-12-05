include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)


add_executable(main main.cpp ImageBW.cpp ImageBW.hpp Image.hpp Image.cpp 
PixelBW.hpp PixelBW.cpp)
target_link_libraries(main "-lX11")
target_link_libraries(main "-pthread")


#add_executable(main main.cpp)
#target_link_libraries(main "-lX11")
#target_link_libraries(main "-pthread")