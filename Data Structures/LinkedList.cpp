//
// Created by VEDANT KASHYAP on 12/31/2017.
//

#include <iostream>
#include "lib/LinkedList.h"

using namespace std;

void printList(struct LL_node *LL) {
    while (LL != NULL) {
        cout << LL->data << " ";
        LL = LL->next;
    }
    cout << endl;
}

void Delete(struct LL_node **LL, int val) {
    struct LL_node *temp = *LL;
    struct LL_node *prev = NULL;

    if (temp != NULL && temp->data == val) {    // Check if we have to remove the head node itself
        *LL = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != val) { // Find the node with data = val
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;                   // If you don't find the node then return;

    prev->next = temp->next;                      // Previous's next node will be the current's next basically skipping a node

    free(temp);
}

void Insert(struct LL_node **LL, int index, int val) {
    struct LL_node *newNode = (struct LL_node *) malloc(sizeof(struct LL_node));
    struct LL_node *last = *LL;
    newNode->data = val;

    for (int i = 0; i < index - 1; ++i)
        last = last->next;

    newNode->next = last->next;
    last->next = newNode;

    return;
}

void Append(struct LL_node **LL, int val) {
    struct LL_node *newNode = (struct LL_node *) malloc(sizeof(struct LL_node));
    struct LL_node *last = *LL;
    newNode->data = val;
    newNode->next = NULL;

    if (*LL == NULL) {
        *LL = newNode;
        return;
    }
    while (last->next != NULL)
        last = last->next;

    last->next = newNode;
    return;
}

void Swap(struct LL_node **LL, int val1, int val2) {
    if (val1 == val2) return;

    struct LL_node *prev1 = NULL, *curr1 = *LL;     // Keeping a track of current and previous values for val1
    while (curr1 && curr1->data != val1) {          // Searching for val1
        prev1 = curr1;
        curr1 = curr1->next;
    }

    struct LL_node *prev2 = NULL, *curr2 = *LL;     // Keeping a track of current and previous values for val1
    while (curr2 && curr2->data != val2) {          // Searching for val2
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (curr1 == NULL && curr2 == NULL) return;     // If either of val1 or val2 not found

    if (prev1 != NULL)                              // Check if val1 is present in the head node
        prev1->next = curr2;
    else
        *LL = curr2;                                // Make val2 the new head node

    if (prev2 != NULL)                              // Check if val2 is present in the head node
        prev2->next = curr1;
    else
        *LL = curr1;                                // Make val2 the new head node

    struct LL_node *temp = curr1->next;             // Swapping next for val1 and val2 nodes
    curr1->next = curr2->next;
    curr2->next = temp;

    return;;
}

void RotateBW(struct LL_node **LL, int k) {
    if (k == 0) return;

    struct LL_node *temp = *LL;
    int count = 1;
    while (count < k && temp != NULL) {
        temp = temp->next;
        count++;
    }
    if (temp == NULL) return;

    struct LL_node *kNode = temp;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = *LL;
    *LL = kNode->next;
    kNode->next = NULL;
}

void RotateFW(struct LL_node **LL, int k) {
    if (k == 0) return;

    struct LL_node *temp = *LL;
    int count = 1, n = 0;
    while (temp->next != NULL) {
        n++;
        temp = temp->next;
    }
    n++;
    temp = *LL;
    while (count < n - k && temp != NULL) {
        temp = temp->next;
        count++;
    }
    if (temp == NULL) return;

    struct LL_node *kNode = temp;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = *LL;
    *LL = kNode->next;
    kNode->next = NULL;
}

bool Search(struct LL_node **LL, int val) {
    struct LL_node *temp = *LL;
    while (temp->next != NULL) {
        if (temp->data == val) return true;
        temp = temp->next;
    }
    return temp->data == val;
}

void Single_LinkedList() {
    struct LL_node *LL = NULL; // Linked List
    int n;              // Size of the Linked List
    int data;           // Data to be put in the nodes of the Linked List
    int choice;         // To determine which  function to execute
    int index;          // Position to insert data
    int x, y;            // Swapping data inputs

    cout << "Enter the size of the linked list: ";
    cin >> n;

    cout << "Enter the values in the linked list: ";
    for (int i = 0; i < n; ++i) {
        cin >> data;
        Append(&LL, data);
    }

    while (1) {
        cout
                << "\n0 - QUIT\n1 - Print List\n2 - Append Node\n3 - Insert Node at an index\n4 - Delete Node\n5 - Swap Node\n6 - Search for a Node\n7 - Shift Forward\n8 - Shift Backward\n"
                << endl;
        cin >> choice;

        if (choice == 0) break;
        else if (choice == 1) printList(LL);
        else if (choice == 2) {
            cout << "Input data to be appended: ";
            cin >> data;
            Append(&LL, data);
            printList(LL);
        } else if (choice == 3) {
            cout << "Input the data to be appended: ";
            cin >> data;
            cout << "Input the index to append it into: ";
            cin >> index;
            Insert(&LL, index, data);
            printList(LL);
        } else if (choice == 4) {
            cout << "Input the data to be deleted: ";
            cin >> data;
            Delete(&LL, data);
            printList(LL);
        } else if (choice == 5) {
            cout << "Input the 2 nodes to be swapped: ";
            cin >> x >> y;
            Swap(&LL, x, y);
            printList(LL);
        } else if (choice == 6) {
            cout << "Input the node to search: ";
            cin >> data;
            if (Search(&LL, data)) cout << data << " was found in the linked list!";
            else cout << data << " not found in the linked list";
        } else if (choice == 7) {
            cout << "Input the number of times to shift forward: ";
            cin >> data;
            RotateFW(&LL, data);
            printList(LL);
        } else if (choice == 8) {
            cout << "Input the number of times to shift backward: ";
            cin >> data;
            RotateBW(&LL, data);
            printList(LL);
        } else cout << "Not a valid option! Pick a number from 1-8 only!" << endl;
    }
}