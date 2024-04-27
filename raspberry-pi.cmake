# Cross compile exentions for Raspberry pi

# Cross compiler options
set(CMAKE_SYSTEM_NAME LINUX)

set(CMAKE_C_COMPILER   /opt/homebrew/opt/arm-linux-gnueabihf-binutils)
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/arm-linux-gnueabihf-binutils)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH  $ENV{HOME}/projects/targets/pit)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)