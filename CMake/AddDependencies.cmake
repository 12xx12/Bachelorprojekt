function(build_dependencies)
    # Enumerate all submodule libraries
    # SQLiteCpp needs to be included before sqlite so the lsqlite target is available:
    set(DEPENDENCIES googletest SFML)
    foreach(DEPENDENCY ${DEPENDENCIES})
        # Check that the libraries are present:
        if (NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/${DEPENDENCY}/CMakeLists.txt")
            message(FATAL_ERROR "${DEPENDENCY} is missing in folder lib/${DEPENDENCY}. Have you initialized and updated the submodules / downloaded the extra libraries?")
        endif()

        # Include all the libraries
        # We use EXCLUDE_FROM_ALL so that only the explicit dependencies are compiled
        add_subdirectory("lib/${DEPENDENCY}" EXCLUDE_FROM_ALL)
    endforeach()
endfunction()
