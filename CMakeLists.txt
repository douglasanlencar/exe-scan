cmake_minimum_required(VERSION 3.16)
project(Dizionario VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

add_executable(dizionario
    src/main.cpp
    src/DictionaryIndex.cpp
    src/DictionaryIndex.h
    src/JpgPaths.cpp
    src/JpgPaths.h
    src/PageImageView.cpp
    src/PageImageView.h
    src/MainWindow.cpp
    src/MainWindow.h
)

target_link_libraries(dizionario PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

target_compile_definitions(dizionario PRIVATE
    DIZIONARIO_VERSION="${PROJECT_VERSION}"
    DIZIONARIO_APP_ID="org.kde.dizionario"
)

include(GNUInstallDirs)

install(TARGETS dizionario RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES desktop/org.kde.dizionario.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
install(FILES metainfo/org.kde.dizionario.metainfo.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)
install(FILES icons/org.kde.dizionario.svg
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)
install(FILES data/original-page-keys.txt
        DESTINATION ${CMAKE_INSTALL_DATADIR}/dizionario)

enable_testing()
add_executable(test-dictionary-index tests/test_dictionary_index.cpp src/DictionaryIndex.cpp)
target_include_directories(test-dictionary-index PRIVATE src)
target_link_libraries(test-dictionary-index PRIVATE Qt6::Core)
add_test(NAME dictionary-index COMMAND test-dictionary-index)

add_executable(test-jpg-paths tests/test_jpg_paths.cpp src/JpgPaths.cpp)
target_include_directories(test-jpg-paths PRIVATE src)
target_link_libraries(test-jpg-paths PRIVATE Qt6::Core)
add_test(NAME jpg-paths COMMAND test-jpg-paths)
