# Win32 Process Monitor 

A high-performance command line utility for Windows that lists all active system processes. This project demonstrates low level systems programming using the **Windows API** and memory management through system handles.

##  Features
*   **System Snapshots:** Uses `CreateToolhelp32Snapshot` to capture a stable view of the Windows kernel process list.
*   **PID Tracking:** Identifies the unique Process Identifier (PID) for every running application.
*   **Resource Management:** Implements safe Handle closing (`CloseHandle`) to prevent memory leaks.
*   **Formatted Output:** Clean, tabular CLI display using `<iomanip>`.

##  Technical Breakdown
The application uses the following Win32 logic:
1. **Take Snapshot:** Captures all current processes into a `HANDLE`.
2. **Iterate:** Uses `Process32First` and `Process32Next` to walk through the `PROCESSENTRY32` structure.
3. **Display:** Extracts the `th32ProcessID` and `szExeFile` (the .exe name) for output.



##  How to Run
1.  Ensure you are on a **Windows** environment.
2.  Open your C++ compiler (VS Code with MinGW, Visual Studio, etc.).
3.  Compile the source:
    ```bash
    g++ main.cpp -o SysMonitor.exe -lkernel32
    ```
4.  Run the executable:
    ```bash
    ./SysMonitor.exe
    ```

##  What I Learned
*   How the Windows Kernel assigns unique PIDs to applications.
*   The importance of `Handles` as "keys" to system resources.
*   Working with the Tool Help Library (`tlhelp32.h`).

## License
MIT License - feel free to use this for your own learning!
