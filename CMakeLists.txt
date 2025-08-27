cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(MiProyecto)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 11)

# Incluir el directorio 'include' para los encabezados
include_directories(include)

# Buscar todos los archivos .cpp en el directorio src
file(GLOB SOURCES "src/*.cpp")

# Especificar la carpeta donde se generará el ejecutable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Crear el ejecutable
add_executable(SituacionProblema ${SOURCES})

# Regla personalizada para ejecutar el programa automáticamente después de compilar
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SituacionProblema   # Ejecuta desde la carpeta build
    DEPENDS SituacionProblema
)

# Asegura que la compilación siempre ejecute el programa
add_dependencies(run SituacionProblema)
