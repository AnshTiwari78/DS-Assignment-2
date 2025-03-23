#include<iostream>
#include<string>
#include <cstdlib>

using namespace std;

struct parking_lot {
    string vehicle_number;
    string owner;
    int hours;
    string type;
    int otp;
};

struct parking_admin {
    string username;
    string password;
    string pcompany_name, address;
    float revenue = 0, LMV2_wheeler_price = 0, LMV4_wheeler_price = 0, HMV_price = 0;
    parking_lot** LMV2_wheeler_parking;
    parking_lot** LMV4_wheeler_parking;
    parking_lot** HMV_parking;
    int LMV2_wheeler_capacity = 0; 
    int LMV4_wheeler_capacity = 0;
    int HMV_capacity = 0; 
    int total_2wheeler_slips=0, total_4wheeler_slips=0, total_hmv_slips=0;
    parking_admin* next;
};

parking_admin* system_users_list = NULL;

parking_lot** capacity_setter(string message, int& capacity) {
    bool condi = true;
    int size;
    while(condi) {
        cout << endl << message;
        cin >> size;
        if (size == 0) {
            capacity = 0; 
            return NULL;
        }
        if(size > 0) {
            parking_lot** arr = new parking_lot*[size];
	    for(int i=0; i<size; i++){
		arr[i]=nullptr;
	    }
            capacity = size; // Store the capacity
            return arr;
        }
        else{
            cout << endl << "Invalid entry for size, it cannot be negative, please enter again.";
            continue;
        }
    }
    return NULL;
}

float price_setter(string message) {
    bool condi = true;
    float price;
    while(condi) {
        cout << endl << message;
        cin >> price;
        if (price <= 0) {
        cout << endl << "Invalid entry for PRICE, price cannot be zero or negative, please enter again.";
        continue;
        }
        else {
        return price;
        }
    }
    return 0;
}

void create_admin() {
    string in_username, in_password, in_pcompany_name, in_address;

    while(1){
    cout<<endl<<"Create a USERNAME for your profile registration : ";
    cin>>in_username;
    parking_admin* temp = system_users_list;
    bool found = false;
    while (temp != NULL) {
        if (temp->username == in_username) {
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (found == false) {
        break;
    }
    else{
        cout<<endl<<"The username already exists, try choosing a different username.";
        continue;
    }
    }
    
    cout<<endl<<"Create a strong PASSWORD for your profile : ";
    cin>>in_password;
    cout<<endl << "Enter the registered name of your PARKING COMPANY : ";
    cin>>in_pcompany_name;
    cout<<endl << "Enter the address of your PARKING COMPANY : ";
    cin>>in_address;

    parking_admin* new_admin = new parking_admin;

    new_admin->username = in_username;
    new_admin->password = in_password;
    new_admin->pcompany_name = in_pcompany_name;
    new_admin->address = in_address;
    
    new_admin->LMV2_wheeler_parking = capacity_setter("Enter the capacity of 2 wheelers in your parking space (Enter 0 if No space is available): ", new_admin->LMV2_wheeler_capacity);
    if (new_admin->LMV2_wheeler_parking != NULL) {
        new_admin->LMV2_wheeler_price = price_setter("Enter the PER HOUR PRICE for PARKING a single 2 WHEELER : ");
    }
    new_admin->LMV4_wheeler_parking = capacity_setter("Enter the capacity of 4 wheelers in your parking space (Enter 0 if No space is available): ", new_admin->LMV4_wheeler_capacity);
    if (new_admin->LMV4_wheeler_parking != NULL) {
        new_admin->LMV4_wheeler_price = price_setter("Enter the PER HOUR PRICE for PARKING a single 4 WHEELER : ");
    }
    new_admin->HMV_parking = capacity_setter("Enter the capacity of Heavy Motor Vehicles in your parking space (Enter 0 if No space is available): ", new_admin->HMV_capacity);
    if (new_admin->HMV_parking != NULL) {
        new_admin->HMV_price = price_setter("Enter the PER HOUR PRICE for PARKING a single Heavy Motor Vehicles : ");
    }
    new_admin->next = NULL;
    if (new_admin->HMV_parking == NULL && new_admin->LMV4_wheeler_parking == NULL && new_admin->LMV2_wheeler_parking == NULL) {
        delete(new_admin);
        cout << endl << "REGISTRATION FAILED! You need to have at least some parking space to register.";
        return;
    }

    if(system_users_list == NULL) {
        system_users_list = new_admin;
        cout<<endl<<"REGISTRATION SUCCESSFUL!!! \n------------------------------------------------------------------------\nTHE PROFILE CREATED IS AS FOLLOWS :\n"<<new_admin->pcompany_name<<"\nADDRESS --> "<<new_admin->address<<"\nPROFILE USERNAME --> "<<new_admin->username<<"\nPARKING CAPACITY AND PRICE DETAILS... : "<<"\nFOR TWO WHEELERS   :\t\tCAPACITY--> "<<new_admin->LMV2_wheeler_capacity<<"\t\tPRICE--> "<<new_admin->LMV2_wheeler_price<<" Rupees\nFOR FOUR WHEELERS  :\t\tCAPACITY--> "<<new_admin->LMV4_wheeler_capacity<<"\t\tPRICE--> "<<new_admin->LMV4_wheeler_price<<" Rupees\nFOR HEAVY VEHICLES :\t\tCAPACITY--> "<<new_admin->HMV_capacity<<"\t\tPRICE--> "<<new_admin->HMV_price<<" Rupees\n------------------------------------------------------------------------\n"<<"LOGIN TO CONTINUE.";
        return;
    }
    else{
        parking_admin* temp = system_users_list;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_admin;
        cout<<endl<<"REGISTRATION SUCCESSFUL!!! \n------------------------------------------------------------------------\nTHE PROFILE CREATED IS AS FOLLOWS :\n"<<new_admin->pcompany_name<<"\nADDRESS --> "<<new_admin->address<<"\nPROFILE USERNAME --> "<<new_admin->username<<"\nPARKING CAPACITY AND PRICE DETAILS... : "<<"\nFOR TWO WHEELERS   :\t\tCAPACITY--> "<<new_admin->LMV2_wheeler_capacity<<"\t\tPRICE--> "<<new_admin->LMV2_wheeler_price<<" Rupees\nFOR FOUR WHEELERS  :\t\tCAPACITY--> "<<new_admin->LMV4_wheeler_capacity<<"\t\tPRICE--> "<<new_admin->LMV4_wheeler_price<<" Rupees\nFOR HEAVY VEHICLES :\t\tCAPACITY--> "<<new_admin->HMV_capacity<<"\t\tPRICE--> "<<new_admin->HMV_price<<" Rupees\n------------------------------------------------------------------------\n"<<"LOGIN TO CONTINUE.";
        return;
    }
}

parking_admin* admin_login() {
    string in_username, in_password;
    cout<<endl<< "Enter the username of the profile : ";
    cin>>in_username;

    if(system_users_list == NULL) {
        cout<<endl<<"Username not found, LOGIN FAILED!!!";
        return NULL;
    }

    parking_admin* temp = system_users_list;
    bool found = false;
    while(temp != NULL) {
        if(temp->username == in_username) {
            found = true;
            break;
        }
        temp = temp->next;
    }
    if(found == false){
        cout << endl << "Username not found, LOGIN FAILED!!!";
        return NULL;
    }
    else{
        cout<<endl<<"Enter the password of your profile : ";
        cin >> in_password;
        if(in_password == temp->password) {
        cout<<"\n-----------------------------------------------------------\n"<< "LOGIN SUCCESSFUL!!!  Welcome " << temp->pcompany_name << ".";
        return temp;
        }
        else {
        cout << endl << "Entered password is wrong, LOGIN FAILED!!!";
        return NULL;
        }
    }
}

int p_hash_function(string vnumber, parking_lot** p_space, int capacity) {
    int nlength = vnumber.length();
    int codehash, vnum_sum = 0;

    // Calculate hash based on vehicle number
    for (int i = 0; i < nlength; i++) {
        vnum_sum += static_cast<int>(vnumber[i]);
    }

    codehash = vnum_sum % capacity;

    // If the slot is empty or the vehicle number is already parked, return the hashcode
    if(p_space[codehash] == NULL || p_space[codehash]->vehicle_number == vnumber) {
        return codehash;
    }

    // Linear probing in case of collision
    for (int i = 1; i <= capacity + 2; i++) {
        codehash = (codehash + i) % capacity;
        if (p_space[codehash] == NULL || p_space[codehash]->vehicle_number == vnumber) {
            return codehash;
        }
    }
    return -1;  // In case no space is available
}



void park_vehicle(parking_admin* admin) {
    string in_vehicle_number, in_type, name;
    int vehicle_type, hashcode, in_hours;
    float price_paid;
    parking_lot** storer;

    cout<<endl<<"Enter the vehicle number of vehicle to be parked : ";
    cin>>in_vehicle_number;

    cout<<endl<<"Enter name of the vehicle owner : ";
    cin>>name;

    cout<<endl<<"Enter the hours for which you want to park the vehicle : ";
    cin>>in_hours;

    while(1) {
        cout<<endl<<"Select the type of vehicle to be parked :\nEnter '1' for 2 wheeler,\nEnter '2' for 4 wheeler,\nEnter '3' for heavy motor vehicles,\nYOUR CHOICE : ";
        cin>>vehicle_type;
        if(vehicle_type == 1) {
            in_type = "2-WHEELER";
            if(admin->LMV2_wheeler_parking == NULL) {
                cout << endl << "No space available to park the " << in_type << " vehicles.";
                return;
            }
            storer = admin->LMV2_wheeler_parking;
            hashcode = p_hash_function(in_vehicle_number, admin->LMV2_wheeler_parking, admin->LMV2_wheeler_capacity);
            price_paid = in_hours*admin->LMV2_wheeler_price;
            break;
        }
        if (vehicle_type == 2) {
            in_type = "4-WHEELER";
            if (admin->LMV4_wheeler_parking == NULL) {
                cout << endl << "No space available to park the " << in_type << " vehicles.";
                return;
            }
            storer = admin->LMV4_wheeler_parking;
            hashcode = p_hash_function(in_vehicle_number, admin->LMV4_wheeler_parking, admin->LMV4_wheeler_capacity);
            price_paid = in_hours*admin->LMV4_wheeler_price;
            break;
        }
        if (vehicle_type == 3) {
            in_type = "HMV";
            if (admin->HMV_parking == NULL) {
                cout<<endl<<"No space available to park the "<<in_type<<" vehicles.";
                return;
            }
            storer = admin->HMV_parking;
            hashcode = p_hash_function(in_vehicle_number, admin->HMV_parking, admin->HMV_capacity);
            price_paid = in_hours*admin->HMV_price;
            break;
        }
        else {
            cout<<endl<<"Invalid choice, select a valid type.";
            continue;
        }
    }

    if (hashcode != -1) {
        parking_lot* slip = new parking_lot;
        slip->vehicle_number = in_vehicle_number;
        slip->owner = name;
        slip->hours = in_hours;
        slip->type = in_type;
        slip->otp = rand() % 9000 + 1000; 
        storer[hashcode] = slip;
        admin->revenue = admin->revenue + price_paid ;
        if(vehicle_type==1){
            admin->total_2wheeler_slips++;
        }
        if(vehicle_type==2){
            admin->total_4wheeler_slips++;
        }
        if(vehicle_type==3){
            admin->total_hmv_slips++;
        }
        
        cout<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\t\t\t"<<admin->pcompany_name<<" - Parking Ticket"<<"\nVehicle Number --> "<<slip->vehicle_number<<"\nSlip Generated for --> "<<slip->owner<<"\nTime alloted --> "<<slip->hours<<" Hours\n\nParking lot alloted in "<<slip->type<<" parking is "<<hashcode+1<<"\nPrice paid = "<<price_paid<<" Rupees \nOTP Generated -> "<<slip->otp<<"\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<"\n-----------------------------------------------------------";
    }
    else {
        cout<<endl<<"No space available in the "<<in_type<< " parking lot!";
    }
}


void free_parkinglot(parking_admin* admin){
    string vnumber, in_type;
    int hashcode, in_otp, vehicle_type;
    parking_lot** storer;
    cout<<endl<<"Enter the vehicle number to be displaced from parking lot : ";
    cin>>vnumber;
    
    while(1) {
        cout<<endl<<"Select the type to vehicle to be removed :\nEnter '1' for 2 wheeler,\nEnter '2' for 4 wheeler,\nEnter '3' for heavy motor vehicles,\nYOUR CHOICE : ";
        cin>>vehicle_type;
        if(vehicle_type == 1) {
            in_type = "2-WHEELER";
            if(admin->LMV2_wheeler_parking == NULL) {
            cout << endl << "No parking space exists for the " << in_type << " vehicles.";
            return;
            }
            storer = admin->LMV2_wheeler_parking;
            hashcode = p_hash_function(vnumber, admin->LMV2_wheeler_parking, admin->LMV2_wheeler_capacity);
            break;
        }
        if (vehicle_type == 2) {
            in_type = "4-WHEELER";
            if (admin->LMV4_wheeler_parking == NULL) {
            cout << endl << "No parking space exists for the " << in_type << " vehicles.";
            return;
            }
            storer = admin->LMV4_wheeler_parking;
            hashcode = p_hash_function(vnumber, admin->LMV4_wheeler_parking, admin->LMV4_wheeler_capacity);
            break;
        }
        if (vehicle_type == 3) {
            in_type = "HMV";
            if (admin->HMV_parking == NULL) {
            cout<<endl<<"No parking space exists for "<<in_type<<" vehicles.";
            return;
            }
            storer = admin->HMV_parking;
            hashcode = p_hash_function(vnumber, admin->HMV_parking, admin->HMV_capacity);
            break;
        }
        else {
            cout<<endl<<"Invalid choice, select a valid type.";
            continue;
        }
    }
    
    if(hashcode==-1||storer[hashcode]->vehicle_number!=vnumber){
    cout<<endl<<"No vehicle found in the parking space having entered number.";
    return;
    }
    
    else{
    cout<<endl<<"Enter the OTP for removing the vehicle from parking : ";
    cin>>in_otp;
    
    if(storer[hashcode]->otp==in_otp){
    cout<<endl<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl<<"The parking slot number "<<hashcode+1<<" in "<<storer[hashcode]->type<<" parking space is now empty.";
    cout<<endl<<"The OTP matched! The vehicle can be taken out of the parking lot."<<endl<<"Thankyou "<<storer[hashcode]->owner<<" for parking with us, visit again!"<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-----------------------------------------------------------";
    delete storer[hashcode];
    storer[hashcode]=nullptr;
    return;
    }
    else{
    cout<<endl<<"The OTP does not match! Permission to take the vehicle denied.";
    return;
    }
    }
}



void search_vehicle(parking_admin* admin){
    string vnumber, in_type;
    int hashcode, vehicle_type;
    parking_lot** storer;
    cout<<endl<<"Enter the vehicle number to be searched in the parking lot : ";
    cin>>vnumber;
    
    while(1) {
        cout<<endl<<"Select the type to vehicle to be searched :\nEnter '1' for 2 wheeler,\nEnter '2' for 4 wheeler,\nEnter '3' for heavy motor vehicles,\nYOUR CHOICE : ";
        cin>>vehicle_type;
        if(vehicle_type == 1) {
            in_type = "2-WHEELER";
            if(admin->LMV2_wheeler_parking == NULL) {
            cout << endl << "No parking space exists for the " << in_type << " vehicles.";
            return;
            }
            storer = admin->LMV2_wheeler_parking;
            hashcode = p_hash_function(vnumber, admin->LMV2_wheeler_parking, admin->LMV2_wheeler_capacity);
            break;
        }
        if (vehicle_type == 2) {
            in_type = "4-WHEELER";
            if (admin->LMV4_wheeler_parking == NULL) {
            cout << endl << "No parking space exists for the " << in_type << " vehicles.";
            return;
            }
            storer = admin->LMV4_wheeler_parking;
            hashcode = p_hash_function(vnumber, admin->LMV4_wheeler_parking, admin->LMV4_wheeler_capacity);
            break;
        }
        if (vehicle_type == 3) {
        in_type = "HMV";
        if (admin->HMV_parking == NULL) {
        cout<<endl<<"No parking space exists for "<<in_type<<" vehicles.";
        return;
        }
        storer = admin->HMV_parking;
        hashcode = p_hash_function(vnumber, admin->HMV_parking, admin->HMV_capacity);
        break;
        }
        else {
        cout<<endl<<"Invalid choice, select a valid type.";
        continue;
        }
    }
    if(hashcode==-1){
    cout<<endl<<"No vehicle found in the parking space having the entered number.";
    return;
    }
    else if(storer[hashcode]==NULL){
    cout<<endl<<"No vehicle found in the parking space having the entered number.";
    return;
    }
    else if(storer[hashcode]->vehicle_number!=vnumber){
    cout<<endl<<"No vehicle found in the parking space having the entered number.";
    return;
    }
    else{
    cout<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-----------------------------------------------------------";
    cout<<endl<<"The vehicle found at parking slot -> "<<hashcode+1<<", in the "<<storer[hashcode]->type<<" parking space."<<endl<<"The vehicle has a total parking time of "<<storer[hashcode]->hours<<" hours.";
    cout<<endl<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    return;
    }
}



void view_slot_details(parking_admin* admin){
    string vnumber, in_type;
    int slot_number, vehicle_type, storer_capacity;
    parking_lot** storer;
    
    while(1) {
        cout<<endl<<"Select the type to vehicle parking to be searched :\nEnter '1' for 2 wheeler,\nEnter '2' for 4 wheeler,\nEnter '3' for heavy motor vehicles,\nYOUR CHOICE : ";
        cin>>vehicle_type;
        if(vehicle_type == 1) {
        in_type = "2-WHEELER";
        if(admin->LMV2_wheeler_parking == NULL) {
        cout << endl << "No parking space exists for the "<< in_type << " vehicles.";
        return;
        }
        storer = admin->LMV2_wheeler_parking;
        storer_capacity = admin->LMV2_wheeler_capacity;
        break;
        }
        if (vehicle_type == 2) {
        in_type = "4-WHEELER";
        if (admin->LMV4_wheeler_parking == NULL) {
        cout << endl << "No parking space exists for the " << in_type << " vehicles.";
        return;
        }
        storer = admin->LMV4_wheeler_parking;
        storer_capacity = admin->LMV4_wheeler_capacity;
        break;
        }
        if (vehicle_type == 3) {
        in_type = "HMV";
        if (admin->HMV_parking == NULL) {
        cout<<endl<<"No parking space exists for "<<in_type<<" vehicles.";
        return;
        }
        storer = admin->HMV_parking;
        storer_capacity = admin->HMV_capacity;
        break;
        }
        else {
        cout<<endl<<"Invalid choice, select a valid type.";
        continue;
        }
    }
    
    while(1){
    cout<<endl<<"Enter the slot number to see its details in the parking lot : ";
    cin>>slot_number;
    if (slot_number<1||slot_number>storer_capacity){
    cout<<endl<<"Invalid or Non-Exisisting slot number, please re-enter a valid slot number.";
    continue;
    }
    break;
    }
    
    slot_number = slot_number-1;
    
    if(storer[slot_number]==NULL){
    cout<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-----------------------------------------------------------";
    cout<<endl<<"No vehicle parked,,, parking slot number "<<slot_number+1<<" is Empty.";
    cout<<endl<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    return;
    }
    else{
    cout<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-----------------------------------------------------------";
    cout<<endl<<"The number of vehicle parked in the parking slot -> "<<slot_number+1<<", in the "<<storer[slot_number]->type<<" parking space is --> "<<storer[slot_number]->vehicle_number<<endl<<"The name of the vehicle owner is --> "<<storer[slot_number]->owner<<endl<<"The vehicle has a total parking time of --> "<<storer[slot_number]->hours<<" hours.";
    cout<<endl<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    return;
    }
}



void display_revenue_details(parking_admin* admin){
    cout<<endl<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n----------------------------------------------------------------------------------";
    
    cout<<endl<<"\t\t\tREVENUE GENERATION DETAILS : "<<admin->pcompany_name<<endl<<"The total revenue generated = "<<admin->revenue<<" Rupees. "<<endl<<"The analysis of varying parking spaces and profit : "<<endl<<"Total 2 wheelers parking slips generated --> "<<admin->total_2wheeler_slips<<"\t\tRevenue = "<<admin->total_2wheeler_slips*admin->LMV2_wheeler_price<<" Rupees,,, "<<endl<<"Total 4 wheelers parking slips generated --> "<<admin->total_4wheeler_slips<<"\t\tRevenue = "<<admin->total_4wheeler_slips*admin->LMV4_wheeler_price<<" Rupees,,, "<<endl<<"Total hmv parking slips generated --> "<<admin->total_hmv_slips<<"\t\tRevenue = "<<admin->total_hmv_slips*admin->HMV_price<<" Rupees,,, ";
    
    cout<<endl<<"----------------------------------------------------------------------------------\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    return;
}




void display_parking_slots(parking_lot** storer, int size, string name){
    cout<<endl<<"========================"<<name<<"========================";
    for(int i=0; i<size; i++){
        cout<<endl<<"_______________________________________________________________________\n||";
        for(int j=0; j<4; j++){
        string printer, start; 
        if(i+1<10){
        start = " [ ";
        }
        else{
        start = " [";
        }
        if(i+1>size){
        printer = "                |";
        }
        else if (storer[i]==NULL){
        printer = start + to_string(i+1) + "] AVAILABLE |";
        }
        else {
        printer = start + to_string(i+1) + "] OCCUPIED  |";
        }
        cout<<printer;
        i++;
        }
        
        i = i-4;
        cout<<"|"<<endl<<"||";
        
        for(int k=0; k<4; k++){
        string printer, vnum;
        if(i+1>size){
        printer = "                |";
        }
        else if(storer[i]==NULL){
        printer = " -------------- |";
        }
        else{
        vnum = storer[i]->vehicle_number ;
        printer = " -->" + vnum + "  |";
        }
        cout<<printer;
        i++;
        }
        
        i--;
        cout<<"|"<<endl<<"```````````````````````````````````````````````````````````````````````";
    }
    cout<<endl<<"=======================================================================";
}



void display_all_slots(parking_admin* admin){
    string in_type;
    int vehicle_type, storer_capacity;
    parking_lot** storer;
    
    while(1) {
        cout<<endl<<"Select the parking space to be displayed :\nEnter '1' for 2 wheeler,\nEnter '2' for 4 wheeler,\nEnter '3' for heavy motor vehicles,\nYOUR CHOICE : ";
        cin>>vehicle_type;
        if(vehicle_type == 1) {
        in_type = "2-WHEELER-PARKING-SPACE";
        if(admin->LMV2_wheeler_parking == NULL) {
        cout << endl << "No parking space exists for the "<< in_type << " vehicles.";
        return;
        }
        storer = admin->LMV2_wheeler_parking;
        storer_capacity = admin->LMV2_wheeler_capacity;
        break;
        }
        if (vehicle_type == 2) {
        in_type = "4-WHEELER-PARKING-SPACE";
        if (admin->LMV4_wheeler_parking == NULL) {
        cout << endl << "No parking space exists for the " << in_type << " vehicles.";
        return;
        }
        storer = admin->LMV4_wheeler_parking;
        storer_capacity = admin->LMV4_wheeler_capacity;
        break;
        }
        if (vehicle_type == 3) {
        in_type = "===HMV-PARKING-SPACE===";
        if (admin->HMV_parking == NULL) {
        cout<<endl<<"No parking space exists for "<<in_type<<" vehicles.";
        return;
        }
        storer = admin->HMV_parking;
        storer_capacity = admin->HMV_capacity;
        break;
        }
        else {
        cout<<endl<<"Invalid choice, select a valid type.";
        continue;
        }
    }
    display_parking_slots(storer, storer_capacity, in_type);
    return;
}



void parking_management_menu(parking_admin* user) {
    bool condition = true;
    while (condition) {
        cout<<endl<<endl<<"ENTER 1--> TO ALLOT A PARKING LOT TO THE USER" << endl;
        cout<<"ENTER 2--> TO REMOVE THE VEHICLE FROM PARKING LOT"<<endl;
        cout<<"ENTER 3--> TO SEARCH THE VEHICLE PARKING LOT"<<endl;
        cout<<"ENTER 4--> TO VIEW DETAILS OF A PARKING LOT"<<endl;
        cout<<"ENTER 5--> TO VIEW THE REVENUE GENERATED"<<endl;
        cout<<"ENTER 6--> TO DISPLAY THE STATUS OF PARKING LOTS"<<endl;
        cout<<"ENTER 7--> TO EXIT THE MENU"<<endl;
        int option;
        cout<<endl<<"Enter your choice --------> ";
        cin>>option;

        switch (option) {

            case 1: {
                park_vehicle(user);
                break;
            }

            case 2: {
                free_parkinglot(user);
                break;
            }
            
            case 3: {
                search_vehicle(user);
                break;
            }
            
            case 4: {
                view_slot_details(user);
                break;
            }
            
            case 5: {
                display_revenue_details(user);
                break;
            }
            
            case 6: {
                display_all_slots(user);
                break;
            }

            case 7: {
                cout<<endl<<"Exiting the menu,,,,,,,"; 
                condition = false;
                break;
            }
            
            
        }
    }
}

int main() {

    cout << endl << "-----------------------PARKING MANAGEMENT SYSTEM-----------------------";

    parking_admin* current_user = NULL;

    bool condition1 = true;

    while (condition1) {
        cout<<endl << endl << "ENTER 1--> TO LOGIN TO YOUR PROFILE"<<endl;
        cout<<"ENTER 2--> TO REGISTER AS A NEW USER"<<endl;
        cout<<"ENTER 3--> TO EXIT MENU"<<endl;
        int option;
        cout<<endl<<"Enter your choice --------> ";
        cin>>option;

        switch (option) {

            case 1: {
                current_user = admin_login();
                if (current_user != NULL) {
                    parking_management_menu(current_user);
                }
                break;
            }

            case 2: {
                create_admin();
                break;
            }

            case 3: {
                condition1 = false;
                break;
            }
        }
    }

}
