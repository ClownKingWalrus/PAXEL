# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Paxel_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Paxel_autogen.dir\\ParseCache.txt"
  "Paxel_autogen"
  )
endif()
