# GPUBisection
# Language: CUDA
# Input: TXT
# Output: SCREEN
# Tested with: PluMA 1.0, CUDA 10

Bisection Method on the GPU.

Original authors: Miguel Jardines, Tariq Juman, Daniel Raad, and Carlos M. Martinez

The plugin accepts as input a TXT file containing the number of intervals.

The function to bisect is in a file: function.h.  Future goal is to customize this.

Output will be to the screen, each interval and its solution (assuming one).
