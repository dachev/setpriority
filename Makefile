all:
	g++ -o setpriority -lboost_program_options-mt -lboost_regex-mt setpriority.cpp


install:
	cp setpriority ~/bin

clean:
	rm setpriority
