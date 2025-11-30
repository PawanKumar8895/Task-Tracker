#include "TaskManager.hpp"

#include <fstream>
#include <sstream>

TaskManager::TaskManager(std::string storagePath)
    : storagePath_(std::move(storagePath)) {}

bool TaskManager::loadFromDisk() {
    tasks_.clear();
    std::ifstream in(storagePath_);
    if (!in.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            tasks_.emplace_back(parseLine(line));
        }
    }
    return true;
}

bool TaskManager::saveToDisk() const {
    std::ofstream out(storagePath_);
    if (!out.is_open()) {
        return false;
    }
    for (const auto& task : tasks_) {
        out << serialize(task) << '\n';
    }
    return true;
}

void TaskManager::addTask(const std::string& title, const std::string& dueDate) {
    tasks_.push_back(Task{title, dueDate, false});
}

bool TaskManager::markTaskComplete(std::size_t index) {
    if (index >= tasks_.size()) {
        return false;
    }
    tasks_[index].completed = true;
    return true;
}

Task TaskManager::parseLine(const std::string& line) {
    std::stringstream ss(line);
    std::string segment;
    Task task;
    std::getline(ss, task.title, '|');
    std::getline(ss, task.dueDate, '|');
    std::getline(ss, segment, '|');
    task.completed = (segment == "1");
    return task;
}

std::string TaskManager::serialize(const Task& task) {
    std::ostringstream oss;
    oss << task.title << '|' << task.dueDate << '|' << (task.completed ? "1" : "0");
    return oss.str();
}
