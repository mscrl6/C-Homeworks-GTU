all: clean compile run

compile: main.c
	@echo "-------------------------------------------"
	@ulimit -s 1639200
	@echo "Compiling..."
	@gcc main.c -o test

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
