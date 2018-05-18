file(REMOVE_RECURSE
  "libvolk_gnsssdr.pdb"
  "libvolk_gnsssdr.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/volk_gnsssdr_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
