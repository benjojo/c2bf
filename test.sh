#!/bin/bash
BFI=egobfi16

# Test 1
echo -n "Test  1: "
./wrapper/c2bf cc/tests/test1.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "HELLO WORLD!" ] ; then echo "PASS"
else echo "FAIL"
fi

# Test 2
echo -n "Test  2: "
./wrapper/c2bf cc/tests/test2.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "A" ] ; then echo "PASS"
else echo "FAIL"
fi

# Test 3
echo -n "Test  3: "
./wrapper/c2bf cc/tests/test3.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "A" ] ; then echo "PASS"
else echo "FAIL"
fi

# Test 4
echo -n "Test  4: "
./wrapper/c2bf cc/tests/test4.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "A" ] ; then echo "PASS"
else echo "FAIL"
fi

# Test 5
echo -n "Test  5: "
./wrapper/c2bf cc/tests/test5.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "Y" ] ; then echo "PASS"
else echo "FAIL"
fi

# Test 7
echo -n "Test  7: "
./wrapper/c2bf cc/tests/test7.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "Hello world!" ] ; then echo "PASS"
else echo "FAIL"
fi

# Test 8
echo -n "Test  8: "
./wrapper/c2bf cc/tests/test8.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "ABCDEFGHIJ" ] ; then echo "PASS"
else echo "FAIL"
fi

# Test 9
echo -n "Test  9: "
./wrapper/c2bf cc/tests/test9.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "Hello world!" ] ; then echo "PASS"
else echo "FAIL"
fi

# Test 10
echo -n "Test 10: "
./wrapper/c2bf cc/tests/test10.c
export OUTP="`$BFI a.b`"
if [ "$OUTP" = "Hello world!" ] ; then echo "PASS"
else echo "FAIL"
fi

# Done
rm -f a.b
