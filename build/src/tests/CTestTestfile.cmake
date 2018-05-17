# CMake generated Testfile for 
# Source directory: /home/ubuntu/passive_radar/gnss-sdr/src/tests
# Build directory: /home/ubuntu/passive_radar/gnss-sdr/build/src/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(control_thread_test "control_thread_test")
set_tests_properties(control_thread_test PROPERTIES  TIMEOUT "30")
add_test(flowgraph_test "flowgraph_test")
set_tests_properties(flowgraph_test PROPERTIES  TIMEOUT "30")
add_test(gnss_block_test "gnss_block_test")
add_test(gnuradio_block_test "gnuradio_block_test")
add_test(trk_test "trk_test")
subdirs(unit-tests/signal-processing-blocks/libs)
