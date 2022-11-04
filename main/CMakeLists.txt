include( ${PROJECT_DIR}/main/embed_tone.cmake )
set(COMPONENT_SRCS ./main.c)
set(COMPONENT_ADD_INCLUDEDIRS "." "tone")
register_component()
