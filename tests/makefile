all: .SILENT

.SILENT:
	./tests
	lcov --capture --directory ../src/libs/ --output-file gcov.info
	lcov --directory . --zerocounters
	lcov --remove gcov.info '/usr/*' --output-file gcov_filtered.info
	genhtml gcov_filtered.info --output-directory html_cov
	rm *.info