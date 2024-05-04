# 这个是LEXER. 需要在PARSER生成之后再生成.
lex.yy.cpp: ../lex/igniter.l igniter.tab.hpp
	flex -o lex.yy.cpp ../lex/igniter.l

# 生成PARSER.
igniter.tab.hpp igniter.tab.cpp: ../lex/igniter.yxx
	bison -d -v --report-file=report.log ../lex/igniter.yxx -o igniter.tab.cpp
