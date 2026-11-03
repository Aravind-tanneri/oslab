#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void translate_addresses(int page_size, int num_pages, const vector<int>& page_table, const vector<int>& logical_addresses) {
    cout << left << setw(18) << "Logical Address"
         << setw(12) << "Page No."
         << setw(10) << "Offset"
         << setw(12) << "Frame No."
         << setw(18) << "Physical Address" << "\n";
    cout << string(70, '-') << "\n";

    for (int log_addr : logical_addresses) {
        int page_no = log_addr / page_size;
        int offset = log_addr % page_size;

        if (page_no >= num_pages || page_no < 0 || page_table[page_no] == -1) {
            cout << left << setw(18) << log_addr
                 << setw(12) << page_no
                 << setw(10) << offset
                 << setw(12) << "INVALID"
                 << setw(18) << "Page Fault / Trap" << "\n";
        } else {
            int frame_no = page_table[page_no];
            int phys_addr = (frame_no * page_size) + offset;
            cout << left << setw(18) << log_addr
                 << setw(12) << page_no
                 << setw(10) << offset
                 << setw(12) << frame_no
                 << setw(18) << phys_addr << "\n";
        }
    }
}

int main() {
    cout << "=======================================================\n";
    cout << " Lab 8: Address Translation Using Paging\n";
    cout << "=======================================================\n";

    cout << "\n--- Task 1: Basic Paging (Sample from Lab Task 8) ---\n";
    int page_size = 100;
    int num_pages = 5;
    // Mapping: Page 0->3, 1->0, 2->4, 3->1, 4->2
    vector<int> page_table = {3, 0, 4, 1, 2};
    vector<int> logical_addresses = {50, 120, 250, 315, 425};

    cout << "Page Size: " << page_size << " bytes\n";
    cout << "Page Table [Page -> Frame]: ";
    for (int i = 0; i < num_pages; i++) {
        cout << "[" << i << "->" << page_table[i] << "] ";
    }
    cout << "\n\n";

    translate_addresses(page_size, num_pages, page_table, logical_addresses);

    cout << "\n--- Task 2: Paging Architecture Analysis ---\n";
    cout << "Given: Logical Address Space = 4 KB, Physical Memory = 8 KB, Page Size = 1 KB\n";
    cout << "  - Number of Pages  = 4 KB / 1 KB  = 4 pages\n";
    cout << "  - Number of Frames = 8 KB / 1 KB  = 8 frames\n";
    cout << "  - Bits for Page Number = log2(4)  = 2 bits\n";
    cout << "  - Bits for Offset      = log2(1024)= 10 bits\n";
    cout << "  - Bits for Frame Number= log2(8)  = 3 bits\n";
    cout << "  - Page Table Size      = 4 entries * 3 bits (rounded to bytes)\n";

    cout << "\n--- Task 3: Interactive / Dynamic Translation ---\n";
    cout << "Enter 1 to run custom address translation, or 0 to exit: ";
    int choice = 0;
    if (cin >> choice && choice == 1) {
        cout << "Enter Page Size (bytes): ";
        cin >> page_size;
        cout << "Enter Number of Pages: ";
        cin >> num_pages;
        page_table.resize(num_pages);
        cout << "Enter Frame Number for each page (0 to " << num_pages - 1 << "):\n";
        for (int i = 0; i < num_pages; i++) {
            cout << "  Page " << i << " -> Frame: ";
            cin >> page_table[i];
        }

        int q;
        cout << "Enter number of logical addresses to translate: ";
        cin >> q;
        vector<int> addrs(q);
        cout << "Enter " << q << " logical addresses:\n";
        for (int i = 0; i < q; i++) {
            cin >> addrs[i];
        }
        cout << "\nTranslation Table:\n";
        translate_addresses(page_size, num_pages, page_table, addrs);
    }

    return 0;
}
