This is Gregor Richards' parser and abstract syntax tree generator for C. I
used a YACC parser from Jeff Lee, the README for which is included below. The
structure can be understood best by looking through dispast.c.

To get to the code generation step, add generate_* functions to replace the
disp_* functions, then copy dispast.c to generate.c and hack all the disp_*
functions into code generators. It will do depth-first code generation, which
should be fine in most scenarios.

Note that you will have to add your own semantic checker. You can do this as
part of the code generator, if you please, or you can add yet another depth-
first descender based on the disp_* functions to do semantic checking.


Here is the README for the grammar:

The files in this directory contain the ANSI C grammar from the April 30, 1985
draft of the proposed standard. This copy also incorporates all bug fixes I
have seen since the last two postings. With a little work this grammar can
be made to parse the C that most of us know and love (sort of).

There is one bug fix to the grammar that is in this posting. On line 295
of gram.y it previously read declaration_specifiers instead of
type_specifier_list as it does now. I believe the folks at the ANSI committee
made a mistake since if you replace the line with what the original read
you will end up with 16 shift/reduce errors and 2 reduce/reduce errors
(the good ones). As it is, it only has 1 shift/reduce error that occurs
on the if/else construct. YACC creates the correct parser and I don't want
to ugly my grammar up.

Anyway, all cumquats unite and generate this sucker. Then just sit and play
with it. Remember, the grammar accepts things like

	"Hello, world"++;
	--1.23456;
	*'a'

but this is not a bug, but simply a shuffling of the checking into the
semantic analysis. If you want to hack it up to do lvalue and rvalue
checking, I'm sure the ANSI committee would be glad to have your changes.
Don't send'em to me though. I don't want'em. Wear this in good health.

Jeff Lee
gatech!jeff	jeff@gatech	jeff%gatech.CSNet@CSNet-Relay.ARPA
