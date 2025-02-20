
# SHERLOCK ADVENTURE GAME: A STUDY IN PINK
This project implements the core game logic for a 2D grid-based game in C++.  It's currently focused on the backend, with character interactions, movement, and game mechanics as the main features.For further details regarding this project, please refer to the "DETAILED PROJECT DESCRIPTION" document.




### 1. INTRODUCTION
The SHERLOCK ADVENTURE GAME: A STUDY IN PINK project is a highly complex game logic system developed using OOP combined with dynamic memory management. This project simulates the pursuit of a criminal through a maze, featuring the main characters Sherlock, Watson, and the criminal, along with supporting entities such as robots and interactive items. The aim of this project is to demonstrate the integration of multiple complex modules—from map construction and positioning to movement handling and inventory management—highlighting advanced programming techniques.  
## 2. Key Features

### Map & Position
- Constructs a two-dimensional map composed of different elements: **Path** (traversable routes), **Wall** (solid barriers), and **FakeWall** (deceptive walls).  
- The `Position` class manages grid coordinates (row and column) with functions for string formatting, validation, and comparison.

### Moving Entities
- Implements an abstract class `MovingObject` and its concrete subclasses such as `Sherlock`, `Watson`, and `Criminal`.  
- Each entity moves according to its unique rule (defined by a `moving_rule` string) and must adhere to specific conditions based on HP, EXP, and Manhattan distance calculations.

### Array of Moving Entities
- Manages a collection of moving objects, providing functionalities to add new objects, check capacity, and display current status.

### System Configuration
- Reads a configuration file that specifies parameters like map dimensions, object positions, maximum number of moving entities, and initial settings for Sherlock, Watson, and the Criminal.

### Robots and Items
- Implements various types of robots (**RobotC**, **RobotS**, **RobotW**, **RobotSW**) with specialized movement rules and distance calculations.  
- Integrates an item system with objects such as **MagicBook**, **EnergyDrink**, **FirstAid**, **ExcemptionCard**, and **PassingCard** that affect character attributes when used.

### Inventory and Item Exchange
- Each character is equipped with their own inventory (**SherlockBag** for Sherlock, **WatsonBag** for Watson) which stores, retrieves, and exchanges items when encounters occur.

### Game Process – StudyInPinkProgram
- Orchestrates the entire movement process, collision handling, and the creation of robots (after every three valid moves by the Criminal).  
- Continuously updates the game state until a termination condition is met (e.g., HP reaches 0 or the criminal is captured).

### Testing
- Includes a `TestStudyInPink` class designed to comprehensively test all modules and ensure the overall system functions correctly.

---

## 3. System Requirements & Development Environment

### System Requirements
- The software must compile and run on a Unix platform.  
- Use `g++` with the `-std=c++11` flag for compilation.  
- Only two files are permitted for modification:
  - `study_in_pink2.h`
  - `study_in_pink2.cpp`

### Include Directive Guidelines
- In `study_in_pink2.h`, there must be exactly one `#include "main.h"`.  
- In `study_in_pink2.cpp`, there must be exactly one `#include "study_in_pink2.h"`.

---

## 4. Installation and Running Instructions

### Compiling the Program
Open a terminal and run:
```bash
g++ -o main main.cpp study_in_pink2.cpp -I . -std=c++11
```
Once compiled successfully, execute the program with:
```bash
./main
```
### 5. PROJECT STRUCTURE
- main.cpp:
  The entry point of the program.

- study_in_pink2.h /      study_in_pink2.cpp:
  Files where the core logic of the project must be implemented according to the specifications.

- Configuration File:
  Contains initialization parameters for the map and moving objects.

- Additional Files (if any):
  Other source files, sample data files, or documentation that support the project.


### 6. Testing Instructions
- TestStudyInPink:

  - This class is used to ensure that all modules work correctly.
  - It covers scenarios such as movement of Sherlock, Watson, and Criminal, robot encounters, and item usage through the inventory system.
Debugging and Output:

- Utilize the functions `printStep` and `printResult` to monitor the state of the system at each step for debugging and verification purposes.


### 7. Contact & Contribution
- **Contact Information**:

For any questions or support, please contact duongtranminh253@gmail.com.

- **Contributions**:

If this project is released as open source, provide guidelines for contributions including the pull request process and coding standards.
