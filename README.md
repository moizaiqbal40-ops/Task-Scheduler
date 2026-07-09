# Smart "Humanized" Task Scheduler (C++ | OOP)

A console-based task scheduler that doesn't just sort tasks by deadline — it scores them
using logic inspired by human productivity patterns. Hard tasks matched to your best-focus
time of day score higher than the same task at the wrong time.

## Why this project is different
Most to-do list projects just sort by date. This one models **two different kinds of
priority reasoning** through polymorphism:
- Urgent tasks care about deadline + urgency
- Personal tasks care about matching task difficulty to the right time of day

## OOP Concepts Demonstrated

| Concept | Where |
|---|---|
| Abstraction | `Task` is an abstract class with pure virtual functions |
| Inheritance | `UrgentTask` and `PersonalTask` both extend `Task` |
| Polymorphism | `getPriorityScore()` and `display()` behave differently per subclass, called through a base `Task*` pointer |
| Encapsulation | `Scheduler` hides its internal task storage behind public methods only |
| File Handling | Tasks persist to `tasks.txt` between runs |

## Project Structure
```
task-scheduler/
├── Task.h / Task.cpp              # Abstract base class
├── UrgentTask.h / UrgentTask.cpp  # Derived class #1
├── PersonalTask.h / PersonalTask.cpp # Derived class #2
├── Scheduler.h / Scheduler.cpp    # Manages the task queue
├── main.cpp                       # Console menu / entry point
└── tasks.txt                      # Auto-created save file
```

## How to Build & Run
```bash
g++ -std=c++17 -Wall -o scheduler main.cpp Task.cpp UrgentTask.cpp PersonalTask.cpp Scheduler.cpp
./scheduler
```

## Sample Menu
```
1. Add Urgent Task
2. Add Personal Task
3. View Scheduled Queue
4. Complete Top Priority Task
5. Remove Completed Tasks
6. Save & Exit
```

## Possible Extensions (good talking points in an interview)
- Track real completion timestamps and *learn* the user's actual best hours instead of a fixed rule
- Add a `RecurringTask` subclass to show off further polymorphism
- Swap the file storage for SQLite
- Wrap the same `Scheduler` class in a simple GUI (Qt) or web API (Crow/Drogon)

## License
MIT
