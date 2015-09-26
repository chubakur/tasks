all:
	cd libbloom && $(MAKE) all
	gcc btree.c main.c -Llibbloom/build -l:libbloom.so -o test
debug:
	cd libbloom && $(MAKE) all
	gcc -g btree.c main.c -Llibbloom/build -l:libbloom.so -o test
clean:
	cd libbloom && $(MAKE) clean
	rm test
