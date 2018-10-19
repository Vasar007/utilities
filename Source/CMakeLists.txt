include_directories(
    ${PROJECT_BINARY_DIR}
)

set(EXECUTABLE_NAME "utilities")

add_executable(${EXECUTABLE_NAME}
    config/config.hpp

    data_structure/data_structure.hpp
    data_structure/data_structure.cpp

    logger/logger.hpp
    logger/logger.inl
    logger/logger.cpp

    network_interface/network_interface.hpp
    network_interface/network_interface.cpp
    
    parsing/parsing.hpp
    parsing/parsing.inl
    parsing/parsing.cpp

    print/print.hpp
    print/print.inl
    print/print.cpp

    printer/printer.hpp
    printer/printer.inl
    printer/printer.cpp

    utility/utility.hpp
    utility/utility.inl
    utility/utility.cpp

    utility/valid_expression.hpp
)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINKER_LANGUAGE CXX)
