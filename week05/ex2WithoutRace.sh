for i in {1..1000}
do
    if ln numbers.txt file.lock; then
        last=$(tail -n 1 numbers.txt)
        echo $((last+1)) >> numbers.txt
    fi
    rm file.lock
done

# in order to run 2 processes, a bash command is used:
# sh ex2WithoutRace.sh & sh ex2WithoutRace.sh

# now a process cannot write to file if a lock file exists
# as a result the race condition occured only on number 242 (but it still exists)