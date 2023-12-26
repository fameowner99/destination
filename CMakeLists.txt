cmake_minimum_required(VERSION 3.26)

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake")

project(Destinations)

set(CMAKE_CXX_STANDARD 17)

find_package(Crow CONFIG REQUIRED)

# Workaround https://github.com/CrowCpp/Crow/issues/661
list(REMOVE_ITEM _CROW_ICD "_CROW_ICD-NOTFOUND")
set_target_properties(Crow::Crow PROPERTIES INTERFACE_COMPILE_DEFINITIONS "${_CROW_ICD}")

add_executable(Destinations src/main.cpp src/simple_server.cpp src/data_storage.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        Crow::Crow)

file(COPY "${CMAKE_SOURCE_DIR}/destinations.csv" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
