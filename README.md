<div align="center">

# 🧠 Smart Task Scheduler

### A C++ task scheduler that turns priorities and deadlines into an actual queue.

</div>

## 💡 What It Is

A console-based C++17 project built around a simple idea: not every task should have the same priority. Different task types use their own scoring rules, while the scheduler handles them through one common `Task` interface.

## 🛠️ Tech Stack

- **C++17**
- STL `vector` + algorithms
- File streams for persistence
- OOP: abstraction, inheritance, polymorphism, encapsulation

## ⚙️ How It Works

```text
Create Task
    ↓
Task-specific Priority Score
    ↓
Scheduler sorts highest → lowest
    ↓
Complete / Remove
    ↓
Save to tasks.txt
```

`UrgentTask` uses urgency, deadline, and difficulty, while `PersonalTask` also considers a preferred time of day.

## 🚀 Run Locally

Compile with any C++17 compiler:

```bash
g++ -std=c++17 -Wall -Wextra -o scheduler main.cpp Task.cpp UrgentTask.cpp PersonalTask.cpp Scheduler.cpp
./scheduler
```

On Windows, run `scheduler.exe`.

## ✨ What I Learned / Challenges

The main challenge was making polymorphism useful in a real workflow instead of just demonstrating inheritance — each task type genuinely controls its own scheduling behavior.
