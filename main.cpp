// Ryan Mathews
// Dr. Passos
// 4103 OS
// 11/12/2024
//
// Read in file, searched through file to see if page is there, if page is not
// their add one to page fault and then go into our secondchance algorithm to
// replace the page.
//
// Sources: ChatGpt,
// https://www.geeksforgeeks.org/second-chance-or-clock-page-replacement-policy/,
// and https://www.educative.io/answers/what-is-the-second-chance-algorithm.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const int page_size = 1024;
const int memory = 64 * 1024;
const int frames = memory / page_size;

void paging(std::string filename);

int main() {
  paging("data-file-spice.txt");
  return 0;
}

void paging(std::string filename) {
  std::ifstream fin(filename);
  std::vector<int> memory(frames, -1);
  std::vector<bool> second_chance(frames, false);
  int page_faults = 0;
  int replace = 0;

  std::string line;
  while (std::getline(fin, line)) {
    std::stringstream str(line);
    unsigned int address;
    str.ignore(2);
    str >> std::hex >> address;

    // Get hex number
    int page = address / page_size;

    bool page_found = false;
    for (int i = 0; i < memory.size() && !page_found; ++i) {
      if (memory[i] == page) {
        second_chance[i] = true;
        page_found = true;
      }
    }
    if (!page_found) {
      page_faults++;
    }
    bool replaced = false;
    while (!replaced) {
      if (!second_chance[replace]) {
        memory[replace] = page;
        second_chance[replace] = true;
        replaced = true;

      } else {
        second_chance[replace] = false;
      }
      replace = (replace + 1) % frames;
    }
  }
  std::cout << "Page faults = " << page_faults << std::endl;
}
