# This is the Makefile to use for Homework Assignment #3
# To use, at the prompt, type:
#
# 	make calc		# This will make executable calc
# or
# 	make driver		# This will make executable driver
# or
#	make clean		# This will safely remove old stuff

DIR=$(HOME)/../public/hw5

all:	driver1 driver2 calc

calc:	calc.o list.o main.o mylib.o stack.o
	gcc -Wall -pedantic -o calc -g calc.o list.o main.o mylib.o stack.o

calc.o:	calc.c calc.h list.h mylib.h stack.h
	gcc -Wall -pedantic -c -g calc.c

driver1:	driver1.o list.o mylib.o stack.o
	gcc -Wall -pedantic -o driver1 -g driver1.o list.o mylib.o stack.o

driver2:	driver2.o list.o mylib.o stack.o
	gcc -Wall -pedantic -o driver2 -g driver2.o list.o mylib.o stack.o

driver1.o:	driver1.c list.h mylib.h stack.h
	gcc -Wall -pedantic -c -g driver1.c

driver2.o:	driver2.c list.h mylib.h stack.h
	gcc -Wall -pedantic -c -g driver2.c

list.o:	list.c list.h
	gcc -Wall -pedantic -c -g list.c

mylib.o:	mylib.c mylib.h
	gcc -Wall -pedantic -c -g mylib.c

main.o:	main.c calc.h list.h mylib.h stack.h
	gcc -Wall -pedantic -c -g main.c

stack.o:	list.h stack.c stack.h
	gcc -Wall -pedantic -c -g stack.c

valgrind_driver1: driver1
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./driver1 $(DEBUG)

valgrind_driver2: driver2
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./driver2 $(DEBUG)

valgrind_calc: calc
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./calc $(DEBUG)

clean:
	rm -f *.o calc driver1 driver2 core $(HOME)/core

new:
	make clean
	make

backup:	Makefile *.[ch]
	cp -p *.[ch] Makefile $(HOME)/hw5/backup

directories:
	if [ ! -d $(HOME)/hw5 ]; then mkdir $(HOME)/hw5; fi
	if [ ! -d $(HOME)/hw5/backup ]; then mkdir $(HOME)/hw5/backup; fi

install:
	cp -p $(DIR)/Makefile $(DIR)/*.h $(DIR)/main.c \
	$(DIR)/mylib.c $(DIR)/stack.c $(DIR)/calc.c \
	$(DIR)/.cproject $(DIR)/.project \
	$(DIR)/.hw5.vcproj $(DIR)/.hw5.sln \
	$(DIR)/*.empty $(DIR)/driver*.c $(HOME)/hw5
	# cp -p $(DIR)/../_vimrc.student $(HOME)/.vimrc

upgrade:
	cp -p $(DIR)/main.c $(DIR)/driver?.c

public:
	make new
	
	if [ ! -d $(DIR) ]; then mkdir $(DIR); fi
	
	# lock public directory
	chmod 700 $(DIR)
	#
	# copy all files to directory
	cp -p .cproject .project .hw5.sln .hw5.vcproj Makefile \
	*.empty *.c *.h driver1 driver2 calc $(DIR)
	
	# remove solution source files from public directory
	rm -f $(DIR)/list.c
	
	# strip executables of debugging information
	strip $(DIR)/driver1
	strip $(DIR)/driver2
	strip $(DIR)/calc
	
	#
	# set correct permissions on source files
	chmod 644 $(DIR)/Makefile $(DIR)/*.[ch] $(DIR)/*.empty \
		$(DIR)/.*project $(DIR)/.hw5.vcproj $(DIR)/.hw5.sln
	
	# set restrictive permissions on solution source files before due date
	chmod 640 $(DIR)/calc.c
	chmod 640 $(DIR)/mylib.c
	
	# set correct permissions on solution source files (after due date)
	chmod 644 $(DIR)/calc.c
	chmod 644 $(DIR)/mylib.c
	#
	# set correct permissions on executables
	chmod 711 $(DIR)/calc $(DIR)/driver1 $(DIR)/driver2
	
	# unlock public directory for tutors (before assignment handed out)
	chmod 750 $(DIR)

	# move html files to public_html directory
	rm -r $(HOME)/public_html/hw5/
	mkdir $(HOME)/public_html/hw5
	cp -p *html $(HOME)/public_html/hw5
	chmod 744 $(HOME)/public_html/hw5/*html
	chmod 750 $(HOME)/public_html/hw5/

	# unlock public directory
	chmod 755 $(DIR)
	chmod go+rx $(HOME)/public_html/hw5/
	#
	#scp -p Makefile *.[ch] cs12xzz@ieng6-202:~/hw5
