# Указываем исходные файлы
set(SOURCES
    alg.cpp
    main.cpp
)

# Создаем исполняемый файл
add_executable(word_freq ${SOURCES})

# Убеждаемся, что include директория правильно настроена
target_include_directories(word_freq PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Для компиляции с флагом -Werror (если нужно)
if(CMAKE_CXX_FLAGS MATCHES "-Werror")
    target_compile_options(word_freq PRIVATE -Werror)
endif()

# Устанавливаем свойства для выходной директории
set_target_properties(word_freq PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
