#include <iostream>
#include <string.h>
#include <limits>
#include <cctype>

using namespace std;

#define MAXBUS 10
#define MAXPASS 50

int main_choice;
const int admin_pass = 1234;
const int max_tries = 5;
int bus_index = 0;
int pass_index = 0;
float total_sales = 0;
int last_booking_start = 0;
int last_booking_count = 0;

struct bus_details {
    int busno;
    char route[30];
    int avail_seats;
    char date[12];
    char dept_time[10];
    char jour_time[10];
    float price;
};

struct passenger_details {
    char name[20];
    int age;
    int busno;  
};

struct passenger_details pass[MAXPASS];
struct bus_details bus[MAXBUS];


void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidDateFormat(const char* date) {
   
    if (strlen(date) != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    
    
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }
    
    return true;
}

bool isValidTimeFormat(const char* time) {
   
    if (strlen(time) != 5) return false;
    if (time[2] != '-') return false;
    
   
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (!isdigit(time[i])) return false;
    }
    
    
    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');
    
    return (hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60);
}

bool busExists(int busno) {
    for (int i = 0; i < bus_index; i++) {
        if (bus[i].busno == busno) {
            return true;
        }
    }
    return false;
}

void show_sales() {
    cout << endl << "--------------" << endl;
    cout << "Total Sales: Rs. " << total_sales << endl;
    cout << "----------------" << endl;
    return;
}

void book_ticket() {
    if (bus_index == 0) {
        cout << "No buses available for booking.\n";
        return;
    }

   
    if (pass_index >= MAXPASS) {
        cout << "System passenger limit reached. Cannot book more tickets.\n";
        return;
    }

    int bno;
    cout << "\nEnter Bus Number to book: ";
    while (!(cin >> bno)) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a valid bus number: ";
    }

    bool found = false;
    int bus_idx = -1;
    
    for (int i = 0; i < bus_index; i++) {
        if (bus[i].busno == bno) {
            found = true;
            bus_idx = i;
            cout << "Bus Found! Route: " << bus[i].route << ", Date: " << bus[i].date 
                 << ", Seats Left: " << bus[i].avail_seats << endl;

            if (bus[i].avail_seats <= 0) {
                cout << "Sorry, no seats available on this bus!\n";
                return;
            }
            break;
        }
    }

    if (!found) {
        cout << "Bus not found with number " << bno << ".\n";
        return;
    }

    int qty;
    cout << "How many tickets do you want to book? ";
    while (!(cin >> qty) || qty <= 0) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a positive number: ";
    }

    if (qty > bus[bus_idx].avail_seats) {
        cout << "Only " << bus[bus_idx].avail_seats << " seats are available.\n";
        return;
    }

    
    if (pass_index + qty > MAXPASS) {
        cout << "Sorry, system cannot book more than " << (MAXPASS - pass_index) 
             << " passengers at this time.\n";
        return;
    }

    
    last_booking_start = pass_index;
    last_booking_count = qty;

   
    int starting_index = pass_index;
    for (int j = 0; j < qty; j++) {
        cout << "Enter Passenger " << (j + 1) << " Name: ";
        cin >> pass[starting_index + j].name;
        
        cout << "Age: ";
        while (!(cin >> pass[starting_index + j].age) || pass[starting_index + j].age <= 0 || 
               pass[starting_index + j].age > 120) {
            clearInputBuffer();
            cout << "Invalid age. Please enter a number between 1 and 120: ";
        }
        
      
        pass[starting_index + j].busno = bno;
        
        cout << "End of Passenger " << (j + 1) << " entry.\n";
    }
    
   
    pass_index += qty;

    cout << "----------------------------" << endl;
    cout << "ALL Passenger/s Added Successfully" << endl;
    cout << "----------------------------" << endl;

    float total = qty * bus[bus_idx].price;
    cout << "Total Amount: Rs. " << total << "\nConfirm booking? (1=Yes, 0=No): ";
    int confirm;
    while (!(cin >> confirm) || (confirm != 0 && confirm != 1)) {
        clearInputBuffer();
        cout << "Invalid input. Enter 1 for Yes or 0 for No: ";
    }

    if (confirm == 1) {
        bus[bus_idx].avail_seats -= qty;
        total_sales += total;
        cout << "Booking successful! " << qty << " tickets booked.\n";
    } else {
        cout << "Booking cancelled.\n";
        pass_index -= qty; 
    }

    cout << bus[bus_idx].avail_seats << " seats remaining on this bus.\n";
}

void show_ticket() {
    if (bus_index == 0) {
        cout << "No buses available in the system.\n";
        return;
    }
    
    if (pass_index == 0) {
        cout << "No bookings have been made yet.\n";
        return;
    }
    
    int busno;
    cout << "Enter Bus Number: ";
    while (!(cin >> busno)) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a valid bus number: ";
    }
    
    bool found_bus = false;
    int bus_idx = -1;
    
    for (int i = 0; i < bus_index; i++) {
        if (bus[i].busno == busno) {
            found_bus = true;
            bus_idx = i;
            break;
        }
    }
    
    if (!found_bus) {
        cout << "Bus not found with number " << busno << ".\n";
        return;
    }
    
    // Check if there are any bookings for this bus
    bool found_bookings = false;
    for (int j = 0; j < pass_index; j++) {
        if (pass[j].busno == busno) {
            found_bookings = true;
            break;
        }
    }
    
    if (!found_bookings) {
        cout << "No bookings found for bus number " << busno << ".\n";
        return;
    }
    
    cout << "\n====== TICKET DETAILS ======\n";
    cout << "Bus No: " << bus[bus_idx].busno << endl;
    cout << "Route: " << bus[bus_idx].route << endl;
    cout << "Date: " << bus[bus_idx].date << endl;
    cout << "Departure Time: " << bus[bus_idx].dept_time << endl;
    cout << "Journey Time: " << bus[bus_idx].jour_time << endl;
    cout << "Ticket Price per Person: Rs. " << bus[bus_idx].price << endl;
    
    cout << "\n--- Passenger Details ---\n";
    int passenger_count = 0;
    float total_fare = 0;
    
    // Modified to show all passengers on this bus
    for (int j = 0; j < pass_index; j++) {
        if (pass[j].busno == busno) {
            cout << "Name: " << pass[j].name << ", Age: " << pass[j].age << endl;
            passenger_count++;
            total_fare += bus[bus_idx].price;
        }
    }
    
    cout << "\nTotal Passengers: " << passenger_count << endl;
    cout << "Total Fare: Rs. " << total_fare << endl;
    cout << "===========================\n";
}

void search_bus() {
    if (bus_index == 0) {
        cout << "No buses available to search.\n";
        return;
    }

    char search_route[30];
    cout << "Enter Route (Format: FROM-TO. NO SPACES): ";
    cin >> search_route;
    
    if (strlen(search_route) < 3) {
        cout << "Route name too short. Please enter a valid route.\n";
        return;
    }

    bool found = false;
    
    cout << "\n===== SEARCH RESULTS =====\n";
    
    for (int i = 0; i < bus_index; i++) {
        
        char route_lower[30];
        char search_lower[30];
        
        strcpy(route_lower, bus[i].route);
        strcpy(search_lower, search_route);
        
        for (int j = 0; route_lower[j]; j++) {
            route_lower[j] = tolower(route_lower[j]);
        }
        
        for (int j = 0; search_lower[j]; j++) {
            search_lower[j] = tolower(search_lower[j]);
        }
        
        // Check if the search term is a substring of the route
        if (strstr(route_lower, search_lower) != NULL) {
            found = true;
            cout << "\n+++++++++" << endl;
            cout << "Bus Found" << endl;
            cout << "++++++++++" << endl;
            cout << "Bus Number: " << bus[i].busno << endl;
            cout << "Route: " << bus[i].route << endl;
            cout << "Available Seats: " << bus[i].avail_seats << endl;
            cout << "Date (DD-MM-YYYY): " << bus[i].date << endl;
            cout << "Departure Time (HH-MM 24HR): " << bus[i].dept_time << endl;
            cout << "Journey Time: " << bus[i].jour_time << endl;
            cout << "Ticket Price: Rs. " << bus[i].price << endl;
        }
    }
    
    if (!found) {
        cout << endl << "Sorry. No Buses Found for route: " << search_route << endl;
    }
}

void add_bus() {
   
    if (bus_index >= MAXBUS) {
        cout << "Maximum bus limit reached. Cannot add more buses.\n";
        return;
    }

    int num_bus;
    cout << "Enter the number of Buses to add: ";
    while (!(cin >> num_bus) || num_bus <= 0) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a positive number: ";
    }

    while (bus_index + num_bus > MAXBUS) {
        cout << "Sorry, MAX Bus Count Reached." << endl;
        cout << "You can only add up to " << (MAXBUS - bus_index) << " more buses." << endl;
        cout << "Enter a new number of buses to add: ";
        while (!(cin >> num_bus) || num_bus <= 0) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a positive number: ";
        }
    }

    for (int i = bus_index; i < bus_index + num_bus; i++) {
        cout << "\n--- Enter details for Bus " << (i + 1) << " ---" << endl;

        
        cout << "Enter Bus Number: ";
        while (!(cin >> bus[i].busno) || bus[i].busno <= 0) {
            clearInputBuffer();
            cout << "Invalid bus number. Please enter a positive number: ";
        }

       
        bool duplicate = false;
        for (int j = 0; j < i; j++) {
            if (bus[j].busno == bus[i].busno) {
                cout << "Bus number already exists. Please enter a different number.\n";
                i--; 
                duplicate = true;
                break;
            }
        }
        if (duplicate) continue;

       
        cout << "Enter Route (Separate To and From with '-' and no spaces): ";
        cin >> bus[i].route;
        while (strlen(bus[i].route) < 3 || !strchr(bus[i].route, '-')) {
            cout << "Invalid route format. Please use FROM-TO format: ";
            cin >> bus[i].route;
        }

        
        cout << "Enter Available Seats: ";
        while (!(cin >> bus[i].avail_seats) || bus[i].avail_seats <= 0) {
            clearInputBuffer();
            cout << "Invalid seat count. Please enter a positive number: ";
        }

        
        cout << "Enter Date (DD-MM-YYYY): ";
        cin >> bus[i].date;
        while (!isValidDateFormat(bus[i].date)) {
            cout << "Invalid date format. Use DD-MM-YYYY: ";
            cin >> bus[i].date;
        }

        
        cout << "Enter Departure Time (HH-MM 24HR): ";
        cin >> bus[i].dept_time;
        while (!isValidTimeFormat(bus[i].dept_time)) {
            cout << "Invalid time format. Use HH-MM (24-hour): ";
            cin >> bus[i].dept_time;
        }

        
        cout << "Enter Journey Time (e.g., 2hrs30min): ";
        cin >> bus[i].jour_time;

       
        cout << "Enter Ticket Price: ";
        while (!(cin >> bus[i].price) || bus[i].price <= 0) {
            clearInputBuffer();
            cout << "Invalid price. Please enter a positive number: ";
        }

        cout << "End of Bus " << bus[i].busno << " entry.\n";
    }

    bus_index += num_bus;

    cout << "----------------------------" << endl;
    cout << "ALL BUS/ES Added Successfully" << endl;
    cout << "----------------------------" << endl;
}

void show_bus() {
    if (bus_index == 0) {
        cout << "No buses added yet." << endl;
        return;
    }

    cout << endl << "------------------------------" << endl;
    cout << "Showing Buses from The Feed" << endl;
    cout << "----------------------------" << endl;

    for (int i = 0; i < bus_index; i++) {
        cout << "Bus Number: " << bus[i].busno << endl;
        cout << "Route: " << bus[i].route << endl;
        cout << "Available Seats: " << bus[i].avail_seats << endl;
        cout << "Date (DD-MM-YYYY): " << bus[i].date << endl;
        cout << "Departure Time (HH-MM 24HR): " << bus[i].dept_time << endl;
        cout << "Journey Time: " << bus[i].jour_time << endl;
        cout << "Ticket Price: Rs. " << bus[i].price << endl;

        cout << endl << "End of Bus " << bus[i].busno << endl;
        cout << "----------------------------------------" << endl;
    }
}

void delete_bus() {
    if (bus_index == 0) {
        cout << "No buses available to delete.\n";
        return;
    }

    cout << "-----------------" << endl;
    cout << "    DELETE BUS   " << endl;
    cout << "-----------------" << endl;
    
    int busno;
    cout << "Enter Bus Number to be Deleted: ";
    while (!(cin >> busno)) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a valid bus number: ";
    }

    bool found = false;

    for (int i = 0; i < bus_index; i++) {
        if (bus[i].busno == busno) {
            // Check if there are bookings for this bus
            bool has_bookings = false;
            for (int j = 0; j < pass_index; j++) {
                if (pass[j].busno == busno) {
                    has_bookings = true;
                    break;
                }
            }
            
            if (has_bookings) {
                cout << "Cannot delete bus with existing bookings.\n";
                return;
            }
            
            // Shift all buses after this one up by one position
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

void modify_bus() {
    if (bus_index == 0) {
        cout << "No buses available to modify.\n";
        return;
    }

    int busno;
    cout << "Enter Bus Number to modify: ";
    while (!(cin >> busno)) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a valid bus number: ";
    }

    bool found = false;

    for (int i = 0; i < bus_index; i++) {
        if (bus[i].busno == busno) {
            found = true;
            cout << "\nModifying Bus " << busno << " details\n";
            cout << "Current details:\n";
            cout << "1. Route: " << bus[i].route << endl;
            cout << "2. Available Seats: " << bus[i].avail_seats << endl;
            cout << "3. Date: " << bus[i].date << endl;
            cout << "4. Departure Time: " << bus[i].dept_time << endl;
            cout << "5. Journey Time: " << bus[i].jour_time << endl;
            cout << "6. Price: Rs. " << bus[i].price << endl;
            
            int field;
            cout << "\nEnter the field number to modify (1-6) or 0 to cancel: ";
            while (!(cin >> field) || field < 0 || field > 6) {
                clearInputBuffer();
                cout << "Invalid input. Enter a number between 0 and 6: ";
            }
            
            switch (field) {
                case 0:
                    cout << "Modification cancelled.\n";
                    return;
                case 1:
                    cout << "Enter new Route (Separate To and From with '-' and no spaces): ";
                    cin >> bus[i].route;
                    while (strlen(bus[i].route) < 3 || !strchr(bus[i].route, '-')) {
                        cout << "Invalid route format. Please use FROM-TO format: ";
                        cin >> bus[i].route;
                    }
                    break;
                case 2:
                    cout << "Enter new Available Seats: ";
                    while (!(cin >> bus[i].avail_seats) || bus[i].avail_seats <= 0) {
                        clearInputBuffer();
                        cout << "Invalid seat count. Please enter a positive number: ";
                    }
                    break;
                case 3:
                    cout << "Enter new Date (DD-MM-YYYY): ";
                    cin >> bus[i].date;
                    while (!isValidDateFormat(bus[i].date)) {
                        cout << "Invalid date format. Use DD-MM-YYYY: ";
                        cin >> bus[i].date;
                    }
                    break;
                case 4:
                    cout << "Enter new Departure Time (HH-MM 24HR): ";
                    cin >> bus[i].dept_time;
                    while (!isValidTimeFormat(bus[i].dept_time)) {
                        cout << "Invalid time format. Use HH-MM (24-hour): ";
                        cin >> bus[i].dept_time;
                    }
                    break;
                case 5:
                    cout << "Enter new Journey Time: ";
                    cin >> bus[i].jour_time;
                    break;
                case 6:
                    cout << "Enter new Ticket Price: ";
                    while (!(cin >> bus[i].price) || bus[i].price <= 0) {
                        clearInputBuffer();
                        cout << "Invalid price. Please enter a positive number: ";
                    }
                    break;
            }
            
            cout << "Bus details updated successfully!\n";
            return;
        }
    }

    if (!found) {
        cout << "No bus found with number " << busno << ".\n";
    }
}

void admin_menu() {
    int admin_choice;
    while (true) {
        cout << "\n-----------------" << endl;
        cout << "     ADMIN MENU   " << endl;
        cout << "-----------------" << endl;
        cout << "1. SHOW BUSSES" << endl;
        cout << "2. ADD BUSSES" << endl;
        cout << "3. MODIFY BUS" << endl;
        cout << "4. REMOVE BUSSES" << endl;
        cout << "5. Show Total Sales" << endl;
        cout << "6. BACK TO MAIN MENU" << endl;
        cout << "+++++++++++++++++" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> admin_choice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (admin_choice) {
            case 1:
                show_bus();
                break;
            case 2:
                add_bus();
                break;
            case 3:
                modify_bus();
                break;
            case 4:
                delete_bus();
                break;
            case 5:
                show_sales();
                break;
            case 6:
                return; // Go back to main menu
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void admin() {
    int cli_pass;
    int tries = 0;
    cout << endl << "Enter Admin Password: ";
    while (!(cin >> cli_pass)) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a numeric password: ";
    }
    
    while (cli_pass != admin_pass) {
        tries++;
        if (tries >= max_tries) {
            cout << "Max tries reached. Access denied.\n";
            cout << "Returning to main menu...\n";
            return;
        }
        cout << "Wrong password. " << (max_tries - tries) << " attempts remaining.\n";
        cout << "Enter Admin Password: ";
        while (!(cin >> cli_pass)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a numeric password: ";
        }
    }

    admin_menu();
}

void cancel_ticket() {
    if (pass_index == 0) {
        cout << "No bookings have been made yet.\n";
        return;
    }

    int busno;
    cout << "Enter Bus Number for cancellation: ";
    while (!(cin >> busno)) {
        clearInputBuffer();
        cout << "Invalid input. Please enter a valid bus number: ";
    }
    
   
    bool bus_found = false;
    int bus_idx = -1;
    
    for (int i = 0; i < bus_index; i++) {
        if (bus[i].busno == busno) {
            bus_found = true;
            bus_idx = i;
            break;
        }
    }
    
    if (!bus_found) {
        cout << "Bus not found with number " << busno << ".\n";
        return;
    }
    
   
    bool bookings_found = false;
    for (int i = 0; i < pass_index; i++) {
        if (pass[i].busno == busno) {
            bookings_found = true;
            break;
        }
    }
    
    if (!bookings_found) {
        cout << "No bookings found for bus number " << busno << ".\n";
        return;
    }
    
    
    cout << "\n--- Passengers on Bus " << busno << " ---\n";
    for (int i = 0; i < pass_index; i++) {
        if (pass[i].busno == busno) {
            cout << "Index: " << i << ", Name: " << pass[i].name << ", Age: " << pass[i].age << endl;
        }
    }
    
    
    int cancel_index;
    cout << "\nEnter the Index of the passenger to cancel: ";
    while (!(cin >> cancel_index) || cancel_index < 0 || cancel_index >= pass_index || 
           pass[cancel_index].busno != busno) {
        clearInputBuffer();
        cout << "Invalid index. Please enter a valid passenger index shown above: ";
    }
    
    
    char confirm;
    cout << "Confirm cancellation for " << pass[cancel_index].name << "? (Y/N): ";
    cin >> confirm;
    
    if (toupper(confirm) == 'Y') {
        
        bus[bus_idx].avail_seats++;
        
        
        total_sales -= bus[bus_idx].price;
        
       
        if (cancel_index == pass_index - 1) {
           
            pass_index--;
        } else {
            
            for (int i = cancel_index; i < pass_index - 1; i++) {
                pass[i] = pass[i + 1];
            }
            pass_index--;
        }
        
        cout << "Ticket successfully cancelled.\n";
        cout << "Seat returned to available pool.\n";
    } else {
        cout << "Cancellation aborted.\n";
    }
}

void user() {
    int user_choice;
    while (true) {
        cout << "\n===== USER MENU =====\n";
        cout << "1. View Available Buses\n";
        cout << "2. Book Tickets\n";
        cout << "3. Show Tickets\n";
        cout << "4. Search For Buses\n";
        cout << "5. Cancel Ticket\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> user_choice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (user_choice) {
            case 1: show_bus(); break;
            case 2: book_ticket(); break;
            case 3: show_ticket(); break;
            case 4: search_bus(); break;
            case 5: cancel_ticket(); break;
            case 6: return;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}

void main_screen() {
    cout << "\n*\n";
    cout << "*        BUS RESERVATION SYSTEM        *\n";
    cout << "*\n";
    
    int main_choice;
    while (true) {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Admin Login\n";
        cout << "2. User Portal\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> main_choice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

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

int main() {
    main_screen();
    return 0;
}
