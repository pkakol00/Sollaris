if(EXISTS "/home/pkakol/Documents/PWR/teamwork/pz/sollaris/tests/my_tests[1]_tests.cmake")
  include("/home/pkakol/Documents/PWR/teamwork/pz/sollaris/tests/my_tests[1]_tests.cmake")
else()
  add_test(my_tests_NOT_BUILT my_tests_NOT_BUILT)
endif()