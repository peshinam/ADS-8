set(SOURCES
    alg.cpp
    main.cpp
)
add_executable(word_freq ${SOURCES})
target_include_directories(word_freq PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
if(CMAKE_CXX_FLAGS MATCHES "-Werror")
    target_compile_options(word_freq PRIVATE -Wno-unused-result)
endif()
set_target_properties(word_freq PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
