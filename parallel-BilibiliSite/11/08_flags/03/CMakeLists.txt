add_executable(main)
file(GLOB sources CONFIGURE_DEPENDS *.cpp *.h)
target_sources(main PUBLIC ${sources})

if (WIN32)
    target_compile_definitions(main PUBLIC MY_NAME="Bill Gates")
elseif (UNIX AND NOT APPLE)
    target_compile_definitions(main PUBLIC MY_NAME="Linus Torvalds")
elseif (APPLE)
    target_compile_definitions(main PUBLIC MY_NAME="Steve Jobs")
endif()
