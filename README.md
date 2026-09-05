<h1 align="center">🧠 Smart Task Scheduler</h1>

<p align="center">
  <strong>A C++17 task scheduling system that combines priority scoring with OOP polymorphism and human-centered scheduling rules.</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue?style=flat-square" alt="C++17">
  <img src="https://img.shields.io/badge/OOP-Polymorphism-purple?style=flat-square" alt="Object Oriented Programming">
  <img src="https://img.shields.io/badge/Storage-File%20Persistence-orange?style=flat-square" alt="File Persistence">
  <img src="https://img.shields.io/badge/License-MIT-green?style=flat-square" alt="MIT License">
</p>

## 📌 Overview

Smart Task Scheduler is a **console-based C++17 application** that goes beyond a basic to-do list. Instead of sorting every task only by its deadline, the scheduler calculates a priority score based on the task type and its attributes.

The project is primarily an **object-oriented programming and problem-solving project**. It uses an abstract `Task` interface with specialized `UrgentTask` and `PersonalTask` implementations, allowing different priority strategies to work through the same scheduler.

For personal tasks, the scoring logic also considers a simple human-productivity rule: difficult work receives a higher score when it matches a preferred time of day.

## 🎯 Problem → Solution

**Problem:** A conventional task list may treat every task the same and sort only by date or deadline.

**Solution:** Each task type owns its own priority formula. The scheduler stores tasks through the common `Task` interface, calculates their scores polymorphically, and keeps the highest-priority task at the front of the queue.

## ✨ Key Features

- **Two task types:** Urgent and Personal
- **Dynamic priority scoring:** Different task types use different scoring strategies
- **Deadline awareness:** Earlier deadlines increase priority
- **Urgency scoring:** Urgent tasks include a configurable urgency level from 1–10
- **Humanized scheduling rule:** Personal tasks receive bonuses when difficulty matches a preferred time of day
- **Polymorphic task handling:** The scheduler works with `Task*` without knowing the concrete subtype
- **Automatic priority ordering:** Tasks are re-sorted after insertion
- **Task completion workflow:** Complete the current top-priority task and remove completed tasks
- **Persistent storage:** Tasks are serialized to `tasks.txt` and restored on the next run
- **Input validation:** Menu values, deadlines, difficulty, urgency, and time preferences are range-checked
- **Memory cleanup:** `Scheduler` owns and releases its dynamically allocated task objects

## 🧩 OOP Concepts Demonstrated

| Concept | Implementation |
|---|---|
| **Abstraction** | `Task` is an abstract base class with pure virtual methods. |
| **Inheritance** | `UrgentTask` and `PersonalTask` derive from `Task`. |
| **Polymorphism** | `getPriorityScore()`, `display()`, `getType()`, and `serialize()` are overridden by derived classes and called through `Task*`. |
| **Encapsulation** | `Scheduler` keeps its task collection private and exposes controlled public operations. |
| **Virtual Destructor** | `Task` provides a virtual destructor for safe polymorphic cleanup. |
| **Composition / Ownership** | `Scheduler` manages the lifetime of the task objects it stores. |

The base class deliberately requires each subtype to provide its own priority formula, making polymorphism central to the scheduling behavior rather than merely decorative. fileciteturn36file0

## ⚙️ Priority Engine

### Urgent tasks

The urgent-task score combines three factors:

```text
Score = (Urgency × 10) + (Deadline Factor × 3) + (Difficulty × 2)
Deadline Factor = 24 − Deadline Hour
```

This makes higher urgency, greater difficulty, and earlier deadlines contribute to the final score. fileciteturn37file0

### Personal tasks

Personal tasks use difficulty, deadline, and a preferred time-of-day bonus:

- Hard + Morning → higher productivity bonus
- Medium + Afternoon → moderate bonus
- Easy + Evening → moderate bonus
- Other combinations → default bonus

This is intentionally a **rule-based heuristic**, not machine learning. The goal is to demonstrate how domain rules can be encoded into an extensible OOP design. fileciteturn38file0

## 🔄 Scheduling Flow

```text
User Input
    ↓
Create Task Subclass
    ↓
Scheduler::addTask()
    ↓
Calculate Polymorphic Priority Score
    ↓
Sort Highest → Lowest Priority
    ↓
Display / Complete / Remove
    ↓
Serialize to tasks.txt
    ↓
Restore on next launch
```

The scheduler sorts its `Task*` collection using the virtual `getPriorityScore()` method, so the ordering logic automatically works across task subtypes. fileciteturn39file0

## 🏗️ Architecture

```text
                    ┌─────────────────┐
                    │      Task       │
                    │  Abstract Base  │
                    └────────┬────────┘
                             │
                ┌────────────┴────────────┐
                ↓                         ↓
       ┌────────────────┐        ┌─────────────────┐
       │  UrgentTask    │        │  PersonalTask   │
       │ urgency-based  │        │ time-aware rule │
       │ priority score │        │ priority score  │
       └───────┬────────┘        └────────┬────────┘
               └────────────┬────────────┘
                            ↓
                    ┌───────────────┐
                    │   Scheduler   │
                    │ priority queue│
                    └───────┬───────┘
                            ↓
                       tasks.txt
```

## 📁 Project Structure

```text
Task-Scheduler/
├── Task.h / Task.cpp                  # Abstract task interface + shared behavior
├── UrgentTask.h / UrgentTask.cpp      # Urgency-based task subtype
├── PersonalTask.h / PersonalTask.cpp  # Time-preference task subtype
├── Scheduler.h / Scheduler.cpp        # Task storage, ordering, completion, persistence
├── main.cpp                           # Console UI and input validation
└── tasks.txt                          # Runtime save file
```

## 🛠️ Tech Stack

| Technology | Purpose |
|---|---|
| **C++17** | Core application language |
| **STL `vector`** | Internal task collection |
| **STL algorithms** | Priority sorting and completed-task removal |
| **File streams** | Save/load persistent task data |
| **OOP** | Abstraction, inheritance, polymorphism, encapsulation |

## 🚀 Build & Run

### Requirements

- A C++ compiler with C++17 support
- `g++` / MinGW, GCC, or another C++17-compatible compiler

### Compile

```bash
g++ -std=c++17 -Wall -Wextra -o scheduler main.cpp Task.cpp UrgentTask.cpp PersonalTask.cpp Scheduler.cpp
```

### Run

```bash
./scheduler
```

On Windows with MinGW, run:

```bash
scheduler.exe
```

## 🖥️ Console Workflow

```text
========== SMART TASK SCHEDULER ==========
1. Add Urgent Task
2. Add Personal Task
3. View Scheduled Queue
4. Complete Top Priority Task
5. Remove Completed Tasks
6. Save & Exit
===========================================
```

The application validates numeric input before accepting deadlines, difficulty levels, urgency, and time preferences. fileciteturn40file0

## 💾 Persistence

Tasks are saved in a simple pipe-delimited text format. On startup, the scheduler reads the saved records, reconstructs the correct derived class, restores completion state, and recalculates the priority ordering.

This gives the console application persistence across separate executions without requiring an external database. fileciteturn39file0

## 🧠 Engineering Notes

- The scheduler keeps its internal `vector<Task*>` private and exposes operations through `Scheduler` methods.
- `std::sort` maintains highest-priority-first ordering after tasks are added or loaded.
- Completed tasks can be marked first and physically removed later.
- The virtual destructor in `Task` supports safe deletion through a base-class pointer.
- Task serialization is polymorphic, allowing each subtype to persist its additional data.
- Input validation prevents invalid values for bounded numeric fields.

## ⚠️ Current Limitations

- Console-only interface
- Persistence uses a text file rather than a database
- Priority formulas are fixed heuristics rather than learned from user behavior
- Deadline is represented as an hour of day (`0–23`), not a full calendar date/time
- Raw pointers are used for task ownership; modern C++ smart pointers would be a natural improvement
- No automated unit-test suite is currently included

## 🔮 Future Improvements

- Replace raw pointers with `std::unique_ptr<Task>` for clearer ownership and safer memory management
- Add full date/time deadlines using `std::chrono`
- Add a `RecurringTask` subtype to extend the polymorphic design
- Track completion history and use it to estimate productive time windows
- Replace text persistence with SQLite
- Add automated unit tests for scoring and scheduling behavior
- Add a GUI with Qt or expose the scheduler through a C++ web API
- Add configurable scoring weights instead of hard-coded formulas

## 💼 What This Project Demonstrates

This project is especially useful as a **C++ / OOP portfolio project** because the technical story is clear:

- Designing an abstract interface
- Extending behavior through inheritance
- Using runtime polymorphism in a real scheduling workflow
- Translating business/productivity rules into deterministic algorithms
- Managing dynamic object lifetime
- Sorting and filtering collections with the STL
- Persisting structured application state
- Building a complete command-line application rather than isolated class examples

## 📸 Screenshots / Demo

<!-- Add console screenshots or a short terminal GIF here when available. -->

## 📄 License

MIT License.

## 👩‍💻 Author

**Moeeza Iqbal**  
Computer Science Student | Software Engineering Portfolio
