#ifndef PERSONAL_TASK_H
#define PERSONAL_TASK_H

#include "Task.h"

enum class TimePreference { MORNING = 0, AFTERNOON = 1, EVENING = 2 };

// INHERITANCE: PersonalTask "is-a" Task
// Personal tasks care about WHEN the user is naturally good at that kind of work
// (research shows most people handle hard tasks better in the morning).
class PersonalTask : public Task {
private:
    TimePreference preference;

public:
    PersonalTask(const std::string& title, int deadlineHour, Difficulty difficulty, TimePreference preference);

    // POLYMORPHISM: a completely different scoring formula than UrgentTask
    int getPriorityScore() const override;
    void display() const override;
    std::string getType() const override;
    std::string serialize() const override;

    TimePreference getPreference() const;
    static std::string preferenceToString(TimePreference p);
};

#endif
