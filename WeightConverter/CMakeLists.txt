cmake_minimum_required(VERSION 3.16)

# Имя проекта — zhrcpo1 (как ваша папка). Из него получится zhrcpo1.exe
project(zhrcpo1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Автоматическая обработка Qt-файлов ---
# AUTOMOC — автоматически запускает moc для классов с Q_OBJECT
# AUTOUIC — автоматически обрабатывает .ui файлы (если появятся)
# AUTORCC — автоматически обрабатывает .qrc ресурсы (если появятся)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --- Путь к Qt для MSVC ---
# ВАЖНО: проверьте, что эта папка существует у вас на диске!
set(CMAKE_PREFIX_PATH "D:/Qt/6.11.2/msvc2022_64")

# --- Флаги для корректной работы с кириллицей в MSVC ---
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# --- Поиск Qt6 (нужны модули Core, Gui, Widgets) ---
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# --- Список исходных файлов проекта ---
add_executable(${PROJECT_NAME} WIN32
    main.cpp
    MeasurementType.h
    ModelChangeListener.h
    WeightModel.h
    WeightModel.cpp
    InputForm.h
    InputForm.cpp
    MainView.h
    MainView.cpp
    WeightController.h
    WeightController.cpp
)

# --- Связываем наш проект с библиотеками Qt ---
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# --- Автоматически копируем DLL-файлы Qt рядом с .exe ---
# Это нужно, чтобы программа запускалась без "танцев с бубнами" и PATH
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "D:/Qt/6.11.2/msvc2022_64/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Копирование DLL Qt рядом с исполняемым файлом..."
)

# --- Автоматическое развёртывание Qt-плагинов после сборки ---
# Ищем windeployqt в папке Qt
find_program(WINDEPLOYQT_EXECUTABLE
    NAMES windeployqt
    HINTS "D:/Qt/6.11.2/msvc2022_64/bin"
)

if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            --debug
            --no-translations
            "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Развёртывание плагинов Qt..."
    )
endif()