#include<iostream>
#include<climits>
#include<limits>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;
// Class representing a flight
class Flight
{
public:
    string flight_name; // Name of the flight
    int flight_id; // Unique identifier for the flight
    int flight_cap; // Capacity of the flight
    float flight_arrival_time, flight_departure_time; // Arrival and departure times of the flight
    string flight_class; // Class of the flight (e.g., economy, business)

    // Default constructor
    Flight(){}
    // Parameterized constructor
    Flight(string f_name, int f_id, int f_cap, float f_at, float f_dt,
    string flight_class)
    {
        this->flight_name = f_name;
        this->flight_id = f_id;
        this->flight_cap = f_cap;
        this->flight_arrival_time = f_at;
        this->flight_departure_time = f_dt;
    }
    friend class FlightManagement;
    friend class LinkedListNode;
};

// Class representing a node in a linked list
class LinkedListNode
{
    Flight *obj; // Pointer to a Flight object
    LinkedListNode *next; // Pointer to the next node in the linked list
    LinkedListNode(){}
    LinkedListNode(Flight *obj){
        this->obj = obj;
        this->next = NULL;
    }
    friend class FlightManagement;
    friend class Flight;
};

// Custom comparison function for sorting flights based on different criteria
bool compareFlights(Flight* a, Flight* b, string criterion) {
    if (criterion == "arrival_time") {
        return a->flight_arrival_time < b->flight_arrival_time;
    } else if (criterion == "departure_time") {
        return a->flight_departure_time < b->flight_departure_time;
    } else {
        return (a->flight_departure_time - a->flight_arrival_time) < (b->flight_departure_time - b->flight_arrival_time);
    }
}

// Class for managing flights
class FlightManagement
{
    LinkedListNode *head; // Pointer to the head of the linked list
    LinkedListNode *tail; // Pointer to the tail of the linked list
    int size; // Size of the linked list
public:
    // Constructor
    FlightManagement()
    {
        this->size = 0;
        head = NULL;
        tail = NULL;
    }
    // Function to insert a new record of a flight
    void insert_record(string flight_name, int flight_id,int flight_cap,
    float flight_arrival_time, float flight_departure_time, string flight_class)
    {
        Flight *fl = new Flight(flight_name, flight_id, flight_cap, flight_arrival_time, 
                                flight_departure_time, flight_class);
        if(size == 0)
        {
            LinkedListNode *temp = new LinkedListNode(fl);
            head = temp;
            tail = temp;
        }
        else
        {
            LinkedListNode *temp = new LinkedListNode(fl);
            tail->next = temp;
            tail = tail->next;
        }
        size++;
    }

    // Function to delete a record of a flight
    void delete_record(int id)
    {
        LinkedListNode *temp = head;
        LinkedListNode *prev = NULL;
        bool flag = false;
        while(temp != NULL)
        {
            if(temp->obj->flight_id == id)
            {
                if(prev == NULL) {
                    head = head->next;
                } else {
                    prev->next = temp->next;
                    if(temp == tail) tail = prev;
                }
                delete temp;
                flag = true;
                size--;
                cout<<"Record deleted successfully.\n";
                break;
            }
            prev = temp;
            temp = temp->next;
        }
        if(!flag) cout<<"No such record exists.\n";    
    }

    // Function to print all flight records
    void print_records()
    {
        LinkedListNode *temp = head;
        while(temp != NULL)
        {
            cout<<temp->obj->flight_name<<" "<<temp->obj->flight_id<<" "
            <<temp->obj->flight_class<<" "<<temp->obj->flight_arrival_time
            <<" "<<temp->obj->flight_departure_time<<" "<<temp->obj->flight_class<<endl;
            temp = temp->next;
        }
    }
    
    // Function to get the number of flights
    int get_no_of_flights()
    {
        return size;
    }

    // Function to check if the flight management system is empty
    bool is_empty()
    {
        return size == 0;
    }

    // Function to merge two linked lists based on specified criteria
    LinkedListNode* merge(LinkedListNode* a, LinkedListNode* b, string criterion) 
    {
        LinkedListNode *c = new LinkedListNode();
        LinkedListNode *temp = c;
        while(a != NULL && b != NULL)
        {
            if(compareFlights(a->obj, b->obj, criterion))
            {
                temp->next = a;
                a = a->next;
            }
            else
            {
                temp->next= b;
                b = b->next;
            }
            temp = temp->next;
        }
        if(a == NULL) temp->next = b;
        else temp->next = a;
        return c->next;
    }

    // Function to sort the linked list based on specified criteria
    LinkedListNode* merge_sort(LinkedListNode* head, string criterion) {
        if(head == NULL || head->next == NULL) return head;
        LinkedListNode *slow = head;
        LinkedListNode *fast = head;
        while(fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        LinkedListNode *left = head;
        LinkedListNode *right = slow->next;
        slow->next = NULL;
        left = merge_sort(left, criterion);
        right = merge_sort(right, criterion);
        LinkedListNode *c = merge(left, right, criterion);
        return c;
    }

    // Function to sort the flights based on specified criterion
    void sort_flights(string criterion)
    {
        head = merge_sort(head, criterion);
    }

    // Function to calculate the shortest path between airports using Dijkstra's algorithm
    void shortest_path_calculator(int source, int destination)
    {
        // Initialize distances to infinity
        vector<int> dist(size, INT_MAX);
        // Priority queue to store vertices and their distances from the source
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        // Set distance of source to 0
        dist[source] = 0;
        pq.push({0, source});

        // Dijkstra's algorithm
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            LinkedListNode *temp = head;
            while (temp != NULL) {
                if (temp->obj->flight_id == u) {
                    break;
                }
                temp = temp->next;
            }

            // Traverse all adjacent vertices of u
            while (temp != NULL) {
                int v = temp->obj->flight_id;
                int weight = 1; // Assuming equal weight for all edges

                // Relaxation step
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }

                temp = temp->next;
            }
        }

        // Output the shortest distance from source to destination
        cout << "Shortest distance from " << source << " to " << destination << " is: " << dist[destination] << endl;
    }
};
void clearInputBuffer() {
    // Read and discard characters until newline is encountered
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Main function
int main()
{
    // Create an instance of FlightManagement
    FlightManagement fm;

    // Menu-driven loop
    int choice;
    do {
        cout << "\nFlight Management System Menu:\n";
        cout << "1. Insert a flight record\n";
        cout << "2. Delete a flight record\n";
        cout << "3. Print all flight records\n";
        cout << "4. Sort flights\n";
        cout << "5. Calculate shortest path between airports\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                string flight_name, flight_class;
                int flight_id, flight_cap;
                float flight_arrival_time, flight_departure_time;
                cout << "Enter flight name: ";
                getline(cin, flight_name);
                clearInputBuffer();
                cout << "Enter flight ID: ";
                cin >> flight_id;
                cout << "Enter flight capacity: ";
                cin >> flight_cap;
                cout << "Enter arrival time: ";
                cin >> flight_arrival_time;
                cout << "Enter departure time: ";
                cin >> flight_departure_time;
                cout << "Enter flight class: ";
                cin >> flight_class;
                fm.insert_record(flight_name, flight_id, flight_cap, flight_arrival_time, flight_departure_time, flight_class);
                break;
            }
            case 2: {
                int id;
                cout << "Enter the flight ID to delete: ";
                cin >> id;
                fm.delete_record(id);
                break;
            }
            case 3: {
                cout << "Flight records:\n";
                fm.print_records();
                break;
            }
            case 4: {
                string criterion;
                cout << "Enter sorting criterion (arrival_time/departure_time/stay_time): ";
                cin >> criterion;
                fm.sort_flights(criterion);
                cout << "Flights sorted based on " << criterion << ":\n";
                fm.print_records();
                break;
            }
            case 5: {
                int source, destination;
                cout << "Enter source airport ID: ";
                cin >> source;
                cout << "Enter destination airport ID: ";
                cin >> destination;
                fm.shortest_path_calculator(source, destination);
                break;
            }
            case 0: {
                cout << "Exiting...\n";
                break;
            }
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while(choice != 0);

    return 0;
}