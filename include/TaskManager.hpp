#pragma once

#include <string>
#include <vector>

struct Task {
    std::string title;
    std::string dueDate;
    bool completed{false};
};

/**
 * Lightweight manager for study tasks that persists a simple pipe-delimited file.
 */
class TaskManager {
public:
    explicit TaskManager(std::string storagePath);

    bool loadFromDisk();
    bool saveToDisk() const;

    void addTask(const std::string& title, const std::string& dueDate);
    bool markTaskComplete(std::size_t index);

    const std::vector<Task>& getTasks() const { return tasks_; }

private:
    static Task parseLine(const std::string& line);
    static std::string serialize(const Task& task);

    std::string storagePath_;
    std::vector<Task> tasks_;
};
