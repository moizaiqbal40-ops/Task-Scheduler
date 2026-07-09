#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Task.h"
#include <vector>
#include <string>

// ENCAPSULATION: the internal storage (vector acting as our priority structure)
// is private. Outside code can only interact through public methods below.
class Scheduler {
private:
    std::vector<Task*> tasks;

    // Keeps the vector sorted so tasks[0] is always the highest priority task.
    void resortByPriority();

public:
    Scheduler() = default;
    ~Scheduler(); // frees all heap-allocated tasks

    void addTask(Task* task);
    void displayQueue() const;
    bool completeTopTask();          // marks the highest priority task as done
    void removeCompletedTasks();

    int pendingCount() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif
