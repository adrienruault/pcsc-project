cmake_minimum_required(VERSION 3.5)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)




add_executable(main_temp main_temp.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(main_temp "-lX11")
target_link_libraries(main_temp "-pthread")

add_executable(user user.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp PixelRGB.hpp PixelRGB.cpp
HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp)
target_link_libraries(user "-lX11")
target_link_libraries(user "-pthread")

add_executable(hanning_low_pass hanning_low_pass.cpp ComplexNumber.hpp ComplexNumber.cpp)

add_executable(test_histogram test_histogram.cpp Image.cpp PixelBW.cpp PixelRGB.cpp
Filter.hpp Fourier_Transform.hpp HistogramBW.cpp HistogramRGB.cpp Filter.cpp
ComplexNumber.cpp Error.hpp)
target_link_libraries(test_histogram "-lX11")
target_link_libraries(test_histogram "-pthread")

add_executable(test_fft test_fft.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_fft "-lX11")
target_link_libraries(test_fft "-pthread")

add_executable(test_low_pass test_low_pass.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_low_pass "-lX11")
target_link_libraries(test_low_pass "-pthread")

add_executable(test_high_pass test_high_pass.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_high_pass "-lX11")
target_link_libraries(test_high_pass "-pthread")

add_executable(test_band_pass test_band_pass.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_band_pass "-lX11")
target_link_libraries(test_band_pass "-pthread")
