add_library(
        glad STATIC 
        src/glad.c  
        include/glad.h 
        include/khrplatform.h)
target_include_directories(glad PUBLIC include/)
