for i in {1..1000}
do
    last=$(tail -n 1 numbers.txt)
    echo $((last+1)) >> numbers.txt
done

# in order to run 2 processes, a bash command is used:
# sh ex2WithRace.sh & sh ex2WithRace.sh

# as a result, doubled numbers appeared from number 2