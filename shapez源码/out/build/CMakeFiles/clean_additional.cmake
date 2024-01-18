# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\shapez_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\shapez_autogen.dir\\ParseCache.txt"
  "shapez_autogen"
  )
endif()
