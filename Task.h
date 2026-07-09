#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

// Difficulty affects how the "human behavior" engine schedules the task
enum class Difficulty { EASY = 1, MEDIUM = 2, HARD = 3 };

// Abstract base class -> demonstrates ABSTRACTION + shared interface
class Task {
protected:
    std::string title;
    int deadlineHour;      // 0-23, hour by which task should ideally be done
    Difficulty difficulty;
    bool isCompleted;

public:
    Task(const std::string& title, int deadlineHour, Difficulty difficulty);
    virtual ~Task() = default;

    // Pure virtual -> every derived task MUST define its own priority formula
    virtual int getPriorityScore() const = 0;

    // Pure virtual -> every derived task describes itself differently
    virtual void display() const = 0;

    virtual std::string getType() const = 0;

    // Common (non-virtual) behavior shared by all tasks -> ENCAPSULATION
    void markCompleted();
    bool getIsCompleted() const;
    std::string getTitle() const;
    int getDeadlineHour() const;
    Difficulty getDifficulty() const;

    // Used for saving/loading task data to a file
    virtual std::string serialize() const;
};

#endif
