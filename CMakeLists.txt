cmake_minimum_required ( VERSION 3.8 )

set ( CMAKE_CXX_STANDARD 17 )

set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin/" )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/" )

add_library ( dispute SHARED
    "source/flag.cpp"
    "source/flag_filter.cpp"
    "source/format_string.cpp" )

target_include_directories ( dispute PUBLIC
    "include/"
    "submodules/simple-visitation/include/" )

add_executable ( dispute_test
    "test/dispute_test.cpp" )

target_link_libraries ( dispute_test
    dispute )
