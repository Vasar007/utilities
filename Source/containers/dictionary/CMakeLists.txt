include_directories(
    ${PROJECT_BINARY_DIR}
)

set(EXECUTABLE_NAME "Dictionary")

# Add source to this project's executable.
add_executable(${EXECUTABLE_NAME}
    "not_found_exception.hpp"

    "key_not_found_exception.hpp"
    
    "dictionary.hpp"
    
    "my_dictionary.hpp"
    "my_dictionary.inl"

    "main.cpp"
)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINKER_LANGUAGE CXX)
