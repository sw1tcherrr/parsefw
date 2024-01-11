#!/usr/bin/sh

antlr4 -Dlanguage=Cpp Grammar.g4 -no-listener -no-visitor -long-messages -o generatedG

antlr4 -Dlanguage=Cpp Tokens.g4 -no-listener -no-visitor -long-messages -o generatedT
