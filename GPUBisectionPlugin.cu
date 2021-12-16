#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <emmintrin.h>
#include <sys/time.h>
#include "GPUBisectionPlugin.h"


void GPUBisectionPlugin::input(std::string file) {
   std::ifstream infile(file.c_str(), std::ios::in);
   infile >> N;
}

void GPUBisectionPlugin::run() {
  //Call GPU
  gpu(N);  
}

void GPUBisectionPlugin::output(std::string file) {
}
PluginProxy<GPUBisectionPlugin> GPUBisectionPluginProxy = PluginProxy<GPUBisectionPlugin>("GPUBisection", PluginManager::getInstance());

