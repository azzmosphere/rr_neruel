# Cross compile exentions for Raspberry pi

# Cross compiler options
set(CMAKE_SYSTEM_NAME LINUX)

set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH /Users/newuser/projects/targets/pi)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(GCC_COVERAGE_LINK_FLAGS    "--specs=nosys.specs")