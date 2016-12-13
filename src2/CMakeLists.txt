include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)


add_executable(main_temp main_temp.cpp Image.hpp PixelBW.hpp PixelBW.cpp PixelRGB.hpp PixelRGB.cpp)
target_link_libraries(main_temp "-lX11")
target_link_libraries(main_temp "-pthread")

