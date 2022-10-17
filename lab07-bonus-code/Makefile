# CSCI 2021 lab Makefile
AN = lab07-bonus
CLASS = 2021

CFLAGS = -Wall -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	coins_mainb \

all: $(PROGRAMS)

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test-quiz                # run tests that verify quiz answers'
	@echo '  > make test-code                # run tests that verify code is correct'
	@echo '  > make test                     # run all automated tests'
	@echo '  > make clean-tests              # remove all test results'

############################################################
# 'make zip' to create zip file for submission
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi

coins_mainb : coins_mainb.c coins_funcs_asmb.s
	$(CC) -o $@ $^

################################################################################
# testing targets
test-setup :
	@chmod u+rx testy test_quiz_filter

test : test-setup all coins_mainb
	./testy test_coins_mainb.org $(testnum)

# test-quiz: test-setup QUESTIONS.txt
# 	./testy test_$(AN).org 1


clean:
	rm -f *.o $(PROGRAMS)

clean-tests:
	rm -rf test-results/

