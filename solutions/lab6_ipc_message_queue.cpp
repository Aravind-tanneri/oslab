#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

// Structure for message buffer
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    // Create a message queue using IPC_PRIVATE
    int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msgid < 0) {
        cerr << "Failed to create message queue.\n";
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed.\n";
        return 1;
    } 
    else if (pid == 0) {
        // Child Process: Receiver
        msg_buffer message;
        // Wait and receive message of type 1
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        cout << "[Receiver/Child] Received Message: \"" << message.msg_text << "\"\n" << flush;
        exit(0);
    } 
    else {
        // Parent Process: Sender
        msg_buffer message;
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from Sender via Message Queue!");

        cout << "[Sender/Parent] Sending Message: \"" << message.msg_text << "\"\n";
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);

        // Wait for receiver child to finish reading
        wait(NULL);

        // Destroy the message queue from system memory
        msgctl(msgid, IPC_RMID, NULL);
        cout << "[Sender/Parent] Message queue destroyed successfully.\n";
    }

    return 0;
}
