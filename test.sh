#!/bin/bash

BASEDIR=`pwd`
TESTDIR="$BASEDIR"
RESULTDIR="$BASEDIR"
TIMEOUT=15
LIMIT=20M
MAX=10
GCC=g++
SHELL="/bin/sh -c"

function log() {
    echo "$@" >&2
}

function write_status() {
    log "$1 $2"
}

function run_tests() {
    TMPDIR="$BASEDIR"
    CPPOPTS=-std=c++11
    for ID in `seq 1 $MAX`
    do
	SRC=`find "$TMPDIR" -name "fn*_prob$ID\_*.cpp" -print0`
	EXE="$TMPDIR/prog$ID"
	if [ -f "$SRC" ]
	then
	    $GCC -o "$EXE" $CPPOPTS "$SRC" 2>/dev/null
	    if [ -x "$EXE" ]
	    then
			for TESTIN in "$TESTDIR/$ID"?.test
			do
				TESTBASE=`basename "$TESTIN" .test`
				TESTOUT="$TESTIN".ans
				PROGRESULT="$RESULTDIR"/"$TESTBASE"
				PROGOUT="$PROGRESULT".out
				PROGERR="$PROGRESULT".err
				rm -f "$PROGOUT" "$PROGERR"
				STATUS=`timeout $TIMEOUT "$EXE" < "$TESTIN" 2> "$PROGERR" | head -c $LIMIT > "$PROGOUT"; echo ${PIPESTATUS[0]}`
				if [ $STATUS = 124 ]
				then
					write_status $TESTBASE "TO"
				elif [ $STATUS = 141 ]
				then
					write_status $TESTBASE "OL"
				elif [ $STATUS != 0 ]
				then
					write_status  $TESTBASE "RE"
				elif ! diff -b "$PROGOUT" "$TESTOUT" > /dev/null 2> /dev/null
				then
					write_status $TESTBASE "WA"
				fi
			done
	    else
			for TESTIN in "$TESTDIR/$ID"?.test
			do
				write_status $TESTBASE "CE"
			done
	    fi
	else
	    for TESTIN in "$TESTDIR/$ID"?.test
	    do
			write_status $TESTBASE "NA"
	    done
	fi
    done 
}

run_tests
