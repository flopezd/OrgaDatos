cmake_minimum_required(VERSION 3.1)
project(OrgaDatos)

# Directorios a crear
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Flags para compilar
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11")

# Directorio destino
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Resources
set(RESOURCES resources)
file(COPY ${RESOURCES} DESTINATION ${PROJECT_SOURCE_DIR}/bin)

# Sources
set(SOURCE_FILES
    src/Common.h
    src/main.cpp
    )

add_executable(OrgaDatos ${SOURCE_FILES}  )

# Bibliotecas
target_link_libraries(OrgaDatos)

