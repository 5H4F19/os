
#include <stdio.h>

// Structure to represent a process
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

// Function to calculate the completion time, waiting time, and turnaround time of each process
void calculateTimes(Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int shortest_job = -1;
        int shortest_burst_time = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
                if (processes[i].burst_time < shortest_burst_time) {
                    shortest_burst_time = processes[i].burst_time;
                    shortest_job = i;
                }
            }
        }

        if (shortest_job == -1) {
            current_time++;
            continue;
        }

        // Update the completion time of the current process
        processes[shortest_job].completion_time = current_time + processes[shortest_job].burst_time;

        // Calculate waiting time and turnaround time
        processes[shortest_job].waiting_time = current_time - processes[shortest_job].arrival_time;
        processes[shortest_job].turnaround_time = processes[shortest_job].waiting_time + processes[shortest_job].burst_time;

        // Update the current time
        current_time = processes[shortest_job].completion_time;

        // Update the total waiting time and total turnaround time
        total_waiting_time += processes[shortest_job].waiting_time;
        total_turnaround_time += processes[shortest_job].turnaround_time;

        // Mark the process as completed
        processes[shortest_job].is_completed = 1;
        completed_processes++;
    }

    // Print the process details
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Print the average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}


int main() {
    int n;  // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].is_completed = 0;
    }

    // Calculate times using the SJF algorithm
    calculateTimes(processes, n);

    return 0;
}

