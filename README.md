

# Design Dexterity Challenge - AeroHack Rubik's Cube Solver

A C++ implementation of an algorithm to solve a 3x3 Rubik's Cube, developed for the **AeroHack '25** challenge.

-----

## ✨ Features

  * **Cube State Modeling:** Represents the cube's state and transitions internally using efficient data structures.
  * **Move Engine:** Implements a move engine to simulate all 18 face rotations (U, U', D, D', etc.) and track permutations accurately.
  * **Efficient Solving Algorithm:** Utilizes a highly efficient, two-phase algorithm to find optimal solutions from any scrambled state.
  * **State Prediction:** Capable of tracking and predicting the cube's state after each move is applied.
  * **(Bonus) Visual UI:** Includes a creative visual simulation of the cube for a better user experience.
  * **(Bonus) Scalability:** Designed with optional scalability for different cube sizes in mind.

-----

## 🧠 Algorithm: Two-Phase Kociemba

This solver implements **Herbert Kociemba's two-phase algorithm**, a powerful method that finds near-optimal solutions to the Rubik's Cube. The algorithm dramatically reduces the complex problem into two more manageable steps, or phases.

> **Why a Two-Phase Algorithm?**
> A direct approach to solving the cube requires searching through a massive number of states (\~$4.3 \\times 10^{19}$). The two-phase algorithm breaks this down by first reaching an intermediate state before proceeding to the final solved state.

#### **Phase 1: Reach the G1 Subgroup**

The goal of this phase is to get the cube into a specific subgroup of states (`G1`) where the search for a final solution is much simpler.

  * **Goal:**
      * All edge pieces are correctly oriented.
      * All corner pieces are correctly oriented.
      * The four edge pieces belonging to the middle slice are placed in that slice.
  * **Method:** An **Iterative Deepening A\* (IDA\*)** search is used to find the shortest sequence of moves to reach this state.

#### **Phase 2: Solve Within the G1 Subgroup**

Once the cube is in the `G1` state, the final solution is found using a restricted set of moves that keep the cube within this subgroup.

  * **Goal:** Solve the cube completely by only arranging the permutations of the corners and edges.
  * **Allowed Moves:** `U, U', D, D', R2, L2, F2, B2`
  * **Method:** A second **IDA\*** search is performed using only these moves to find the final solution.

-----

## 📂 Project Structure

  * **`📁 src/`**: Contains all C++ source code (`.h` and `.cpp` files), including the cube's implementation, the IDA\* solver, and the pattern databases for the two-phase algorithm.
  * **`📁 examples/`**: Holds generated output examples, including solution walkthroughs for various scrambles and performance analysis.
  * **`main.cpp`**: The main entry point to run the solver and generate examples.
  * **`IDASolver.cpp`**: The core engine implementing the IDA\* search algorithm.
  * **`PatternDatabase.cpp`**: Manages the heuristic lookup tables which store pre-calculated costs to speed up the search.
  * **`.gitignore`**: Configured to exclude compiled executables and build directories.

-----

## 🛠️ Tech Stack

  * **Language:** C++

-----

## 🚀 Getting Started

### Prerequisites

  * A C++ compiler (e.g., G++, Clang)
  * Make (optional, for automating compilation)

### Installation & Compilation

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/RitamPal26/Aerohack_rubick_cube.git
    ```
2.  **Navigate to the project directory:**
    ```bash
    cd Aerohack_rubick_cube
    ```
3.  **Compile the source code:**
    ```bash
    g++ -o solver src/*.cpp
    ```
4.  **Run the solver:**
    ```bash
    ./solver
    ```

-----

## 🧑‍💻 Author

  * **Ritam Pal**
      * **GitHub:** [@RitamPal26](https://github.com/RitamPal26)
      * **LinkedIn:** [Ritam Pal](https://www.linkedin.com/in/ritam-pal-124175244/)
      * **Portfolio:** [Portfolio Website](https://new-portfolio-lovat-one.vercel.app/)
