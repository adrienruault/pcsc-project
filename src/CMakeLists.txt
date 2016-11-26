include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lena lena.cpp)
target_link_libraries(lena "-lX11")
target_link_libraries(lena "-pthread")

add_executable(flag flag.cpp)
target_link_libraries(flag "-lX11")
target_link_libraries(flag "-pthread")

add_executable(z_trans_test z_trans_test.cpp digital_filter.h digital_filter.cpp)
target_link_libraries(z_trans_test "-lX11")
target_link_libraries(z_trans_test "-pthread")

add_executable(rescale rescale.cpp digital_filter.h digital_filter.cpp)
target_link_libraries(rescale "-lX11")
target_link_libraries(rescale "-pthread")
