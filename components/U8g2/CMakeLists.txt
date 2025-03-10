# Busca todos os arquivos .c na pasta csrc/
file(GLOB U8G2_C_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/clib/*.c")

# Busca todos os arquivos .cpp na pasta src/
file(GLOB U8G2_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

idf_component_register(
    SRCS ${U8G2_C_FILES} ${U8G2_CPP_FILES}
    INCLUDE_DIRS "src" "src/clib"
    REQUIRES arduino
)