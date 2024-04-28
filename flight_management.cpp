// Please refer the README.md file for detailed report of each and every functions used in the program.
#include<iostream>
#include<climits>
using namespace std;


class Flight
{
    string flight_name;
    int flight_id;
    int flight_cap;
    float flight_arrival_time, flight_departure_time;
    string flight_class;
public:
    // ctor
    Flight(){}
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
};

class LinkedListNode
{

    Flight *obj;
    LinkedListNode *next;
    LinkedListNode(){}
    LinkedListNode(Flight *obj){
        this->obj = obj;
        this->next = NULL;
    }
    friend class FlightManagement;
    friend class Flight;
};

class FlightManagement
{
    LinkedListNode *head;
    LinkedListNode *tail;
    int size;
public:
    FlightManagement()
    {
        this->size = 0;
        head = NULL;
        tail = NULL;
    }
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

    void delete_record(int id)
    {
        LinkedListNode *temp = head;
        bool flag = false;
        while(temp->next != NULL)
        {
            if(temp->next->obj->flight_id == id)
            {
                temp->next = temp->next->next;
                flag = true;
            }
            temp = temp->next;
        }
        if(flag == true){
            size--;
            cout<<"Record deleted successfully.\n";
        }
        else cout<<"No such record exists.\n";
        
    }
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
    
    int get_no_of_flights()
    {
        return size;
    }

    bool is_empty()
    {
        if(size == 0) return 1;
        return 0;
    }

    float get_flight_with_longest_stay()
    {
        LinkedListNode *temp = head;
        float maxstay = 0.00;
        while(temp->next->next != NULL)
        {
            maxstay = max(temp->next->obj->flight_departure_time - 
                temp->next->obj->flight_arrival_time, maxstay);
            temp = temp->next;
        }
        return maxstay;
    }

    LinkedListNode* merge_acc_to_arrival_time(LinkedListNode* a, LinkedListNode* b) 
    {
        // SC O(1)
        LinkedListNode *c = new LinkedListNode();
        LinkedListNode *temp = c;
        while(a != NULL && b != NULL)
        {
            if(a->obj->flight_arrival_time <= b->obj->flight_arrival_time)
            {
                temp->next = a;
                a = a->next;
                temp = temp->next; 
            }
            else
            {
                temp->next= b;
                b = b->next;
                temp = temp->next;
            }

        }
        if(a == NULL) temp->next = b;
        else temp->next = a;
        return c->next;
    }
    LinkedListNode* sort_acc_to_arr_time(LinkedListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        // to find the left middle elem
        LinkedListNode *slow = head;
        LinkedListNode *fast = head;
        while(fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        // now slow is at left middle
        LinkedListNode *left = head;
        LinkedListNode *right = slow->next;
        slow->next = NULL;
        left = sort_acc_to_arr_time(left);
        right = sort_acc_to_arr_time(right);
        LinkedListNode *c = merge_acc_to_arrival_time(left, right);
        return c;
    }

    LinkedListNode* merge_acc_to_departure_time(LinkedListNode* a, LinkedListNode* b) 
    {
        // SC O(1)
        LinkedListNode *c = new LinkedListNode();
        LinkedListNode *temp = c;
        while(a != NULL && b != NULL)
        {
            if(a->obj->flight_departure_time <= b->obj->flight_departure_time)
            {
                temp->next = a;
                a = a->next;
                temp = temp->next; 
            }
            else
            {
                temp->next= b;
                b = b->next;
                temp = temp->next;
            }

        }
        if(a == NULL) temp->next = b;
        else temp->next = a;
        return c->next;
    }

    LinkedListNode* sort_acc_to_dep_time(LinkedListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        // to find the left middle elem
        LinkedListNode *slow = head;
        LinkedListNode *fast = head;
        while(fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        // now slow is at left middle
        LinkedListNode *left = head;
        LinkedListNode *right = slow->next;
        slow->next = NULL;
        left = sort_acc_to_dep_time(left);
        right = sort_acc_to_dep_time(right);
        LinkedListNode *c = merge_acc_to_departure_time(left, right);
        return c;
    }
    LinkedListNode* merge_acc_to_stay_time(LinkedListNode* a, LinkedListNode* b) 
    {
        // SC O(1)
        LinkedListNode *c = new LinkedListNode();
        LinkedListNode *temp = c;
        while(a != NULL && b != NULL)
        {
            if(a->obj->flight_departure_time - a->obj->flight_arrival_time <= 
                b->obj->flight_departure_time - b->obj->flight_arrival_time)
            {
                temp->next = a;
                a = a->next;
                temp = temp->next; 
            }
            else
            {
                temp->next= b;
                b = b->next;
                temp = temp->next;
            }

        }
        if(a == NULL) temp->next = b;
        else temp->next = a;
        return c->next;
    }

    LinkedListNode* sort_acc_to_stay_time(LinkedListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        // to find the left middle elem
        LinkedListNode *slow = head;
        LinkedListNode *fast = head;
        while(fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        // now slow is at left middle
        LinkedListNode *left = head;
        LinkedListNode *right = slow->next;
        slow->next = NULL;
        left = sort_acc_to_stay_time(left);
        right = sort_acc_to_stay_time(right);
        LinkedListNode *c = merge_acc_to_stay_time(left, right);
        return c;
    }
    void get_sorted_on_arrival_time()
    {
        head = sort_acc_to_arr_time(head);
    }

    void get_sorted_on_departure_time()
    {
       head = sort_acc_to_dep_time(head);
    }

    void get_sorted_on_stay_time()
    {
        head = sort_acc_to_stay_time(head);
    }
};

int main()
{
    FlightManagement fm;
    fm.insert_record("SpiceJet", 126, 300, 16.00, 24.00, "VVIP");
    fm.insert_record("SpiceJet", 125, 300, 18.00, 20.00, "Public");
    fm.insert_record("AirIndia", 122, 300, 14.00, 15.00, "VIP");
    fm.insert_record("SpiceJet", 121, 300, 12.00, 23.00, "VVIP");
    cout<<"Normal printing\n";
    fm.print_records();
    cout<<endl;
    cout<<"Arr time\n";
    fm.get_sorted_on_arrival_time();
    fm.print_records();
    cout<<endl;
    cout<<"dep time\n";
    fm.get_sorted_on_departure_time();
    fm.print_records();
    cout<<endl;
    cout<<"Stay time\n";
    fm.get_sorted_on_stay_time();
    fm.print_records();
}
