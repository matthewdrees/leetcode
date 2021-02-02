
psp_stats : psp_stats.cpp statistics.cpp statistics.hpp
	clang++ -std=c++17 statistics.cpp psp_stats.cpp -o $@ -lboost_program_options

test_integration : test_integration.cpp integration.cpp integration.hpp statistics.cpp statistics.hpp
	clang++ -std=c++17 statistics.cpp test_integration.cpp -o $@; ./test

test_statistics : test_statistics.cpp statistics.cpp statistics.hpp
	clang++ -std=c++17 statistics.cpp test_statistics.cpp -o $@; ./test
