#include <iostream>
#include <vector>

using namespace std;

int main() {
    int page_size = 100;
    // Page table from Lab 8: page 0->3, 1->0, 2->4, 3->1, 4->2
    vector<int> page_table = {3, 0, 4, 1, 2};
    vector<int> logical_addrs = {50, 120, 250, 315, 425};

    cout << "=== Lab 8: Address Translation Using Paging ===\n";
    cout << "Page Size = " << page_size << " bytes\n\n";
    cout << "Logical\tPage\tOffset\tFrame\tPhysical Address\n";
    cout << "------------------------------------------------\n";

    for (int addr : logical_addrs) {
        int page = addr / page_size;
        int offset = addr % page_size;
        int frame = page_table[page];
        int phys_addr = (frame * page_size) + offset;

        cout << addr << "\t" << page << "\t" << offset << "\t" << frame << "\t" << phys_addr << "\n";
    }

    return 0;
}
