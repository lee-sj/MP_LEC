

### lab3-2

// Write assembly program that sum from 1 to 10 and save the result at r10

// 1 + 2 + ... + 9 + n = n(n+1)/2 Math 

mov r0, #10 // n

add r1, r0, #1  // n+1

mul r0, r1 // n(n+1)

udiv r10, r0, #2 // n(n+1)/2


NOP

END

### lab3-3

// Assign some 1 byte hex values to r0
mov r0, #0x34

// Find number of 1's in r0 for binary expression

// Save number of 1's to r10


### 