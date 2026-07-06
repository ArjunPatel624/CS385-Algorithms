#!/bin/bash

targetfile=sieve.cpp
cppfile=sieve.cpp
maxtime=2

if [ ! -f "$targetfile" ]; then
    echo "Error: file $targetfile not found"
    echo "Final score: score - penalties = 0 - 0 = 0"
    exit 1
fi

# Required by the Honor System
missing_name=0
head -n 20 "$targetfile" | egrep -i "author.*[a-zA-Z]+"
if [ $? -ne 0 ]; then
    echo "Student name missing"
    missing_name=1
fi

# Required by the Honor System
missing_pledge=0
head -n 20 "$targetfile" | egrep -i "I.*pledge.*my.*honor.*that.*I.*have.*abided.*by.*the.*Stevens.*Honor.*System"
if [ $? -ne 0 ]; then
    echo -e "Pledge missing"
    missing_pledge=1
fi

# Compiling
echo
results=$(make 2>&1)
if [ $? -ne 0 ]; then
    echo "$results"
    echo "Final score: score - penalties = 0 - 0 = 0"
    exit 1
fi

num_tests=0
num_right=0
memory_problems=0
command="./${cppfile%.*}"

run_test_with_args_and_input() {
    ((num_tests++))
    echo -n "Test $num_tests..."

    args="$1"
    input="$2"
    expected_output="$3"

    outputfile=$(mktemp)
    inputfile=$(mktemp)
    statusfile=$(mktemp)

    echo -e "$input" > "$inputfile"

    start=$(date +%s.%N)
    # Run run run, little program!
    (timeout --preserve-status "$maxtime" "$command" $args < "$inputfile" &> "$outputfile"; echo $? > "$statusfile") &> /dev/null
    end=$(date +%s.%N)
    status=$(cat "$statusfile")

    case $status in
        # $command: 128 + SIGBUS = 128 + 7 = 135 (rare on x86)
        135)
            echo "failed (bus error)"
            ;;
        # $command: 128 + SIGSEGV = 128 + 11 = 139
        139)
            echo "failed (segmentation fault)"
            ;;
        # $command: 128 + SIGTERM (sent by timeout(1)) = 128 + 15 = 143
        143)
            echo "failed (time out)"
            ;;
        *)
            # bash doesn't like null bytes so we substitute by hand.
            computed_output=$(sed -e 's/\x0/(NULL BYTE)/g' "$outputfile")
            if [ "$computed_output" = "$expected_output" ]; then
                ((num_right++))
                echo $start $end | awk '{printf "ok (%.3fs)\tvalgrind...", $2 - $1}'
                # Why 93?  Why not 93!
                (valgrind --leak-check=full --error-exitcode=93 $command $args < "$inputfile" &> /dev/null; echo $? > "$statusfile") &> /dev/null
                vgstatus=$(cat "$statusfile")
                case $vgstatus in
                    # valgrind detected an error when running $command
                    93)
                        ((memory_problems++))
                        echo "failed"
                        ;;
                    # valgrind not installed or not in $PATH
                    127)
                        echo "not found"
                        ;;
                    # valgrind: 128 + SIGBUS = 128 + 7 = 135 (rare on x86)
                    135)
                        ((memory_problems++))
                        echo "failed (bus error)"
                        ;;
                    # valgrind: 128 + SIGSEGV = 128 + 11 = 139
                    139)
                        ((memory_problems++))
                        echo "failed (segmentation fault)"
                        ;;
                    # compare with expected status from running $command without valgrind
                    $status)
                        echo "ok"
                        ;;
                    *)
                        ((memory_problems++))
                        echo "unknown status $vgstatus"
                        ;;
                esac
            else
                echo "failed"
                echo "==================== Expected ===================="
                echo "$expected_output"
                echo "==================== Received ===================="
                echo "$computed_output"
                echo "=================================================="
            fi
            ;;
    esac
    rm -f "$inputfile" "$outputfile" "$statusfile"
}

run_test_with_args() {
    run_test_with_args_and_input "$1" "" "$2"
}
run_test_with_input() {
    run_test_with_args_and_input "" "$1" "$2"
}

############################################################
run_test_with_input "x x x" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: Error: Input is not an integer."
run_test_with_input "-1 2 3" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: Error: Input must be an integer >= 0."
run_test_with_input "0 a 2" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: Error: Input is not an integer."
run_test_with_input "1 -1 3" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: Error: Input must be an integer >= lower limit."
run_test_with_input "2 9 33" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: Error: Input must be a digit."
run_test_with_input "0 100 0" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: 
Bad digit: 0
Number of good primes found: 25
Good primes between 0 and 100:
 2  3  5  7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97"
run_test_with_input "100 200 0" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: 
Bad digit: 0
Number of good primes found: 17
Good primes between 100 and 200:
113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199"
run_test_with_input "0 200 3" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: 
Bad digit: 3
Number of good primes found: 29
Good primes between 0 and 200:
  2   5   7  11  17  19  29  41  47  59  61  67  71  79  89  97 101 107 109 127
149 151 157 167 179 181 191 197 199"
run_test_with_input "2 800 4" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: 
Bad digit: 4
Number of good primes found: 109
Good primes between 2 and 800:
  2   3   5   7  11  13  17  19  23  29  31  37  53  59  61  67  71  73  79  83
 89  97 101 103 107 109 113 127 131 137 139 151 157 163 167 173 179 181 191 193
197 199 211 223 227 229 233 239 251 257 263 269 271 277 281 283 293 307 311 313
317 331 337 353 359 367 373 379 383 389 397 503 509 521 523 557 563 569 571 577
587 593 599 601 607 613 617 619 631 653 659 661 673 677 683 691 701 709 719 727
733 739 751 757 761 769 773 787 797"
run_test_with_input "2 1600 7" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: 
Bad digit: 7
Number of good primes found: 161
Good primes between 2 and 1600:
   2    3    5   11   13   19   23   29   31   41   43   53   59   61   83   89
 101  103  109  113  131  139  149  151  163  181  191  193  199  211  223  229
 233  239  241  251  263  269  281  283  293  311  313  331  349  353  359  383
 389  401  409  419  421  431  433  439  443  449  461  463  491  499  503  509
 521  523  541  563  569  593  599  601  613  619  631  641  643  653  659  661
 683  691  809  811  821  823  829  839  853  859  863  881  883  911  919  929
 941  953  983  991 1009 1013 1019 1021 1031 1033 1039 1049 1051 1061 1063 1069
1091 1093 1103 1109 1123 1129 1151 1153 1163 1181 1193 1201 1213 1223 1229 1231
1249 1259 1283 1289 1291 1301 1303 1319 1321 1361 1381 1399 1409 1423 1429 1433
1439 1451 1453 1459 1481 1483 1489 1493 1499 1511 1523 1531 1543 1549 1553 1559
1583"
run_test_with_input "3 97 2" "*********************** Sieve of Eratosthenes (MODIFIED) ***********************
Search for good primes between: 
Bad digit: 2
Number of good primes found: 22
Good primes between 3 and 97:
 3  5  7 11 13 17 19 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97"
############################################################
echo
echo "Total tests run: $num_tests"
echo "Number correct : $num_right"
score=$((100 * $num_right / $num_tests))
echo "Percent correct: $score%"
if [ $missing_name == 1 ]; then
    echo "Missing Name: -5"
fi
if [ $missing_pledge == 1 ]; then
    echo "Missing or incorrect pledge: -5"
fi

if [ $memory_problems -gt 1 ]; then
    echo "Memory problems: $memory_problems (-5 each, max of -15)"
    if [ $memory_problems -gt 3 ]; then
        memory_problems=3
    fi
fi

penalties=$((5 * $missing_name + 5 * $missing_pledge + 5 * $memory_problems))
final_score=$(($score - $penalties))
if [ $final_score -lt 0 ]; then
    final_score=0
fi
echo "Final score: score - penalties = $score - $penalties = $final_score"

make clean > /dev/null 2>&1
