find_package(antlr4-runtime CONFIG REQUIRED)
include_directories(${VCPKG_INSTALLED_DIR}/x64-linux/include/antlr4-runtime)

set(GENERATED generatedG/GrammarParser.cpp
              generatedG/GrammarLexer.cpp
              generatedT/TokensParser.cpp
              generatedT/TokensLexer.cpp )

add_executable(generator generate.cpp ${GENERATED})
target_link_libraries(generator PRIVATE ${VCPKG_INSTALLED_DIR}/x64-linux/lib/libantlr4-runtime.a)
target_include_directories(generator PRIVATE ../lib generatedG generatedT)
