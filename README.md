## External Sorting

**Aim:** External Sorting is a class of algorithms used to deal with massive amounts of data that do not fit in memory.The question aims at implementing one such type: K-Way merge sort algorithm to sort a very large array. This algorithm is a perfect example of the use of divide and conquer where with limited resources large problems are tackled by breaking the problem space into small computable subspaces and then operations are done on them.
</br></br>
**Input Constraints:** A file containing a large unsorted list of integers (will not fit in your usual Laptop RAM).
</br></br>
**Input Format:** Your code should take two arguments.
 First is the name of the input file.
 Second is the name of the output file.
 Example format: If your input file is at ./data/input.txt and if you need your output file at ./data/output.txt, your code should accept two arguments ./a.out “./data/input.txt” “./data/output.txt”
</br></br>
**Output:** A file containing non-Descending sorted list of the given integers.
</br></br>
**To generate an unsorted file:**</br>
```$ python generate_input.py <seed value> <unsorted file name> <number of values> <no of digits>```

