#include<bits/stdc++.h>
using namespace std;

// Global variables
int simulation_time = 1000;
int total_users = 10;
int total_nodes = 10;
int random_num;
int K = 10; // Maximum execution time
int busy_nodes = 0;
int task_successfully_executed = 0;
int task_failed = 0;
int total_task_generated = 0;
float failure_rate = 0.0003;
float cost = 0;
float BR = 7;
float Base = 0.3 * BR;

// Task structure
struct Task
{
    int arrival_time;
    int execution_time;
    int user;
    int deadline;
    float reliability_req;
    int start_execution;

    // Overload the < operator for sorting based on deadline
    bool operator<(const Task& other) const {
        return deadline > other.deadline;
    }
};

Task noTask = {-1, 0, 0, 0, 0}; // Default task with invalid values

// Node structure
struct Node
{
    int node_num;
    float ST = 0.5;
    bool free = true;
    Task task = noTask;
    vector<float> DT;

    Node() : DT(total_users, 0.5) {} // Initialize DT vector with default value

    // Overload the < operator for sorting
    bool operator<(const Node& other) const {
        // If nodes have the same free status, compare based on ST
        if (free == other.free) {
            // Sort free nodes by ST in ascending order
            return ST < other.ST; 
        } else {
            // Sort free nodes before non-free nodes
            return free;
        }
    }
};

// Utility function to generate tasks
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distribution1(1, 10);
uniform_int_distribution<> distribution2(0, 5);
uniform_int_distribution<> distribution3(0, 7);
uniform_int_distribution<> distribution4(0, 10);

priority_queue<Task> task_queue;
vector<Node> nodes(total_nodes);

void generate_task(int time) {
    for(int i = 0; i < total_users; i++) {
        random_num = distribution1(gen);
        if(random_num > 7) {
            total_task_generated++;
            // User i generates a task
            Task t;
            t.arrival_time = time;
            t.execution_time = distribution2(gen);
            t.user = i;
            t.deadline = t.arrival_time + K;
            t.reliability_req = (float) distribution3(gen) / 10.0;

            task_queue.push(t);
        }
    }
}

void update_ST() {
    for(auto& i : nodes) {
        float sum = 0;
        for(auto j : i.DT) {
            sum += j;
        }
        i.ST = (float) sum / total_users;
    }
}

void process_tasks(int i) {
    int finish_time;

    for(auto& j : nodes) {
        if(!j.free) {
            finish_time = j.task.start_execution + j.task.execution_time;

            // Check if halfway through execution time
            if(j.task.start_execution + (j.task.execution_time / 2) == i) {
                float random_num2 = distribution4(gen);
                float fp = 1 - exp(failure_rate * j.task.execution_time);
                fp *= 10;
                if(random_num2 < fp) {
                    j.task = noTask;
                    busy_nodes--;
                    j.free = true;
                }
                j.DT[j.task.user] = (j.DT[j.task.user] > 0) ? j.DT[j.task.user] - 0.1 : 0;
                continue;
            }

            // Check if task execution finished
            if(finish_time <= i) {
                if(finish_time > j.task.deadline) {
                    j.DT[j.task.user] = (j.DT[j.task.user] > 0) ? j.DT[j.task.user] - 0.1 : 0;
                    task_failed++;
                } else {
                    j.DT[j.task.user] = (j.DT[j.task.user] < 1) ? j.DT[j.task.user] + 0.1 : 1;
                    task_successfully_executed++;
                }
                j.task = noTask;
                busy_nodes--;
                j.free = true;
            }
        }
    }

    update_ST();
    sort(nodes.begin(), nodes.end());

    Task temp;
    vector<Task> helper;
    bool found;

    while(!task_queue.empty() && busy_nodes < total_nodes) {
        found = false;
        temp = task_queue.top();
        task_queue.pop();
        if(temp.deadline < i) {
            task_failed++;
            continue;
        }
        for(auto& node : nodes) {
            if(node.free) {
                if(node.ST >= temp.reliability_req) {
                    temp.start_execution = i;
                    node.free = false;
                    node.task = temp;
                    busy_nodes++;
                    found = true;
                    cost += Base + BR * node.ST;
                    break;
                }
            }
        }
        if(!found) {
            helper.push_back(temp);
        }
    }

    for(auto j : helper) {
        if(j.deadline > i) {
            task_queue.push(j);
        } else {
            task_failed++;
        }
    }
}

int main() {
    for(int i = 1; i <= simulation_time; i++) {
        generate_task(i);
        process_tasks(i);
    }

    int time = simulation_time + 1;
    while(!task_queue.empty() || busy_nodes > 0) {
        process_tasks(time++);
    }

    cout << "Total Task Received: " << total_task_generated << endl;
    cout << "Total Task Executed: " << task_successfully_executed << endl;
    cout << "Total Task Failed: " << task_failed << endl;
    cout << "Total Cost: " << cost << endl;

    return 0;
}
