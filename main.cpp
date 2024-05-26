#include <gtest/gtest.h>

using namespace std;

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}

// #include <container.h>
// #include <cstdlib>
// #include <iostream>

// struct Point {
//   int x, y;
// };

// int main(int argc, char **argv) {
//   Container<char, int, int, Point> c('a', 4, 10, Point{12, 1});
//   std::cout << c.getElement<char>(0) << std::endl;
//   std::cout << c.getElement<int>(1) << std::endl;
//   std::cout << c.getElement<int>(2) << std::endl;
//   std::cout << c.getElement<Point>(3).x << std::endl;
//   // void* memory = std::malloc(10*sizeof(int));
//   // allocate<10, char, int, int>(memory, 'a', 4, 10);
//   // std::cout << *(int*)(static_cast<char*>(memory) + sizeof(char) + sizeof(int));
//   // std::free(memory);
//   return 0;
// }