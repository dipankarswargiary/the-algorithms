# The Sorting Program

This program was written to sort some names in
alphabetical order. I specifically needed this
for myself - I was sorting my students' names
to make a list. So, I thought, why not write a
program for it?

So here it is.

- The program is written in C++ (since it happens
  to be my favorite language).

- It takes a text file as input through the command
  line and outputs the sorted list into a text file
  in the same directory where the binary is located.

- Used an array of length 26, each index representing
  a letter from the alphabet (each alphabet will have
  its own Red-Black tree for sorting).

- I have implemented red-black tree from scratch to
  sort the names starting with the same letters.

### Special implementation:

I used the pointer tagging technique to store the
colour of the node removing the need of a seperate
variable to store the colour of the node. The colour
is stored in the same variable as the parent's pointer
using the pointer tagging technique. Bassically I used
the last bit of the address as the colour flag since
the last 3 bits of a memory address are always `000`.
