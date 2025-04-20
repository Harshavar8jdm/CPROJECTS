#include<iostream>
#include<string.h>

using namespace std;

#define MAXBUS 10
#define MAXPASS 10

int main_choice;
const int admin_pass = 1234;
const int max_tries = 5;
int bus_index = 0;
int pass_index = 0;
float total_sales=0;
int last_booking_start = 0;
int last_booking_count = 0;


struct bus_details{

    int busno;
    char route[30];
    int avail_seats;
    char date[12];
    char dept_time[10];
    char jour_time[10];
    float price;

};


struct passenger_details{

    char name[20];
    int age;

};

struct passenger_details pass[MAXPASS];
struct bus_details bus[MAXBUS];

void show_sales(){
    cout << endl <<"--------------" <<endl;
    cout << "Total Sales: " << total_sales <<endl;
    cout <<"----------------" << endl;
    return;

}

void book_ticket(){
    if (bus_index == 0) {
        cout << "No buses available for booking.\n";
        return;
    }

    int bno;
    cout << "\nEnter Bus Number to book: ";
    cin >> bno;

    for (int i = 0; i < bus_index; i++) {
        if (bus[i].busno == bno) {
            cout << "Bus Found! Route: " << bus[i].route << ", Date: " << bus[i].date << ", Seats Left: " << bus[i].avail_seats << endl;

            if (bus[i].avail_seats <= 0) {
                cout << "Sorry, no seats available!\n";
                return;
            }

            int qty;
            cout << "How many tickets do you want to book? ";
            cin >> qty;
            last_booking_start = pass_index;
            last_booking_count = qty;


            if (qty > bus[i].avail_seats) {
                cout << "Only " << bus[i].avail_seats << " seats are available.\n";
                return;
            }
            pass_index =  pass_index + qty;
            
            for (int i = 0; i < qty; i++) {
                cout << "Enter Passenger " << (i + 1) << " Name: ";
                cin >> pass[pass_index].name;
                cout << "Age: ";
                cin >> pass[pass_index].age;
                cout << "End of Passenger " << (i + 1) << " entry.\n";
                
            }
            

            cout << "----------------------------" << endl;
            cout << "ALL Passenger/s Added Successfully" << endl;
            cout << "----------------------------" << endl;

            float total = qty * bus[i].price;
            total_sales = total_sales + total;
            cout << "Total Amount: Rs. " << total << "\nConfirm booking? (1=Yes, 0=No): ";
            int confirm;
            cin >> confirm;

            if (confirm == 1) {
                bus[i].avail_seats -= qty;
                cout << "Booking successful! " << qty << " tickets booked.\n";
            } else {
                cout << "Booking cancelled.\n";
            }

            cout << bus[i].avail_seats << " seats remaining on this bus.\n";

            return;
        }
    }

    cout << "Bus not found with number " << bno << ".\n";
    
    }

void show_ticket() {
        int busno;
        cout<<"Enter Bus Number";
        cin>>busno;
        cout << "\n====== TICKET DETAILS ======\n";
        for (int i = 0; i < bus_index; i++) {
            if (bus[i].busno == busno) {
                cout << "Bus No: " << bus[i].busno << endl;
                cout << "Route: " << bus[i].route << endl;
                cout << "Date: " << bus[i].date << endl;
                cout << "Departure Time: " << bus[i].dept_time << endl;
                cout << "Journey Time: " << bus[i].jour_time << endl;
                cout << "Ticket Price per Person: Rs. " << bus[i].price << endl;
    
                cout << "\n--- Passenger Details ---\n";
                for (int j = last_booking_start; j < last_booking_start + last_booking_count; j++) {
                    cout << "Name: " << pass[j].name << ", Age: " << pass[j].age << endl;
                }
    
                float total = last_booking_count * bus[i].price;
                cout << "\nTotal Fare: Rs. " << total << endl;
                cout << "===========================\n";
                return;
            }
        }
    
        cout << "Error: Bus not found for ticket display.\n";
}

void search_bus(){
    char search_route[30];
    cout<<"Enter Route. (Format: FROM-TO. NO SPACES)";
    cin>>search_route;

    bool found = false;


    for(int i = 0; i<bus_index ;i++){

        if(strcmp(bus[i].route,search_route) == 0){

            found = true;
            cout<< endl << "+++++++++"<<endl;
            cout << "Bus Found" << endl;
            cout<< "++++++++++"<<endl;
            cout<<"Bus Number: "<<bus[i].busno<<endl;
            cout<<"Route: "<<bus[i].route<<endl;
            cout<<"Available Seats: "<<bus[i].avail_seats<<endl;
            cout<<"Date(DD-MM-YYYY)"<<bus[i].date<<endl;
            cout<<"Departure Time (HH-MM  24HR): "<<bus[i].dept_time<<endl;
            cout<<"Journey Time: "<<bus[i].jour_time<<endl;
            cout<<"Ticket Price: "<<bus[i].price<<endl;

        }
        
    }
    
    if(!found){
        cout<<endl<<"Sorry. No Buses Found"<<endl;
    }

    return;

}


void add_bus() {
    int num_bus;
    cout << "Enter the number of Buses to add: ";
    cin >> num_bus;

    while (bus_index + num_bus > MAXBUS) {
        cout << "Sorry, MAX Bus Count Reached." << endl;
        cout << "You can only add up to " << (MAXBUS - bus_index) << " more buses." << endl;
        cout << "Enter a new number of buses to add: ";
        cin >> num_bus;
    }

    for (int i = bus_index; i < bus_index + num_bus; i++) {
        cout << "\n--- Enter details for Bus " << (i + 1) << " ---" << endl;

        cout << "Enter Bus Number: ";
        cin >> bus[i].busno;

        cout << "Enter Route (Separate To and From with '-' and no spaces): ";
        cin >> bus[i].route;

        cout << "Enter Available Seats: ";
        cin >> bus[i].avail_seats;

        cout << "Enter Date (DD-MM-YYYY): ";
        cin >> bus[i].date;

        cout << "Enter Departure Time (HH-MM 24HR): ";
        cin >> bus[i].dept_time;

        cout << "Enter Journey Time: ";
        cin >> bus[i].jour_time;

        cout << "Enter Ticket Price: ";
        cin >> bus[i].price;

        cout << "End of Bus " << bus[i].busno << " entry.\n";
    }

    bus_index += num_bus;

    cout << "----------------------------" << endl;
    cout << "ALL BUS/ES Added Successfully" << endl;
    cout << "----------------------------" << endl;

    return;

}

void show_bus(){
    
    if (bus_index == 0) {
        cout << "No buses added yet." << endl;
        return;
    }

    cout<<endl<<"------------------------------"<<endl;
    cout<<"Showing Busses from The Feed"<<endl;
    cout<<"----------------------------"<<endl;

    for(int i = 0; i<bus_index; i++){
        cout<<"Bus Number: "<<bus[i].busno<<endl;
        cout<<"Route: "<<bus[i].route<<endl;
        cout<<"Available Seats: "<<bus[i].avail_seats<<endl;
        cout<<"Date(DD-MM-YYYY)"<<bus[i].date<<endl;
        cout<<"Departure Time (HH-MM  24HR): "<<bus[i].dept_time<<endl;
        cout<<"Journey Time: "<<bus[i].jour_time<<endl;
        cout<<"Ticket Price: "<<bus[i].price<<endl;

        cout<<endl<<"End of Bus "<<bus[i].busno<<endl;
        cout<<"----------------------------------------"<<endl;

    }

    return;

}

void delete_bus(){
    cout << "-----------------" << endl;
    cout << "    DELETE BUS   " << endl;
    cout << "-----------------" << endl;
    
    int busno;
    cout<<"Enter Bus Number to be Deleted: ";
    cin>>busno;

    bool found  = false;

    for (int i = 0; i < bus_index; i++) {
        if (bus[i].busno == busno) {
            
            for (int j = i; j < bus_index - 1; j++) {
                bus[j] = bus[j + 1];
            }

            bus_index--; 
            found = true;
            cout << "Bus number " << busno << " deleted successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "No bus found with number " << busno << ".\n";
    }

}

void admin_menu() {
    int admin_choice;
    while (true) {
        cout << "-----------------" << endl;
        cout << "     ADMIN MENU   " << endl;
        cout << "-----------------" << endl;
        cout << "1. SHOW BUSSES" << endl;
        cout << "2. ADD BUSSES" << endl;
        cout << "3. REMOVE BUSSES" << endl;
        cout << "4. Show Total Sales" << endl; 
        cout << "5. BACK TO MAIN MENU" << endl;
        cout << "+++++++++++++++++" << endl;
        cout << "Enter your choice: ";
        cin >> admin_choice;

        switch (admin_choice) {
            case 1:
                show_bus();
                break;
            case 2:
                add_bus();
                break;
            case 3:
                delete_bus();
                break;
            case 4:
                show_sales();
                break;
            case 5:
                return; // Go back to main menu
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}


void admin(){

    int cli_pass;
    int tries=0;
    cout<<endl<<"Enter Admin Password: ";
    cin>>cli_pass;
    while((cli_pass != admin_pass)){
        tries++;
        cout<<"Sorry. Try Again."<<endl;
        cout<<"Enter Admin Password:";
        cin>>cli_pass;
        if(tries>max_tries){
            cout<<"Max Tries Reached"<<endl;
            cout<<"Exiting..."<<endl;
            exit(1);
        }
        
    }

    admin_menu();
    
    
}

void user(){
    int user_choice;
    while (true) {
        cout << "\n===== USER MENU =====\n";
        cout << "1. View Available Buses\n";
        cout << "2. Book Tickets\n";
        cout << "3. Show Tickets\n";
        cout << "4. Search For Busses\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> user_choice;

        switch (user_choice) {
            case 1: show_bus(); break;
            case 2: book_ticket(); break;
            case 3: show_ticket(); break;
            case 4: search_bus(); break;

            case 5: return;
            default: cout << "Invalid choice. Try again.\n";
        }
    }

}


void main_screen() {
    int main_choice;
    while (true) {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Admin Login\n";
        cout << "2. User Portal\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> main_choice;

        switch (main_choice) {
            case 1: admin(); break;
            case 2: user(); break;
            case 3:
                cout << "Thank you for using the Bus Booking System.\n";
                return;
            default:
                cout << "Please enter a valid choice.\n";
        }
    }
}

int main(){

    main_screen();
    return 0;

}