#include "Runtime.hpp"

int main(int argc, char** argv){
   try{
       for (int i = 0; i < argc; ++i) {
           SrslRuntime::Runtime runtime(argv[i]);
           runtime.execute();
       }
   } catch(std::exception& e){
       std::cerr << e.what() << std::endl;
       return 1;
   }
}
