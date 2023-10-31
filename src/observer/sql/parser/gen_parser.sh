#!/bin/bash
flex --outfile lex_sql.cpp --header-file=lex_sql.h lex_sql.l
/usr/sbin/bison -d --output yacc_sql.cpp yacc_sql.y
# `which bison` -d --output yacc_sql.cpp yacc_sql.y
#  -Wcounterexamples