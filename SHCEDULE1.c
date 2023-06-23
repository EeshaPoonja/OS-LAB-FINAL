#include <stdio.h>

struct Process {
    int process_id;
    int burst_time;
    int priority;
    int arr;
};

void fcfs(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;

    waiting_time[0] = 0;
  for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arr > processes[j].arr) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        waiting_time[i] = processes[i - 1].burst_time + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
    }

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("First-Come, First-Served (FCFS) Scheduling Algorithm\n");
    printf("--------------------------------------------------\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("\n");
}

void sjf(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        waiting_time[i] = processes[i - 1].burst_time + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
    }

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Shortest Job First (SJF) Scheduling Algorithm\n");
    printf("----------------------------------------------\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("\n");
}

void roundRobin(struct Process processes[], int n, int quantum) {
    int remaining_time[n], waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
    for (int i = 0; i < n; i++) {
        if (remaining_time[i] > 0) {
            if (remaining_time[i] > quantum) {
                time += quantum;
                remaining_time[i] -= quantum;
            } else {
                time += remaining_time[i];
                waiting_time[i] = time - processes[i].burst_time;  // Update waiting time correctly
                remaining_time[i] = 0;
                completed_processes++;
            }
        }
    }
}


    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Round Robin Scheduling Algorithm\n");
    printf("--------------------------------\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("\n");
}

void priority(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        waiting_time[i] = processes[i - 1].burst_time + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
    }

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Priority Scheduling Algorithm\n");
    printf("----------------------------------------------\n");
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].priority, waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter the burst time, arrival time and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d Burst Time: ", i+1);
        scanf("%d", &processes[i].burst_time);
        printf("Process %d Arrival Time: ", i+1);
        scanf("%d", &processes[i].arr);
        printf("Process %d Priority: ", i+1);
        scanf("%d", &processes[i].priority);
        processes[i].process_id = i + 1;
    }
    sjf(processes, n);
    fcfs(processes, n);
    int quantum;
    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);
    roundRobin(processes, n, quantum);
    priority(processes, n);

    return 0;
}
