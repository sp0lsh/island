set (TARGET imgui_example_app)

set (SOURCES "imgui_example_app.cpp")
set (SOURCES ${SOURCES} "imgui_example_app.h")

# Fix for "imgui.lib not found" link error with imgui.lib in Visual Studio.
# 3rdParty lib imgui is linked with target with PUBLIC option but dont propagate to this TARGET.
# Then imgui_example_app.cpp fails to link with unresolved external symbols from imgui.lib.
# So imgui.lib is hinted in imgui_example_app.cpp by `pragma comment( lib, "imgui.lib" )`.
if (WIN32)
    # Add `modules` folder with .lib libraries to "Additional Library Directories" in Visual Studio.
    link_directories("${CMAKE_BINARY_DIR}/modules/${CMAKE_BUILD_TYPE}")
endif()

if (${PLUGINS_DYNAMIC})

    add_library(${TARGET} SHARED ${SOURCES})
    
    add_dynamic_linker_flags()

    target_compile_definitions( ${TARGET} PUBLIC "PLUGINS_DYNAMIC")

else()

    # Adding a static library means to also add a linker dependency for our target
    # to the library.
    set (STATIC_LIBS ${STATIC_LIBS} ${TARGET} PARENT_SCOPE)

    add_library(${TARGET} STATIC ${SOURCES})

endif()

target_link_libraries(${TARGET} PUBLIC ${LINKER_FLAGS})

source_group(${TARGET} FILES ${SOURCES})