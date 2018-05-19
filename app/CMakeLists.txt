# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include(AndroidNdkModules)
android_ndk_import_module_cpufeatures()

add_library(libpng STATIC IMPORTED)
set_target_properties(libpng PROPERTIES IMPORTED_LOCATION ${ANDROID_NDK}/libs/libpng-android/obj/local/${ANDROID_ABI}/libpng.a)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library(    # Sets the name of the library.
                native-engine-lib SHARED

                # Provides a relative path to your source file(s).
                src/main/cpp/native-engine-lib.cpp
                src/main/cpp/jawe/engine.cpp
                src/main/cpp/jawe/updater.cpp
                src/main/cpp/jawe/texture.cpp
                src/main/cpp/jawe/cube_texture.cpp
                src/main/cpp/jawe/png_loader.cpp
                src/main/cpp/jawe/framebuffer.cpp
                src/main/cpp/jawe/random.cpp
                src/main/cpp/jaf/settings.cpp
                src/main/cpp/jaf/engine.cpp
                src/main/cpp/jaf/particle_shader.cpp
                src/main/cpp/jaf/bloom_shader.cpp
                src/main/cpp/jaf/skybox_shader.cpp
                src/main/cpp/jaf/updater.cpp
                src/main/cpp/jaf/particle.cpp
                src/main/cpp/jaf/director.cpp
                src/main/cpp/jaf/sequence.cpp
                src/main/cpp/jaf/sequence_creator.cpp
                src/main/cpp/jaf/rocket_behaviour.cpp
                src/main/cpp/jaf/rocket_creator.cpp
                src/main/cpp/jaf/trail_behaviour.cpp
                src/main/cpp/jaf/burst_behaviour.cpp
                src/main/cpp/jaf/slow_burst_behaviour.cpp
                src/main/cpp/jaf/burst_creator.cpp
                src/main/cpp/jaf/slow_burst_creator.cpp
             )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log)

find_library( OPENGL_LIB GLESv3 )
find_library( EGL_LIB EGL )
find_library( ANDROID_LIB android)

target_include_directories(native-engine-lib PRIVATE ${ANDROID_NDK}/libs/libpng-android/jni/)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-engine-lib
                       libpng
                       z
                       ${OPENGL_LIB}
                       ${EGL_LIB}
                       ${ANDROID_LIB}
                       cpufeatures

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib})