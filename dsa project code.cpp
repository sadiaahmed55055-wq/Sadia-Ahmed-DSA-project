#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
struct Order {
    int id;
    string customerName;
    string item;
    double price;
    int priority;

    Order* next;
    Order* prev;

    Order(int i, string n, string it, double p, int pr) {
        id = i;
        customerName = n;
        item = it;
        price = p;
        priority = pr;
        next = prev = NULL; 
    }
};

class RestaurantManagementSystem {
private:
    Order* head;
    Order* tail;
    vector<Order*> orderQueue;
    vector<Order*> undoStack;

public:
    RestaurantManagementSystem() : head(NULL), tail(NULL) {}

    void addOrder(int id, string name, string item, double price, int priority) {
        Order* newOrder = new Order(id, name, item, price, priority);
        if (!head) {
            head = tail = newOrder;
        } else {
            tail->next = newOrder;
            newOrder->prev = tail;
            tail = newOrder;
        }
        orderQueue.push_back(newOrder);
        cout << "\n[Success] Order #" << id << " added." << endl;
    }

    void displayOrders() {
        if (!head) {
            cout << "\n[Empty] No orders." << endl;
            return;
        }
        Order* temp = head;
        cout << "\n--- All Orders ---" << endl;
        while (temp) {
            cout << "ID: " << temp->id << " | Name: " << temp->customerName 
                 << " | Price: " << temp->price << endl;
            temp = temp->next;
        }
    }

    void searchOrder(int id) {
        Order* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "\n[Found] Customer: " << temp->customerName << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\n[Error] ID " << id << " not found." << endl;
    }

    void sortByPrice() {
        if (!head || !head->next) return;
        bool swapped;
        Order* ptr1;
        Order* lptr = NULL;
        do {
            swapped = false;
            ptr1 = head;
            while (ptr1->next != lptr) {
                if (ptr1->price > ptr1->next->price) {
                    swap(ptr1->id, ptr1->next->id);
                    swap(ptr1->customerName, ptr1->next->customerName);
                    swap(ptr1->item, ptr1->next->item);
                    swap(ptr1->price, ptr1->next->price);
                    swap(ptr1->priority, ptr1->next->priority);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
        cout << "\n[Sorted] Orders organized by price." << endl;
    }

    void processOrder() {
        if (orderQueue.empty()) {
            cout << "\n[Empty] No orders to process." << endl;
            return;
        }
        Order* current = orderQueue.front();
        cout << "\n[Processing] Order #" << current->id << " for " << current->customerName << endl;
        undoStack.push_back(current);
        orderQueue.erase(orderQueue.begin());
    }

    void undoLastAction() {
        if (undoStack.empty()) {
            cout << "\n[Error] Nothing to undo." << endl;
            return;
        }
        Order* restored = undoStack.back();
        undoStack.pop_back();
        orderQueue.insert(orderQueue.begin(), restored);
        cout << "\n[Undo] Order #" << restored->id << " restored to queue." << endl;
    }
};

int main() {
    RestaurantManagementSystem rms;
    int choice, id, priority;
    string name, item;
    double price;

    while (true) {
        cout << "\n1. Add Order\n2. Display\n3. Search\n4. Sort\n5. Process\n6. Undo\n0. Exit\nChoice: ";
        if (!(cin >> choice)) break; 
        if (choice == 0) break;

        switch (choice) {
            case 1:
                cout << "ID: "; cin >> id;
                cin.ignore();
                cout << "Name: "; getline(cin, name);
                cout << "Item: "; getline(cin, item);
                cout << "Price: "; cin >> price;
                cout << "Priority: "; cin >> priority;
                rms.addOrder(id, name, item, price, priority);
                break;
            case 2: rms.displayOrders(); break;
            case 3: cout << "Enter ID: "; cin >> id; rms.searchOrder(id); break;
            case 4: rms.sortByPrice(); break;
            case 5: rms.processOrder(); break;
            case 6: rms.undoLastAction(); break;
        }
    }
    return 0;
}
