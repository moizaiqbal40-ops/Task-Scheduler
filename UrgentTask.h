#ifndef URGENT_TASK_H
#define URGENT_TASK_H

#include "Task.h"

// INHERITANCE: UrgentTask "is-a" Task
// Urgent tasks care mostly about how close the deadline is.
class UrgentTask : public Task {
private:
    int urgencyLevel; // 1-10, how critical the task is regardless of deadline

public:
    UrgentTask(const std::string& title, int deadlineHour, Difficulty difficulty, int urgencyLevel);

    // POLYMORPHISM: overrides base formula with its own priority logic
    int getPriorityScore() const override;
    void display() const override;
    std::string getType() const override;
    std::string serialize() const override;
};

#endif
