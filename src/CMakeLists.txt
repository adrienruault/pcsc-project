cmake_minimum_required(VERSION 2.6)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)

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

add_executable(test_fft_color test_fft_color.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_fft_color "-lX11")
target_link_libraries(test_fft_color "-pthread")

add_executable(test_low_pass test_low_pass.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_low_pass "-lX11")
target_link_libraries(test_low_pass "-pthread")

add_executable(test_low_pass_color test_low_pass_color.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_low_pass_color "-lX11")
target_link_libraries(test_low_pass_color "-pthread")

add_executable(test_high_pass test_high_pass.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_high_pass "-lX11")
target_link_libraries(test_high_pass "-pthread")

add_executable(test_high_pass_color test_high_pass_color.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_high_pass_color "-lX11")
target_link_libraries(test_high_pass_color "-pthread")

add_executable(test_band_pass test_band_pass.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_band_pass "-lX11")
target_link_libraries(test_band_pass "-pthread")

add_executable(test_band_pass_color test_band_pass_color.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_band_pass_color "-lX11")
target_link_libraries(test_band_pass_color "-pthread")

add_executable(test_user user.cpp Image.hpp Image.cpp PixelBW.hpp PixelBW.cpp
PixelRGB.hpp PixelRGB.cpp HistogramBW.hpp HistogramBW.cpp HistogramRGB.hpp HistogramRGB.cpp Fourier_Transform.hpp
ComplexNumber.hpp ComplexNumber.cpp Filter.hpp Filter.cpp)
target_link_libraries(test_user "-lX11")
target_link_libraries(test_user "-pthread")
