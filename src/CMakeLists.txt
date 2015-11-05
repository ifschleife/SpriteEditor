set(SOURCES
	main.cpp
    mainwindow.cpp
    spritearea.cpp
    )

set(HEADERS
    mainwindow.h
    spritearea.h
    )

set(UI_FILES
    mainwindow.ui
    )

set(QRC_FILES
    # ../res/res.qrc
    )

find_package(Qt5Widgets REQUIRED)

include_directories(${QT_INCLUDES})

link_directories(${QT_LIBRARIES})

add_executable(SpriteEditor WIN32
    ${SOURCES} ${HEADERS} ${UI_FILES} ${QRC_FILES})

qt5_use_modules(SpriteEditor Widgets)
