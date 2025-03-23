#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>

using namespace std;

struct parking_lot {
    string vehicle_number;
    string owner;
    int hours;
    string type;
    int otp;
};

struct waiting_parking_lot {
    string vehicle_number;
    string owner;
    int hours;
    string type;
    int otp;
    waiting_parking_lot* next;
};

struct parking_admin {
    string username;
    string password;
    string pcompany_name, address;
    float revenue = 0, LMV2_wheeler_price = 0, LMV4_wheeler_price = 0, HMV_price = 0;
    parking_lot** parking_space;
    waiting_parking_lot* waiting_list;
    int LMV2_wheeler_capacity = 0, LMV4_wheeler_capacity = 0, HMV_capacity = 0, total_capacity = 0; 
    int total_2wheeler_slips=0, total_4wheeler_slips=0, total_hmv_slips=0;
    parking_admin* next;
};

parking_admin* system_users_list = NULL;


int capacity_setter(string message, int limit) {
    int size;
    while(1) {
        cout<<endl<< message;
        cin>>size;
        if(size > limit) {
        return size;
        }
        else{
        cout<<endl<<"Invalid entry for size, please enter again.";
        continue;
        }
    }
    return 0;
}

float price_setter(string message) {
    bool condi = true;
    float price;
    while(condi) {
        cout << endl << message;
        cin >> price;
        if (price <= 0) {
        cout << endl << "Invalid entry for, the value cannot be zero or negative, please enter again.";
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
    cout<<endl<<"Create a username for your profile registration : ";
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
    
    cout<<endl<<"Create a strong password for your profile : ";
    cin>>in_password;
    cout<<endl << "Enter the registered name of your parking company : ";
    cin>>in_pcompany_name;
    cout<<endl << "Enter the address of your parking compnay : ";
    cin>>in_address;

    parking_admin* new_admin = new parking_admin;

    new_admin->username = in_username;
    new_admin->password = in_password;
    new_admin->pcompany_name = in_pcompany_name;
    new_admin->address = in_address;
    new_admin->next = NULL;
    
    int total_capacity = capacity_setter("Enter the total capacity of your parking lot : ", 0);
    new_admin->parking_space = new parking_lot*[total_capacity];;
    new_admin->total_capacity = total_capacity;
    for(int i=0; i<total_capacity; i++){
        new_admin->parking_space[i]=nullptr;
    }
    
    while(1){
    new_admin->LMV2_wheeler_capacity = capacity_setter("Enter the space available in parking lot for 2-wheeler vehicles ", -1);
    
    new_admin->LMV4_wheeler_capacity = capacity_setter("Enter the space available in parking lot for 4-wheeler vehicles ", -1);
    
    new_admin->HMV_capacity = capacity_setter("Enter the space available in parking lot for heavy motor vehicles ", -1);
    
    if (total_capacity != new_admin->LMV2_wheeler_capacity + new_admin->LMV4_wheeler_capacity + new_admin->HMV_capacity) {
        cout<<endl<<"The values for sizes entered for 2-wheelers, 4-wheelers, and HMVs does not match the total capacity of your parking lot. Therefore, re-enter the sizes.";
        continue;
    }
    else{
        break;
    }
    }
    
    if (new_admin->LMV2_wheeler_capacity > 0) {
        new_admin->LMV2_wheeler_price = price_setter("Enter the per hour price for parking a single 2-wheeler : ");
    }
    if (new_admin->LMV4_wheeler_capacity > 0) {
        new_admin->LMV4_wheeler_price = price_setter("Enter the per hour price for parking a single 4-wheeler : ");
    }
    if (new_admin->HMV_capacity > 0) {
        new_admin->HMV_price = price_setter("Enter the per hour price for parking a single heavy motor vehicles : ");
    }
    
    if(system_users_list == NULL) {
        system_users_list = new_admin;
        cout<<endl<<"REGISTRATION SUCCESSFUL!!! \n-----------------------------------------------------------\nTHE PROFILE CREATED IS AS FOLLOWS :\n"<<new_admin->pcompany_name<<"\nADDRESS --> "<<new_admin->address<<"\nPROFILE USERNAME --> "<<new_admin->username<<"\nPARKING CAPACITY AND PRICE DETAILS... : "<<"\nFOR TWO WHEELERS   :\t\tCAPACITY--> "<<new_admin->LMV2_wheeler_capacity<<"\t\tPRICE--> "<<new_admin->LMV2_wheeler_price<<" Rupees.\nFOR FOUR WHEELERS  :\t\tCAPACITY--> "<<new_admin->LMV4_wheeler_capacity<<"\t\tPRICE--> "<<new_admin->LMV4_wheeler_price<<" Rupees.\nFOR HEAVY VEHICLES :\t\tCAPACITY--> "<<new_admin->HMV_capacity<<"\t\tPRICE--> "<<new_admin->HMV_price<<" Rupees.\n-----------------------------------------------------------\n"<<"LOGIN TO CONTINUE.";
        return;
    }
    else{
        parking_admin* temp = system_users_list;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_admin;
        cout<<endl<<"REGISTRATION SUCCESSFUL!!! \n-----------------------------------------------------------\nTHE PROFILE CREATED IS AS FOLLOWS :\n"<<new_admin->pcompany_name<<"\nADDRESS --> "<<new_admin->address<<"\nPROFILE USERNAME --> "<<new_admin->username<<"\nPARKING CAPACITY AND PRICE DETAILS... : "<<"\nFOR TWO WHEELERS   :\t\tCAPACITY--> "<<new_admin->LMV2_wheeler_capacity<<"\t\tPRICE--> "<<new_admin->LMV2_wheeler_price<<" Rupees.\nFOR FOUR WHEELERS  :\t\tCAPACITY--> "<<new_admin->LMV4_wheeler_capacity<<"\t\tPRICE--> "<<new_admin->LMV4_wheeler_price<<" Rupees.\nFOR HEAVY VEHICLES :\t\tCAPACITY--> "<<new_admin->HMV_capacity<<"\t\tPRICE--> "<<new_admin->HMV_price<<" Rupees.\n-----------------------------------------------------------\n"<<"LOGIN TO CONTINUE.";
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



void delete_an_admin(){
string in_username, in_password;
cout<<endl<< "Enter the username of the profile : ";
cin>>in_username;

if(system_users_list == NULL) {
cout<<endl<<"Username not found, deletion process aborted!!!";
return;
}

parking_admin* temp = system_users_list;
parking_admin* prev = NULL;
bool found = false;
do {
if(temp->username == in_username) {
found = true;
break;
}
prev = temp;
temp = temp->next;
}while(temp != NULL);

if(found == false){
cout << endl << "Username not found, deletion process aborted!!!";
return;
}
else{
cout<<endl<<"Enter the password of your profile : ";
cin >> in_password;
if(in_password == temp->password) {
string confirm;
cout<<"If you delete your profile, all the related details will be permanently lost."<<endl;
cout<<"Enter 'YES' to confirm the deletion of the profile : ";
cin>>confirm;
if(confirm=="YES"){
if(prev == NULL) {  
system_users_list = temp->next;  
}
else{
prev->next = temp->next; 
}
delete temp;
cout<<endl<<"THE PROFILE HAS BEEN DELETED SUCCESSFULLY."<<endl;
}
else{
cout<<endl<<"Aborting the deletion process........"<<endl;
}
}
else {
cout<<endl<<"Entered password is wrong, deletion process aborted!!!";
}
}
}



int LMV2W_hash_function(string vnumber, parking_lot** p_space, int lmv2_capacity) {
    int nlength = vnumber.length();
    int codehash, vnum_sum = 0;

    for (int i = 0; i < nlength; i++) {
        vnum_sum += static_cast<int>(vnumber[i]);
    }

    codehash = vnum_sum % lmv2_capacity;

    // If the slot is empty or the vehicle number is already parked, return the hashcode
     if(p_space[codehash] == nullptr ){
            return codehash;
        }
     else if(p_space[codehash]->vehicle_number == vnumber){
            return codehash;
        }

    // Qadratic probing in case of collision
    for (int i = 1; i <= lmv2_capacity+1; i++) {
        codehash = (codehash + i + i*i) % lmv2_capacity;
        if(p_space[codehash] == nullptr ){
            return codehash;
        }
        else if(p_space[codehash]->vehicle_number == vnumber){
            return codehash;
        }
    }
    return -1;  // In case no space is available
}



int LMV4W_hash_function(string vnumber, parking_lot** p_space, int lmv2_capacity, int lmv4_capacity) {
    int nlength = vnumber.length();
    int codehash, vnum_sum = 0;

    for (int i = 0; i < nlength; i++) {
        vnum_sum += static_cast<int>(vnumber[i]);
    }

    codehash = lmv2_capacity + (vnum_sum % lmv4_capacity);

    // If the slot is empty or the vehicle number is already parked, return the hashcode
    if(p_space[codehash] == nullptr ){
            return codehash;
    }
    else if(p_space[codehash]->vehicle_number == vnumber){
            return codehash;
    }

    // Qadratic probing in case of collision
    for (int i = 1; i <= lmv4_capacity+1; i++) {
        codehash = lmv2_capacity + (((codehash-lmv2_capacity) + i + i*i) % lmv4_capacity);
        if(p_space[codehash] == nullptr ){
            return codehash;
        }
        else if(p_space[codehash]->vehicle_number == vnumber){
            return codehash;
        }
    }
    return -1;  // In case no space is available
}



int HMV_hash_function(string vnumber, parking_lot** p_space, int lmv2_capacity, int lmv4_capacity, int hmv_capacity) {
    int nlength = vnumber.length();
    int codehash, vnum_sum = 0;

    for (int i = 0; i < nlength; i++) {
        vnum_sum += static_cast<int>(vnumber[i]);
    }

    codehash = lmv2_capacity + lmv4_capacity + (vnum_sum % hmv_capacity);

    // If the slot is empty or the vehicle number is already parked, return the hashcode
     if(p_space[codehash] == nullptr ){
            return codehash;
        }
        else if(p_space[codehash]->vehicle_number == vnumber){
            return codehash;
        }

    // Quadratic probing in case of collision
    for (int i = 1; i <= hmv_capacity+1; i++) {
        codehash = lmv2_capacity + lmv4_capacity + (((codehash-lmv2_capacity-lmv4_capacity) + i + i*i) % hmv_capacity);
         if(p_space[codehash] == nullptr ){
            return codehash;
        }
        else if(p_space[codehash]->vehicle_number == vnumber){
            return codehash;
        }
    }
    return -1;  // In case no space is available
}



bool search_vehicle_helper(parking_admin* admin, string vnumber, int &hashcode, string &v_type){
        bool found=false;
    for(int i=0; i<1; i++){
    if(admin->LMV2_wheeler_capacity>0){
    hashcode = LMV2W_hash_function(vnumber, admin->parking_space, admin->LMV2_wheeler_capacity);
    if(hashcode==-1){
    }
    else if(admin->parking_space[hashcode]==nullptr){
    }
    else if(admin->parking_space[hashcode]->vehicle_number==vnumber){
    found=true;
    v_type = "2-wheeler";
    break;
    }
    }

    if(admin->LMV4_wheeler_capacity>0){
    hashcode = LMV4W_hash_function(vnumber, admin->parking_space, admin->LMV2_wheeler_capacity, admin->LMV4_wheeler_capacity);
    if(hashcode==-1){
    }
    else if(admin->parking_space[hashcode]==nullptr){
    }
    else if(admin->parking_space[hashcode]->vehicle_number==vnumber){
    found=true;
    v_type = "4-wheeler";
    break;
    }
    }

    if(admin->HMV_capacity>0){
    hashcode = HMV_hash_function(vnumber, admin->parking_space, admin->LMV2_wheeler_capacity, admin->LMV4_wheeler_capacity, admin->HMV_capacity);
    if(hashcode==-1){
    }
    else if(admin->parking_space[hashcode]==nullptr){
    }
    else if(admin->parking_space[hashcode]->vehicle_number==vnumber){
    found=true;
    v_type = "heavy motor vehicle";
    break;
    }
    }
    }
    return found;
}



bool validate_vehicle_number(string vnumber){
    if(vnumber.length() != 10){
        cout<<endl<<"Invalid length! Please enter a valid vehicle number.";
        return false;
    }
    if (!isalpha(vnumber[0]) || !isalpha(vnumber[1])||!isalpha(vnumber[4]) || !isalpha(vnumber[5])) {
        cout<<endl<<"Invalid vehicle number! Please enter a valid number.";
        return false;
    }
    if(islower(vnumber[0])||islower(vnumber[1])||islower(vnumber[4])||islower(vnumber[5])){
        cout<<endl<<"Invalid vehicle number! All the characters should be in capital letters.";
        return false;
    }
    if(!isdigit(vnumber[2]) || !isdigit(vnumber[3])||!isdigit(vnumber[6]) || !isdigit(vnumber[7])||!isdigit(vnumber[8]) || !isdigit(vnumber[9])) {
        cout<<endl<<"Invalid vehicle number! Please enter a valid number.";
        return false;
    }
    return true;
}




void add_slip_to_file(parking_admin* admin, parking_lot* slip, int hashcode, double price_paid) {
    ofstream file;
    file.open(admin->username+".txt", ios::app);  

    if (!file) {
        cerr << "The slips not !" << endl;
        return;
    }

    file<<"\n--------------------------------------------------------------------------\n";
    file<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
    file<<"\t\t\t"<<admin->pcompany_name<<" - Parking Ticket"<<endl;
    file<<"Vehicle Number --> "<<slip->vehicle_number<<endl;
    file<<"Slip Generated for --> "<<slip->owner<<endl;
    file<<"Time allotted --> "<<slip->hours<<" Hours"<<endl<<endl;
    file<<"Parking lot allotted in "<<slip->type<<" parking is "<<hashcode + 1<<endl;
    file<<"Price paid = " << price_paid << " Rupees \n";
    file<<"OTP Generated-> " << slip->otp << "\n";
    file<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
    file<<"--------------------------------------------------------------------------\n";
    file<<endl;
    file.close();
}




void park_vehicle(parking_admin* admin) {
    string in_vehicle_number, in_type, name;
    int vehicle_type, hashcode, in_hours;
    float price_paid;

    bool condi = false;
    for(int i=0; i<3; i++){
    cout<<endl<<"Enter the vehicle number of vehicle to be parked : ";
    cin>>in_vehicle_number;
    if(validate_vehicle_number(in_vehicle_number)){
        condi = true;
        break;
    }
    }
    if(condi==false){
        return;
    }
    
    bool found=false;
    found = search_vehicle_helper(admin, in_vehicle_number, hashcode, in_type);
    if(found==true){
    cout<<endl<<"The vehicle with number "<<in_vehicle_number<<" is already parked in the parking space.";
	return;
    }
    waiting_parking_lot* temp = admin->waiting_list;
        while(temp!=NULL){
            if(temp->vehicle_number==in_vehicle_number){
                cout<<endl<<"The vehicle with entered number already exists in waiting list. ";
                cout<<endl<<"Parking lot will be alloted as soon space frees up, wait for your turn."<<endl;
                return;
            }
            temp = temp->next;
        }

    cout<<endl<<"Enter name of the vehicle owner : ";
    cin>>name;

    in_hours = price_setter("Enter the hours for which you want to park the vehicle : ");

    while(1) {
        cout<<endl<<"Select the type of vehicle to be parked :\nEnter '1' for 2 wheeler,\nEnter '2' for 4 wheeler,\nEnter '3' for heavy motor vehicles,\nYOUR CHOICE : ";
        cin>>vehicle_type;
        if(vehicle_type == 1) {
            in_type = "2-WHEELER";
            if(admin->LMV2_wheeler_capacity == 0) {
                cout << endl << "No space available to park the " << in_type << " vehicles.";
                return;
            }
            hashcode = LMV2W_hash_function(in_vehicle_number, admin->parking_space, admin->LMV2_wheeler_capacity);
            price_paid = in_hours * admin->LMV2_wheeler_price;
            break;
        }
        if (vehicle_type == 2) {
            in_type = "4-WHEELER";
            if (admin->LMV4_wheeler_capacity == 0) {
                cout << endl << "No space available to park the " << in_type << " vehicles.";
                return;
            }
            hashcode = LMV4W_hash_function(in_vehicle_number, admin->parking_space, admin->LMV2_wheeler_capacity, admin->LMV4_wheeler_capacity);
            price_paid = in_hours * admin->LMV4_wheeler_price;
            break;
        }
        if (vehicle_type == 3) {
            in_type = "HMV";
            if (admin->HMV_capacity == 0) {
                cout<<endl<<"No space available to park the "<<in_type<<" vehicles.";
                return;
            }
            hashcode = HMV_hash_function(in_vehicle_number, admin->parking_space, admin->LMV2_wheeler_capacity, admin->LMV4_wheeler_capacity, admin->HMV_capacity);
            price_paid = in_hours * admin->HMV_price;
            break;
        }
        else {
            cout<<endl<<"Invalid choice, select a valid type.";
            continue;
        }
    }
	cout<<endl<<"( Hashcode generated : "<<hashcode<<" )";
    if (hashcode == -1){
        char choice;
        cout<<endl<<"No space available in the "<<in_type<< " parking lot!";
        while(1){
        cout<<endl<<"Enter 'Y' if you want to stay in waiting list, else Enter 'N' : ";
        cin>>choice; 
        if(choice=='N'){
	    return;
        }
        else if(choice=='Y'){
        waiting_parking_lot* temp = admin->waiting_list;
        while(temp!=NULL){
            if(temp->vehicle_number==in_vehicle_number){
                cout<<endl<<"The vehicle with entered number already exists in waiting list. ";
                cout<<endl<<"Parking lot will be alloted as soon space frees up, wait for your turn."<<endl;
                return;
            }
            temp = temp->next;
        }
        
        waiting_parking_lot* slip = new waiting_parking_lot;
        slip->vehicle_number = in_vehicle_number;
        slip->owner = name;
        slip->hours = in_hours;
        slip->type = in_type;
        slip->next = NULL;
        if(admin->waiting_list == NULL) {
        admin->waiting_list = slip;
        cout<<endl<<"ENTRY CONFIRMED FOR WAITING LIST!!!\nThe lot will be assigned automatically and the slip will be generated when the space becomes free.  \n-----------------------------------------------------------\n";
        return;
        }
        else{
            waiting_parking_lot* temp = admin->waiting_list;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = slip;
            cout<<endl<<"ENTRY CONFIRMED FOR WAITING LIST!!!\nThe lot will be assigned automatically and the slip will be generated when the space becomes free.  \n-----------------------------------------------------------\n";
            return;
        }
        }
        else {
            cout<<endl<<"Invalid Choice!!!! Please enter either 'Y' or 'N'.";
            continue;
        } 
        }
	}
    else if(admin->parking_space[hashcode] == nullptr) {
        parking_lot* slip = new parking_lot;
        slip->vehicle_number = in_vehicle_number;
        slip->owner = name;
        slip->hours = in_hours;
        slip->type = in_type;
        slip->otp = rand() % 9000 + 1000; 
        admin->parking_space[hashcode] = slip;
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
        
        cout<<"\n-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\t\t\t"<<admin->pcompany_name<<" - Parking Ticket"<<"\nVehicle Number --> "<<slip->vehicle_number<<"\nSlip Generated for --> "<<slip->owner<<"\nTime alloted --> "<<slip->hours<<" Hours\n\nParking lot alloted in "<<slip->type<<" parking is "<<hashcode+1<<"\nPrice paid = "<<price_paid<<" Rupees \nOTP Generated-> "<<slip->otp<<"\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<"\n-----------------------------------------------------------";

        add_slip_to_file(admin, slip, hashcode, price_paid);
    }
    }



void park_from_waiting_list(parking_admin* admin, waiting_parking_lot* waiting_vehicle){
    int hashcode;
    float price_paid;
    if(waiting_vehicle->type == "2-WHEELER") {
            hashcode = LMV2W_hash_function(waiting_vehicle->vehicle_number, admin->parking_space, admin->LMV2_wheeler_capacity);
            price_paid = waiting_vehicle->hours * admin->LMV2_wheeler_price;
        }
    if (waiting_vehicle->type == "4-WHEELER") {
            hashcode = LMV4W_hash_function(waiting_vehicle->vehicle_number, admin->parking_space, admin->LMV2_wheeler_capacity, admin->LMV4_wheeler_capacity);
            price_paid = waiting_vehicle->hours * admin->LMV4_wheeler_price;
        }
    if (waiting_vehicle->type == "HMV") {
            hashcode = HMV_hash_function(waiting_vehicle->vehicle_number, admin->parking_space, admin->LMV2_wheeler_capacity, admin->LMV4_wheeler_capacity, admin->HMV_capacity);
            price_paid = waiting_vehicle->hours * admin->HMV_price;
        }
    
    if(hashcode!=-1 && admin->parking_space[hashcode] == nullptr) {
        parking_lot* slip = new parking_lot;
        slip->vehicle_number = waiting_vehicle->vehicle_number;
        slip->owner = waiting_vehicle->owner;
        slip->hours = waiting_vehicle->hours;
        slip->type = waiting_vehicle->type;
        slip->otp = rand() % 9000 + 1000; 
        admin->parking_space[hashcode] = slip;
        admin->revenue = admin->revenue + price_paid ;
        if(waiting_vehicle->type == "2-WHEELER"){
            admin->total_2wheeler_slips++;
        }
        if(waiting_vehicle->type == "4-WHEELER"){
            admin->total_4wheeler_slips++;
        }
        if(waiting_vehicle->type == "HMV"){
            admin->total_hmv_slips++;
        }

    if(admin->waiting_list == waiting_vehicle) {
        waiting_parking_lot* temp = waiting_vehicle;
        admin->waiting_list = admin->waiting_list->next;  
        delete temp; 
    }

    
    waiting_parking_lot* temp = admin->waiting_list;
    while(temp != NULL && temp->next != waiting_vehicle) {
        temp = temp->next;  
    }

    // If the node to delete was found
    if(temp != NULL && temp->next == waiting_vehicle) {
        temp->next = waiting_vehicle->next;  // Unlink the node
        delete waiting_vehicle;  // Free memory of the node
    }
        
    cout<<endl<<"Automatically alloting slot from the waiting list."<<endl;
    cout<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\t\t\t"<<admin->pcompany_name<<" - Parking Ticket"<<"\nVehicle Number --> "<<slip->vehicle_number<<"\nSlip Generated for --> "<<slip->owner<<"\nTime alloted --> "<<slip->hours<<" Hours\n\nParking lot alloted in "<<slip->type<<" parking is "<<hashcode+1<<"\nPrice paid = "<<price_paid<<" Rupees \nOTP Generated-> "<<slip->otp<<"\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<"\n-----------------------------------------------------------";
    add_slip_to_file(admin, slip, hashcode, price_paid);
    }
        
}



void free_parkinglot(parking_admin* admin){
    string vnumber, v_type;
    int hashcode, in_otp;
    bool condi = false;
    
    bool yup = false ;
    for(int i=0; i<3; i++){
    cout<<endl<<"Enter the vehicle number to be displaced from parking lot : ";
    cin>>vnumber;
    if(validate_vehicle_number(vnumber)){
        yup = true;
        break;
    }
    }
    if(yup==false){
        return;
    }
    
    for(int i=0; i<1; i++){

    if(admin->LMV2_wheeler_capacity>0){
    hashcode = LMV2W_hash_function(vnumber, admin->parking_space, admin->LMV2_wheeler_capacity);
    if(hashcode==-1){
    }
    else if(admin->parking_space[hashcode]==nullptr){
    }
    else if(admin->parking_space[hashcode]->vehicle_number==vnumber){
    condi=true;
    v_type = "2-WHEELER";
    break;
    }
    }

    if(admin->LMV4_wheeler_capacity>0){
    hashcode = LMV4W_hash_function(vnumber, admin->parking_space, admin->LMV2_wheeler_capacity, admin->LMV4_wheeler_capacity);
    if(hashcode==-1){
    }
    else if(admin->parking_space[hashcode]==nullptr){
    }
    else if(admin->parking_space[hashcode]->vehicle_number==vnumber){
    condi=true;
    v_type = "4-WHEELER";
    break;
    }
    }

    if(admin->HMV_capacity>0){
    hashcode = HMV_hash_function(vnumber, admin->parking_space, admin->LMV2_wheeler_capacity, admin->LMV4_wheeler_capacity, admin->HMV_capacity);
    if(hashcode==-1){
    }
    else if(admin->parking_space[hashcode]==nullptr){
    }
    else if(admin->parking_space[hashcode]->vehicle_number==vnumber){
    condi=true;
    v_type = "HMV";
    break;
    }
    }
    }

    if(condi==false){
    cout<<endl<<"No vehicle found in the parking space having entered number.";
    return;
    }
    
    else{
    cout<<endl<<"Enter the OTP for removing the vehicle from parking : ";
    cin>>in_otp;
    
    if(admin->parking_space[hashcode]->otp==in_otp){
    cout<<endl<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl<<"The parking slot number "<<hashcode+1<<" is now empty for parking.";
    cout<<endl<<"The OTP matched! The "<<v_type<<" vehicle can be taken out of the parking lot."<<endl<<"Thankyou "<<admin->parking_space[hashcode]->owner<<" for parking with us, visit again!"<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-----------------------------------------------------------";
    delete admin->parking_space[hashcode];
    admin->parking_space[hashcode]=nullptr;

    if(admin->waiting_list==NULL){
    return;
    }
    else{
    waiting_parking_lot* temp = admin->waiting_list;
    bool found=false;
    while(temp != NULL){
        if(temp->type==v_type){
            found=true;
            break;
        }
        temp = temp->next;
    }
    if(found==true){
    park_from_waiting_list(admin, temp) ;
    return;
    }
    }
    }
    else{
    cout<<endl<<"The OTP does not match! Permission to take the vehicle denied.";
    return;
    }
    }
}



bool search_vehicle(parking_admin* admin){
    string vnumber, v_type;
    int hashcode;
    
    while(1){
    cout<<endl<<"Enter the vehicle number to be searched in the parking lot : ";
    cin>>vnumber;
    if(validate_vehicle_number(vnumber)){
        break;
    }
    }
    
    bool found=false;
    found = search_vehicle_helper(admin, vnumber, hashcode, v_type);

    if(found==false){
    cout<<endl<<"No vehicle found in the parking space having entered number.";
    return false;
    }

    else{
    cout<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-----------------------------------------------------------";
    cout<<endl<<"The vehicle found at parking slot -> "<<hashcode+1<<", in the "<<admin->parking_space[hashcode]->type<<" section of parking space."<<endl<<"The vehicle has a total parking time of "<<admin->parking_space[hashcode]->hours<<" hours.";
    cout<<endl<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    return true;
    }
}



void view_slot_details(parking_admin* admin){
    string vnumber, in_type;
    int slot_number, vehicle_type, storer_capacity;
          
    while(1){
    cout<<endl<<"Enter the slot number to see its details in the parking lot : ";
    cin>>slot_number;
    if (slot_number<1||slot_number>admin->total_capacity){
    cout<<endl<<"Invalid or Non-Exisisting slot number, please re-enter a valid slot number.";
    continue;
    }
    break;
    }
    
    slot_number = slot_number-1;
    
    if(admin->parking_space[slot_number]==nullptr){
    cout<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-----------------------------------------------------------";
    cout<<endl<<"No vehicle parked,,, parking slot number "<<slot_number+1<<" is Empty.";
    cout<<endl<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    return;
    }
    else{
    cout<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-----------------------------------------------------------";
    cout<<endl<<"The number of vehicle parked in the parking slot -> "<<slot_number+1<<", in the "<<admin->parking_space[slot_number]->type<<" parking space is --> "<<admin->parking_space[slot_number]->vehicle_number<<endl<<"The name of the vehicle owner is --> "<<admin->parking_space[slot_number]->owner<<endl<<"The vehicle has a total parking time of --> "<<admin->parking_space[slot_number]->hours<<" hours.";
    cout<<endl<<"-----------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    return;
    }
}



void display_revenue_details(parking_admin* admin){
    cout<<endl<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n---------------------------------------------------------------------";
    
    cout<<endl<<"\t\t\tREVENUE GENERATION DETAILS : "<<admin->pcompany_name<<endl<<"The total revenue generated = "<<admin->revenue<<" Rupees. "<<endl<<"The analysis of varying parking spaces and profit : "<<endl<<"Total 2 wheelers parking slips generated --> "<<admin->total_2wheeler_slips<<"\t\tRevenue = "<<admin->total_2wheeler_slips*admin->LMV2_wheeler_price<<" Rupees,,, "<<endl<<"Total 4 wheelers parking slips generated --> "<<admin->total_4wheeler_slips<<"\t\tRevenue = "<<admin->total_4wheeler_slips*admin->LMV4_wheeler_price<<" Rupees,,, "<<endl<<"Total hmv parking slips generated --> "<<admin->total_hmv_slips<<"\t\tRevenue = "<<admin->total_hmv_slips*admin->HMV_price<<" Rupees,,, ";
    
    cout<<endl<<"---------------------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    return;
}




void display_parking_slots(parking_admin* admin){
    parking_lot** storer = admin->parking_space;
    int size = admin->total_capacity ;
    cout<<endl<<"===========================PARKING-SPACE-STATUS============================";
        for(int i=0; i<size; i++){
        cout<<endl<<"___________________________________________________________________________\n||";
        for(int j=0; j<4; j++){
        string printer, start; 
        if(i+j+1<10){
        start = " [  ";
        }
        else if(i+j+1<100){
        start = " [ ";
        }
        else{
        start = " [";
        }
        if(i+j+1>size){
        printer = "                 |";
        }
        else if (storer[i+j]==nullptr){
        printer = start + to_string(i+j+1) + "] AVAILABLE |";
        }
        else {
        printer = start + to_string(i+j+1) + "] OCCUPIED  |";
        }
        cout<<printer;
        }
        
        cout<<"|"<<endl<<"||";
        
        for(int k=0; k<4; k++){
        string printer, vnum;
        if(i+k+1>size){
        printer = "                 |";
        }
        else if(storer[i+k]==nullptr){
        printer = " --------------- |";
        }
        else{
        vnum = storer[i+k]->vehicle_number ;
        printer = " --> " + vnum + "  |";
        }
        cout<<printer;
        }

        cout<<"|"<<endl<<"||";

        for(int l=0; l<4; l++){
        string printer, vnum;
        if(i+l+1>size){
        printer = "                 |";
        }
        else if(i+l<admin->LMV2_wheeler_capacity){
        printer = " -2-WHEELER-LOT- |";
        }
        else if(i+l<admin->LMV4_wheeler_capacity+admin->LMV2_wheeler_capacity){
        printer = " -4-WHEELER-LOT- |";
        }
        else if(i+l<size){
        printer = " --H.M.V.--LOT-- |";
        }
        cout<<printer;
        }
        i=i+3;
        cout<<"|"<<endl<<"```````````````````````````````````````````````````````````````````````````";
    }
    cout<<endl<<"===========================================================================";
}               






void display_waiting_list(parking_admin* admin){
    cout<<endl<<"========================== VEHICLE-WAITING-LIST ==========================="<<endl;
    if(admin->waiting_list==NULL){
        cout<<endl<<"The Waiting List is Empty !!!"<<endl<<"No vehicle in the waiting."<<endl;
    }
    else{
        int i=1;
        waiting_parking_lot* temp = admin->waiting_list ;
        while(temp != NULL){
            cout<<endl<<i<<"--->"<<" VEHICLE NUMBER : "<<temp->vehicle_number<<";  TYPE : "<<temp->type<<endl<<"OWNER'S NAME : "<<temp->owner<<";  PARKING HOURS : "<<temp->hours<<endl;
            cout<<"----------------------------------------------------------------"<<endl;
            temp = temp->next;
        };
    }
    cout<<endl<<"===========================================================================";
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
        cout<<"ENTER 7--> TO DISPLAY THE WAITING LIST FOR PARKING"<<endl;
        cout<<"ENTER 8--> TO EXIT THE MENU"<<endl;
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
                display_parking_slots(user);
                break;
            }

            case 7: {
                display_waiting_list(user);
                break;
            }


            case 8: {
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
        cout<<"ENTER 3--> TO DELETE AN EXISTING PROFILE"<<endl;
        cout<<"ENTER 4--> TO EXIT MENU"<<endl;
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
                delete_an_admin();
                break;
            }

            case 4: {
                condition1 = false;
                break;
            }
            
        }
    }

}









