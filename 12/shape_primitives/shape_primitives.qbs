import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        consoleApplication: true

        cpp.cxxLanguageVersion: "c++14"

        property path lib_dir: "../../../lib"

        files: [
            lib_dir +"/Graph_lib/Graph.cpp",
            lib_dir +"/Graph_lib/GUI.cpp",
            lib_dir +"/Graph_lib/Window.cpp",
            "main.cpp",
        ]

        cpp.includePaths: lib_dir
        Properties {
            condition: qbs.targetOS.contains("windows")
            cpp.defines: "WIN32"
            cpp.systemIncludePaths: "c:/mingw64/fltk-1.3.8/include"
            cpp.libraryPaths: "c:/mingw64/fltk-1.3.8/lib"
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
        Properties {
            condition: qbs.targetOS.contains("linux")
            cpp.systemIncludePaths: "/home/vova/opt/fltk-1.3.7/include"
            cpp.libraryPaths: "/home/vova/opt/fltk-1.3.7/lib"
            cpp.staticLibraries: [
                "fltk_images",
                "png",
                "z",
                "jpeg",
                "fltk",
                "Xrender",
                "Xcursor",
                "Xfixes",
                "Xext",
                "Xft",
                "fontconfig",
                "Xinerama",
                "dl",
                "m",
                "X11",
            ]
        }

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
