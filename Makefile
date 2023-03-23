all: 
	mkdir -p buildfolder
	cd buildfolder && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j 6 && ./demo
	gcc t.c && ./a.out
run:
	cd buildfolder &&  make -j 6 && ./demo

clean: clean_test
	rm -r buildfolder
	rm -r cmake/CMakeFiles cmake/antlr4_runtime cmake/CMakeCache.txt

all_test: MyGrammar.g4
	antlr4 MyGrammar.g4 -Dlanguage=Cpp #-no-listener -no-visitor
clean_test:
	-rm MyGrammarLexer.cpp MyGrammarParser.cpp MyGrammarBaseListener.cpp MyGrammarListener.cpp
	-rm MyGrammarLexer.h MyGrammarParser.h MyGrammarBaseListener.h MyGrammarListener.h
	-rm MyGrammar.interp MyGrammarLexer.interp MyGrammar.tokens MyGrammarLexer.tokens
