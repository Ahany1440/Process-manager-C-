#include <iostream>     // Standard input-output stream library
#include <windows.h>    // The core Windows library (required for Handles and system types)
#include <tlhelp32.h>   // Tool Help library (required for taking snapshots of processes)
#include <iomanip>      // Used for "io manipulators" to format the output table
using namespace std;    // This allows us to use cout, endl, left, etc., without the std:: prefix

void ListProcesses() {
    // 1. Create a "Snapshot" handle. 
    // TH32CS_SNAPPROCESS tells Windows to include all processes in the snapshot.
    // The '0' means we are capturing processes for the entire system.
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    // Check if the snapshot handle is valid; if not, the system couldn't take the "photo."
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cout << "Failed to create snapshot." << endl;
        return; 
    }

    // PROCESSENTRY32 is a struct that holds details about a process (Name, PID, etc.)
    PROCESSENTRY32 pe32;
    
    // You MUST set the size of the structure before using it for the API to work correctly.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the very first process in the snapshot.
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap); // Always clean up handles to avoid memory leaks.
        return;
    }

    // Formatting the header: 'left' aligns text, 'setw(10)' sets a column width.
    cout << left << setw(10) << "PID" << " | " << "Process Name" << endl;
    cout << "------------------------------------------" << endl;

    // Start a loop to walk through every "entry" in the snapshot we took.
    do {
        // th32ProcessID is the ID, szExeFile is the name of the executable.
        cout << left << setw(10) << pe32.th32ProcessID << " | " << pe32.szExeFile << endl;

    // Process32Next moves to the next process. It returns 'false' when the list ends.
    } while (Process32Next(hProcessSnap, &pe32));

    // Release the snapshot handle back to the OS.
    CloseHandle(hProcessSnap);
}

int main() {
    // Execute our listing function
    ListProcesses();
    
    // Pause so you can actually read the list before the window closes
    system("pause"); 
    
    return 0; 
}