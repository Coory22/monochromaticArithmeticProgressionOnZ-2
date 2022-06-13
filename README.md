"# monochromaticArithmeticProgressionOnZ-2" 

The bias c code bias towards a vertical coloring. performance of this code was touch upon in my capstone paper.

The unbiased C code was optimized to the fullest extent it could be. We may need to add memory to the count in the numOfmap method because right now it only stores 32 bit integers. this code will be the hardest to read because I was trying to use C to its fullest extent and was able to make two times faster than it was previously. Also, this code will allow for bigger values of n because all the memory is stored on the heap. if needed you can add more threads, but I was limited by the number of CPU I have on my laptop. I was able to run 50x50 grid in 20 minute and foresee an 100x100 in 24 hours.

The python code will be the easiest to read so I would recommend starting there that also bias towards a vertical coloring.
