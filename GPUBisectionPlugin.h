#include "Plugin.h"
#include "PluginProxy.h"
#include <string>
#include <map>

#include "function.h"

class GPUBisectionPlugin : public Plugin {

	public:
		void input(std::string file);
		void run();
		void output(std::string file);
	private:
                std::string inputfile;
		std::string outputfile;
		float* a;
		int N;
};

//Device bisection method
__device__ void doBisectionGPU (double a, double b, double t1, long maxNumOfIterations){
	
    double p1 = 0.0;
//Step 1
    long i = 0;
	// Left y-axis point of current interval [a,b]
    double fOfA = f(a);

//Step 2
    while (i <= maxNumOfIterations) {
//Step 3
        double p = ((a + b) / 2);
        double fOfP = f(p);

        if (fabs((p - p1) / p) < t1 && (p != p1)){
            printf("Interval %f-%f:  Iteration no. %3d X = %7.5f\n", a, b, i, p);
            break;
        }

//Step 5
        i = i + 1;

//Step 6
        if (fOfA * f(p) > 0) {
            a = p;
            fOfA = f(p);
        } 
		else
            b = p;

        // update p1
        p1 = p;

//Step 7
        if (i == maxNumOfIterations) {
            printf ("Method failed after %ld iterations\n",
                               maxNumOfIterations);
        }
    }
}	
// Device parallelized N-section method
__global__ void gpu_doBisection(long N, double aStart, double h) {

   long element = blockIdx.x*blockDim.x + threadIdx.x;
   
   // As long as element is less than number of threads, step into if statement
   if (element < N){
	   //f(X) times f(Xi+1) = result
	   double result = f((aStart+element*h)) * f((aStart+(element+1)*h));
	   
	   // Return only negative results indexes
	   if(result<0){
		   //Calculate left and right enpoint of negative results at which roots lay.
		  // Left Xi and Right Xi+1 endpoints for each N
		  double aSmaller = aStart + (element*h);
		  double bSmaller = aStart + ((element+1)*h);
		  doBisectionGPU (aSmaller, bSmaller, 0.0000001, 500); 
	   }
   }
}

// Host CPU method
void gpu(long N) 
{
	//Declaring GPU threads and cores based on N
	long numThreads = 1024;
	long numCores = N / 1024 + 1;

	//Start and end of graph
	double aStart = 400;
	double b = 1200000000;
	
	//Brake the graph into smaller intervals
	double h = (b-aStart)/N;
	
	//Call GPU method
	gpu_doBisection<<<numCores, numThreads>>>(N, aStart, h);
   
   cudaDeviceSynchronize();
}
