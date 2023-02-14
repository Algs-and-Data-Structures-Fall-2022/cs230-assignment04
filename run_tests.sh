# Compile:
g++ -std=c++17 -o assignment assignment01.cpp

# Change this to the name of your subfolder:
pth=$"tests/"

for test in ${pth}*.txt; do

    # Run the compiled file on the input:
    echo -en ">>> running ${test}\n"
    ./assignment "${test}"

    # Verify this input's collapse sequence:
     
done
