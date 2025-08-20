#!/bin/bash
mkdir -p test;
cp pipex test;
cd test;

# Invlid number of arguments test case
test_invalid_number_of_arguments() {
    local testname="$1"
    shift
    touch error_log;
    ./pipex "$@" 2>error_log;
    local status=$?

    if [ "$status" -ne 1 ]; then
        echo "$testname: FAILED (exit status: $status, expected 1)"
        return
    fi
    if [ -s error_log ]; then
        echo "$testname SUCESS"
    else
		echo "$testname: FAILED (message not found)"
		echo "--- stderr ---"
		cat error_log
    fi

}
echo "--test_invalid_number_of_arguments--"
test_invalid_number_of_arguments test_invalid_number_of_arguments0
test_invalid_number_of_arguments test_invalid_number_of_arguments1 file
test_invalid_number_of_arguments test_invalid_number_of_arguments2 file "cat"
test_invalid_number_of_arguments test_invalid_number_of_arguments3 file "cat" "cat"

# Normal test casunwritable_filee
test() {
	touch input; touch output; touch expected_output; touch error_log; touch expected_error_log;
    bash -c "
        bash -c \"$CMD1\" < input | \
        bash -c \"$CMD2\" > expected_output
    " 2>expected_error_log
    local expected_status=$?
	./pipex input "$CMD1" "$CMD2" output 2> error_log
	local status=$?
    local testname=$1
    if [ "$status" -ne "$expected_status" ]; then
        echo "$testname: failed (exit status: $status, expected $expected_status)"
        return
    fi
	if diff output expected_output > /dev/null; then
		echo "$testname: SUCESS"
	else
		echo "$testname: FAILED"
		diff output expected_output
	fi
}
echo "--Normal test case--"
CMD1="ls -l"
CMD2="wc -w"
test test1

echo "In front of you" > input
CMD1="grep of"
CMD2="wc -c"
test test2

CMD1="tr a-z A-Z"
CMD2="cat"
test test3

CMD1="tr a-z A-Z"
CMD2="cat"
test test4

echo "In front of you\nBefind of you\nBesides you" > input
CMD1="head -n 2"
CMD2="wc -w"
test test5

echo "banana\napple\nbanana\ncherry" > input
CMD1="sort"
CMD2="uniq"
test test6

echo "--Invalid command test--"
CMD1="not_exist"
CMD2="cat"
test test1

CMD1="cat"
CMD2="not_exist"
test test2

CMD1="        " # space
CMD2="cat"
test test3
# exit status: (zsh: 127, bash: 0)
CMD1="cat"
CMD2="          " # space
test test4

CMD1="          " # space and tab
CMD2="cat"
test test5
# exit status: (zsh: 127, bash: 0)
CMD1="cat"
CMD2="          " # space and tab
test test6
# exit status: (zsh: 126, bash: 127)
# I think this test's expected status is incorrect.
CMD1="cat"
CMD2=""
test test7

CMD1=""
CMD2="cat"
test test8
# Test no permission
CMD1="x11vnc"
CMD2="cat"
test test9

CMD1="cat"
CMD2="x11vnc"
test test10

leak_test(){
    local testname="$1"
    shift
    local logfile="valgrind_$testname.log"

    valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
             --log-file="$logfile" ./pipex "$@"

    if grep -q "All heap blocks were freed -- no leaks are possible" "$logfile"; then
        echo "$testname: success"
    else
        echo "$testname: failed"
        echo "--- LEAK SUMMARY for $testname ---"
        awk '/LEAK SUMMARY:/,/^$/' "$logfile"
    fi
}
echo "--memory leak test case--"
leak_test leak_test1 foo
leak_test leak_test2 foo foo
echo "Nothing better than walking" > input
leak_test leak_test3 input cat cat output
leak_test leak_test4 input not_exist cat output
leak_test leak_test5 input cat not_exist output
leak_test leak_test6 input "   " cat output
leak_test leak_test7 input cat "          " output
leak_test leak_test8 input "" cat output
leak_test leak_test9 input cat "" output
leak_test leak_test10 input x11vnc cat output
leak_test leak_test11 input cat x11vnc output
rm -f not_exist_file
leak_test leak_test12 not_exist_file cat cat output
touch unreadable_file
touch unwritable_file
chmod 000 unreadable_file
chmod 555 unwritable_file
leak_test leak_test13 unreadable_file cat cat output
leak_test leak_test14 input cat cat unwritable_file
