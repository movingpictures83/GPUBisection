__device__ double f (double x) {
    // To change function change this line
    // Future goal: Make function runtime-customizable
    return 128 * sin(x/256);
}

//Used for dividing the intervals of the graph into segments
//and to define number of threads and number of cores.
long N = (2496/(192))*1024;
