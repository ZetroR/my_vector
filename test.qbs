import qbs

CppApplication {
    consoleApplication: true

    property path lib_dir: "lib"

    files: [
        "data/image.jpg",
        lib_dir +"/Graph_lib/Graph.cpp",
        lib_dir +"/Graph_lib/GUI.cpp",
        lib_dir +"/Graph_lib/Window.cpp",
        "data/input.txt",
        "data/output.txt",
        "main.cpp",
        "std_lib_facilities.h",
    ]

    cpp.includePaths: lib_dir
    Properties {
        cpp.defines: "WIN64"
        cpp.systemIncludePaths: "c:/mingw64/fltk-1.3.8_win64/include"
        cpp.libraryPaths: "c:/mingw64/fltk-1.3.8_win64/lib"
        cpp.driverLinkerFlags: "-mwindows"
        cpp.staticLibraries: [
            "fltk_images",
            "fltk",
            "fltk_png",
            "fltk_z",
            "fltk_jpeg",
            "ole32",
            "uuid",
            "comctl32",
        ]
    }


    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
