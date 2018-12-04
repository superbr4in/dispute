cmake_minimum_required ( VERSION 3.8 )

set ( CMAKE_CXX_STANDARD 17 )

add_library ( dispute SHARED
    "source/flag.cpp"
    "source/flag_filter.cpp"
    "source/format_string.cpp" )

target_include_directories ( dispute PUBLIC
    "include/" )

add_executable ( dispute-test
    "test/dispute_test.cpp" )

target_link_libraries ( dispute-test
    dispute )
