# CPU Scheduling Simulator

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)

A robust, command-line based simulator written in C++ for evaluating and comparing various CPU scheduling algorithms. This project provides a quantitative analysis of algorithm performance based on standard metrics like average waiting time and average turnaround time.

---
## ✨ Features

* **Analysis of 5 Core Algorithms:** Implements a variety of common scheduling algorithms to compare their performance.
* **Modular & Object-Oriented Design:** Structured with a focus on clean, maintainable, and scalable code by encapsulating data and separating concerns.
* **Dynamic Input:** Uses a custom parser to read test cases from text files, allowing for flexible and repeatable simulations.
* **Detailed Performance Metrics:** Calculates and displays key metrics for each algorithm, providing a clear basis for comparison.

---
## 🤖 Algorithms Implemented

The simulator models the following five algorithms:

1.  **First-Come, First-Served (FCFS)** - *Non-Preemptive*
2.  **Round Robin (RR)** - *Preemptive*
3.  **Shortest Job First (SJF/SPN)** - *Non-Preemptive*
4.  **Shortest Remaining Time Next (SRTN)** - *Preemptive*
5.  **Highest Response Ratio Next (HRRN)** - *Non-Preemptive*

---
## 🔧 Getting Started

### Prerequisites
To compile and run this project, you will need:
* A C++ compiler that supports C++11 or newer (e.g., **g++**)
* The **make** build automation tool

### Compilation
1.  Clone the repository to your local machine:
    ```sh
    git clone https://github.com/Suraj-kumar-pattnayak/CpuScheduling-Simulator-
    ```
2.  Navigate into the project directory:
    ```sh
    cd CPU-Scheduling-Algorithms
    ```
3.  Compile the project using the provided Makefile:
    ```sh
    make
    ```
    This will create an executable file named `scheduler` (or `scheduler.exe` on Windows).

### Execution
1.  Create an input file (e.g., `input.txt`) with your test case data.
2.  Run the simulator from your terminal, redirecting the input file to the program:

    **On Windows:**
    ```sh
    scheduler.exe < input.txt
    ```

    **On macOS/Linux:**
    ```sh
    ./scheduler < input.txt
    ```

---
## 📝 Input File Format

The program expects an input file with the following format:

* **Line 1:** A comma-separated string of algorithm IDs. For Round Robin (ID 2), specify the quantum with a hyphen.
* **Line 2:** An integer representing the total number of processes.
* **Following Lines:** Each line contains one process in the format `ProcessName,ArrivalTime,ServiceTime`.

#### Example `input.txt`:
```text
1,2-2,3,4,5
4
p1,0,7
p2,2,4
p3,4,1
p4,5,4
```

---
## 📊 Example Output
Running the simulator with the example input above will produce the following statistics:
```
FCFS
Process   | Arrival | Service | Finish | Turnaround | Waiting  |
p1        | 0       | 7       | 7      | 7          | 0        |
p2        | 2       | 4       | 11     | 9          | 5        |
p3        | 4       | 1       | 12     | 8          | 7        |
p4        | 5       | 4       | 16     | 11         | 7        |
---------------------------------------------------------------------------
Mean       |         |         |        | 8.75       | 4.75     |

RR-2
Process   | Arrival | Service | Finish | Turnaround | Waiting  |
p1        | 0       | 7       | 16     | 16         | 9        |
p2        | 2       | 4       | 9      | 7          | 3        |
p3        | 4       | 1       | 7      | 3          | 2        |
p4        | 5       | 4       | 15     | 10         | 6        |
---------------------------------------------------------------------------
Mean       |         |         |        | 9.00       | 5.00     |

SJF
Process   | Arrival | Service | Finish | Turnaround | Waiting  |
p1        | 0       | 7       | 7      | 7          | 0        |
p2        | 2       | 4       | 12     | 10         | 6        |
p3        | 4       | 1       | 8      | 4          | 3        |
p4        | 5       | 4       | 16     | 11         | 7        |
---------------------------------------------------------------------------
Mean       |         |         |        | 8.00       | 4.00     |

SRTN
Process   | Arrival | Service | Finish | Turnaround | Waiting  |
p1        | 0       | 7       | 16     | 16         | 9        |
p2        | 2       | 4       | 7      | 5          | 1        |
p3        | 4       | 1       | 5      | 1          | 0        |
p4        | 5       | 4       | 11     | 6          | 2        |
---------------------------------------------------------------------------
Mean       |         |         |        | 7.00       | 3.00     |

HRRN
Process   | Arrival | Service | Finish | Turnaround | Waiting  |
p1        | 0       | 7       | 7      | 7          | 0        |
p2        | 2       | 4       | 12     | 10         | 6        |
p3        | 4       | 1       | 8      | 4          | 3        |
p4        | 5       | 4       | 16     | 11         | 7        |
---------------------------------------------------------------------------
Mean       |         |         |        | 8.00       | 4.00     |

```

---
## 💡 Key Concepts Demonstrated

This project showcases a practical application of several key computer science concepts:

* **Data Structures:** `std::vector`, `std::queue`, `std::priority_queue`
* **Algorithm Design:** Implementation of various scheduling algorithms with different time complexities.
* **Object-Oriented Design:** Use of `structs` to **encapsulate** process state and create a modular design.
* **Build Automation:** Use of a **Makefile** for efficient project compilation.

---
## 👤 Author

**Suraj Pattanayak**
* **GitHub:** [https://github.com/Suraj-kumar-pattnayak](https://github.com/Suraj-kumar-pattnayak)
* **LinkedIn:** [https://linkedin.com/in/suraj-pattanayak](https://www.linkedin.com/in/suraj-pattanayak-447471282/)
