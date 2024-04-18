# Trust Aware Scheduling of Online Tasks in Fog Nodes

This project focuses on Trust Aware Scheduling of Online Tasks in Fog Nodes. The code provided is for a simulation written in C++ to demonstrate the concept. Below are the instructions for compiling and running the code on a Windows platform using the `g++` compiler.

## Compilation and Execution

1. **Platform:** Windows
2. **Compiler:** g++
3. **File to Compile:** `main.cpp`

### Steps:

1. **Open Command Prompt:** Press `Win + R`, type `cmd`, and press Enter to open the Command Prompt.

2. **Navigate to Project Directory:** Use the `cd` command to navigate to the directory containing your `main.cpp` file.

   ```sh
   cd path\to\your\project\directory
   ```

3. **Compile:** Use the `g++` command to compile the `main.cpp` file.

   ```sh
   g++ main.cpp -o trust_aware_scheduling
   ```

   This command will generate an executable file named `trust_aware_scheduling.exe`.

4. **Run:** Execute the generated executable file.

   ```sh
   ./trust_aware_scheduling.exe
   ```

   The program will run, and the output will be displayed in the Command Prompt.

## Code Customization

You can customize the simulation by changing the following variables at the top of the `main.cpp` file:

```cpp
int simulation_time = 1000;
int total_users = 10;
int total_nodes = 10;
int K = 10; // deadline = arrival time + K
```

- `simulation_time`: The duration of the simulation in time units.
- `total_users`: The total number of users in the simulation.
- `total_nodes`: The total number of Fog nodes in the simulation.
- `K`: The deadline calculation parameter (deadline = arrival time + K).

Feel free to modify these variables according to your simulation requirements.

## Note

Make sure to have the `g++` compiler installed on your Windows system. You can install it as part of the MinGW toolset, which provides a Unix-like environment on Windows.
