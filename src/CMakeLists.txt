include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)

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

add_executable(first_test first_test.cpp)
target_link_libraries(first_test "-lX11")
target_link_libraries(first_test "-pthread")

add_executable(ex1lab2IP ex1lab2IP.cpp)
target_link_libraries(ex1lab2IP "-lX11")
target_link_libraries(ex1lab2IP "-pthread")

add_executable(test_mask image_tools.h image_tools.cpp MyMask.h MyMask.cpp test_mask.cpp )
target_link_libraries(test_mask "-lX11")
target_link_libraries(test_mask "-pthread")
