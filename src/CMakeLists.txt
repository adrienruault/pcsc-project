include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)


add_executable(main_temp main_temp.cpp Image.hpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp)
target_link_libraries(main_temp "-lX11")
target_link_libraries(main_temp "-pthread")
