# Q-Learning 2D Game

This project implements a simple 2D grid-based game using **Q-Learning** in C++. The objective is to guide a player from the starting point to the goal while avoiding monsters on the grid. The agent learns the optimal path through training iterations.

## 📌 Features
- 4x4 grid environment
- Player starts at position (0,0)
- Goal position and monster positions are predefined
- Q-learning with configurable parameters
- Optional sliding effect to simulate movement uncertainty
- Console visualization of the environment

## 🎮 How to Play
After training, the agent automatically plays:
- The agent moves according to the learned Q-values.
- If the player reaches the goal: `The Person Won :)`
- If the player hits a monster: `Game Over !`

## ⚙️ Environment
The grid values:
- `1` → Player
- `0` → Empty cell
- `2` → Monster (hazard)
- `3` → Goal

## 🧠 Q-Learning Parameters
- Learning rate (`y`): `0.6`
- Sliding (random unintended movement): Enabled by default
- Number of training iterations: `50,000`

## 🚀 How to Build & Run
1️⃣ **Requirements**
- C++ compiler (e.g., g++)
- Windows (uses `windows.h` for `Sleep` and `system("cls")`)

