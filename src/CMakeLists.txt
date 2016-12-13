include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)


add_executable(main main.cpp Image.hpp Image.cpp ImageBW.cpp ImageBW.hpp PixelBW.hpp PixelBW.cpp
ImageRGB.hpp ImageRGB.cpp PixelRGB.hpp PixelRGB.cpp)
target_link_libraries(main "-lX11")
target_link_libraries(main "-pthread")

#Image.hpp Image.cpp

add_executable(pixel_bracket_test pixel_bracket_test.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp 
ImageBW.hpp ImageBW.cpp)
target_link_libraries(pixel_bracket_test "-lX11")
target_link_libraries(pixel_bracket_test "-pthread")


#add_executable(main main.cpp)
#target_link_libraries(main "-lX11")
#target_link_libraries(main "-pthread")