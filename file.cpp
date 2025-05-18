#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Record {
    int id;
    string field1, field2, field3;
    Record* next;
};

class Module {
private:
    Record* head = nullptr;
    string moduleName, label1, label2, label3;

public:
    Module(string name, string l1, string l2, string l3)
        : moduleName(name), label1(l1), label2(l2), label3(l3) {}

    ~Module() {
        while (head) {
            Record* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool idExists(int id) {
        Record* temp = head;
        while (temp) {
            if (temp->id == id) return true;
            temp = temp->next;
        }
        return false;
    }

    void addRecord(int id, string f1, string f2, string f3) {
        if (idExists(id)) {
            cout << "Error: Record with ID " << id << " already exists.\n";
            return;
        }
        Record* newRec = new Record{id, f1, f2, f3, nullptr};
        if (!head) {
            head = newRec;
        } else {
            Record* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newRec;
        }
        cout << moduleName << " record added successfully.\n";
    }

    Record* searchRecord(int id) {
        Record* temp = head;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void updateRecord(int id, string f1, string f2, string f3) {
        Record* rec = searchRecord(id);
        if (rec) {
            rec->field1 = f1;
            rec->field2 = f2;
            rec->field3 = f3;
            cout << moduleName << " record updated successfully.\n";
        } else {
            cout << "Error: Record not found.\n";
        }
    }

    void deleteRecord(int id) {
        if (!head) {
            cout << "Error: No records to delete.\n";
            return;
        }

        if (head->id == id) {
            Record* del = head;
            head = head->next;
            delete del;
            cout << "Record deleted successfully.\n";
            return;
        }

        Record* temp = head;
        while (temp->next && temp->next->id != id)
            temp = temp->next;

        if (temp->next) {
            Record* del = temp->next;
            temp->next = temp->next->next;
            delete del;
            cout << "Record deleted successfully.\n";
        } else {
            cout << "Error: Record not found.\n";
        }
    }

    void displayRecords() {
        if (!head) {
            cout << "No records found.\n";
            return;
        }

        cout << "\n--- " << moduleName << " Records ---\n";
        cout << left << setw(10) << "ID" << setw(20) << label1
             << setw(20) << label2 << setw(20) << label3 << "\n";
        cout << string(70, '-') << endl;

        Record* temp = head;
        while (temp) {
            cout << left << setw(10) << temp->id << setw(20) << temp->field1
                 << setw(20) << temp->field2 << setw(20) << temp->field3 << "\n";
            temp = temp->next;
        }
    }

    void sortByField1() {
        if (!head || !head->next) return;

        bool swapped;
        do {
            swapped = false;
            Record* current = head;
            while (current->next) {
                if (current->field1 > current->next->field1) {
                    swap(current->id, current->next->id);
                    swap(current->field1, current->next->field1);
                    swap(current->field2, current->next->field2);
                    swap(current->field3, current->next->field3);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);

        cout << moduleName << " records sorted by " << label1 << ".\n";
    }

    void moduleMenu() {
        int choice;
        do {
            cout << "\n--- " << moduleName << " Module ---\n";
            cout << "1. Add Record\n2. Search Record\n3. Update Record\n";
            cout << "4. Delete Record\n5. Display Records\n6. Sort Records\n0. Back\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            int id;
            string f1, f2, f3;

            switch (choice) {
                case 1:
                    cout << "Enter ID: "; cin >> id;
                    cin.ignore();
                    cout << "Enter " << label1 << ": "; getline(cin, f1);
                    cout << "Enter " << label2 << ": "; getline(cin, f2);
                    cout << "Enter " << label3 << ": "; getline(cin, f3);
                    addRecord(id, f1, f2, f3);
                    break;

                case 2:
                    cout << "Enter ID to search: "; cin >> id;
                    if (Record* r = searchRecord(id))
                        cout << "Found: "<<endl<<" Name: "<< r->field1 <<endl<<" Email: "<< r->field2 <<endl<<" Status: "<< r->field3 << "\n";
                    else
                        cout << "Record not found.\n";
                    break;

                case 3:
                    cout << "Enter ID to update: "; cin >> id;
                    cin.ignore();
                    cout << "Enter new " << label1 << ": "; getline(cin, f1);
                    cout << "Enter new " << label2 << ": "; getline(cin, f2);
                    cout << "Enter new " << label3 << ": "; getline(cin, f3);
                    updateRecord(id, f1, f2, f3);
                    break;

                case 4:
                    cout << "Enter ID to delete: "; cin >> id;
                    deleteRecord(id);
                    break;

                case 5:
                    displayRecords();
                    break;

                case 6:
                    sortByField1();
                    break;

                case 0:
                    break;

                default:
                    cout << "Invalid option. Try again.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    Module customers("Customer", "Name", "Email", "Status");
    Module sales("Sales", "Item", "Amount", "Date");
    Module campaigns("Campaign", "Title", "Start", "End");
    Module tickets("Ticket", "Subject", "Status", "Assignee");

    int choice;
    do {
        cout << "\n==========Welcome to Customer Manegmet System(CRM) System ==========\n\n";
        cout << "1. Customer Module\n2. Sales Module\n";
        cout << "3. Campaign Module\n4. Ticket Module\n0. Exit\n";
        cout << "Select a module: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: customers.moduleMenu(); break;
            case 2: sales.moduleMenu(); break;
            case 3: campaigns.moduleMenu(); break;
            case 4: tickets.moduleMenu(); break;
            case 0: cout << "Exiting CRM System. Goodbye!\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
