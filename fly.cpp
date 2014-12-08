#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "graph.h"
using namespace std;

int main (int argc, char* argv[]) {
   
   string filename;             
   string choice;      
   const int flight_info_per_line = 5;         
   string flight_info[flight_info_per_line];         
   string str_buff; 
   Graph g;              

   //check if command line input is given correctly
   if (argc != 2) {
         cout << "Incorrect format. File was not provided." << endl;
         return 1;
   }
   
   //open and load file specified. If file doesn't exist, prints error and program exits
   istringstream buf(argv[1]);   //create an input string stream
   buf >> filename;              
   ifstream myfile;
   myfile.open(filename.c_str(), ios::in);

   if(!(myfile.is_open())) {
         cout << "File name provided does not exist." << endl;
         return 1;
   }

   //get flight data from each line in file. 
   while (getline(myfile, str_buff)) {
      string s;
      int i = 0;
      istringstream ss;
      ss.str(str_buff);
      while(ss >> s) {
         flight_info[i] = s;
         i++;
      }
      g.add_flight(flight_info, flight_info_per_line);
   }
   
   //ask for user input. check if input matches known cities / correct time and date format
   do {
      cout << "Enter departure city:" << endl;
      getline(cin, choice);
   } while (!(g.set_depart_city(choice)));                      

   do {
      cout << "Enter destination city:" << endl;
      getline(cin, choice);
   } while (!(g.set_destination(choice)));

   do {
      cout << "Enter departure date (DD/MM/YYYY):" << endl;
      getline(cin, choice);
   } while (!(g.set_depart_date(choice)));

   do {
      cout << "Enter earliest acceptable departure time:" << endl;
      getline(cin, choice);
   } while (!(g.set_depart_time(choice)));

   do {
      cout << "Enter return date (DD/MM/YYYY):" << endl;
      getline(cin, choice);
   } while (!(g.set_return_date(choice)));

   do {
      cout << "Enter earliest acceptable return time:" << endl;
      getline(cin, choice);
   } while (!(g.set_return_time(choice)));
      
   while(1) {

      cout << "Prefered flight itinerary (enter the letter):" << endl;
      cout << "• J: Just Get Me There Today" << endl;
      cout << "• F: Fewest Hops" << endl;
      cout << "• S: Shortest Trip" << endl;
      cout << "• C: Cheapest" << endl;
      cout << "• P: Display daily flight schedule" << endl;
      cout << "Enter 'Quit' to exit." << endl;
      cin >> choice;

      if (choice != "J" && choice != "F" && choice != "S" && choice != "C" && choice != "P" && choice != "Quit") {
         cout << "Incorrect Input. ";
      } else {
         if (choice == "J") { 
            cout << "Just Get Me There Today itinerary selected" << endl;
            g.j_itin();
         }  
         if (choice == "F") {
            cout << "Fewest Hops itinerary selected" << endl;
            g.f_itin();
         }  
         if (choice == "S") {
            cout << "Shortest Trip itinerary selected" << endl;
            g.s_itin();
         }
         if (choice == "C") { 
            cout << "Cheapest itinerary selected" << endl;
            g.c_itin();
         }
         if (choice == "P") { 
            cout << "Printing daily flight schedule..." << endl;
            g.print_flight_sched();
         }
         if (choice == "Quit") break;
      }
   }
   return 1;
}


// #include <string>
// #include <iostream>
// #include <sstream>
// #include <fstream>
// #include "graph.h"
// using namespace std;

// void menu(string &choice, Graph &g){
//    do {
//       cout << "Enter departure city:" << endl;
//       getline(cin, choice);
//    } while (!(g.set_depart_city(choice)));                      

//    do {
//       cout << "Enter destination city:" << endl;
//       getline(cin, choice);
//    } while (!(g.set_destination(choice)));

//    do {
//       cout << "Enter departure date (DD/MM/YYYY):" << endl;
//       getline(cin, choice);
//    } while (!(g.set_depart_date(choice)));

//    do {
//       cout << "Enter earliest acceptable departure time:" << endl;
//       getline(cin, choice);
//    } while (!(g.set_depart_time(choice)));

//    do {
//       cout << "Enter return date (DD/MM/YYYY):" << endl;
//       getline(cin, choice);
//    } while (!(g.set_return_date(choice)));

//    do {
//       cout << "Enter earliest acceptable return time:" << endl;
//       getline(cin, choice);
//    } while (!(g.set_return_time(choice)));
// }

// int main (int argc, char* argv[]) {
   
//    string filename;             
//    string choice;      
//    const int flight_info_per_line = 5;         
//    string flight_info[flight_info_per_line];         
//    string str_buff; 
//    Graph g;              

//    //check if command line input is given correctly
//    if (argc != 2) {
//    	   cout << "Incorrect format. File was not provided." << endl;
//    	   return 1;
//    }
   
//    //open and load file specified. If file doesn't exist, prints error and program exits
//    istringstream buf(argv[1]);   //create an input string stream
//    buf >> filename;              
//    ifstream myfile;
//    myfile.open(filename.c_str(), ios::in);

//    if(!(myfile.is_open())) {
//          cout << "File name provided does not exist." << endl;
//          return 1;
//    }

//    //get flight data from each line in file. 
//    while (getline(myfile, str_buff)) {
//       string s;
//       int i = 0;
//       istringstream ss;
//       ss.str(str_buff);
//       while(ss >> s) {
//          flight_info[i] = s;
//          i++;
//       }
//       g.add_flight(flight_info, flight_info_per_line);
//    }
   
//    //ask for user input. check if input matches known cities / correct time and date format
//    menu(choice, g);
      
//    while(1) {

//       cout << "Prefered flight itinerary (enter the letter):" << endl;
//       cout << "• J: Just Get Me There Today" << endl;
//       cout << "• F: Fewest Hops" << endl;
//       cout << "• S: Shortest Trip" << endl;
//       cout << "• C: Cheapest" << endl;
//       cout << "• P: Display daily flight schedule" << endl;
//       cout << "Enter 'New' to re-enter flight values." << endl;
//       cout << "Enter 'Quit' to exit." << endl;
//       cin >> choice;

//       if (choice != "J" && choice != "F" && choice != "S" && choice != "C" && choice != "P" && choice != "Quit"  && choice != "New") {
// 			cout << "Incorrect Input. ";
// 	   } else {
// 			if (choice == "J") { 
//             cout << "Just Get Me There Today itinerary selected" << endl;
//             g.j_itin();
//          }	
// 			if (choice == "F") {
//             cout << "Fewest Hops itinerary selected" << endl << endl;
//             g.f_itin();
//       	}	
// 	  		if (choice == "S") {
//             cout << "Shortest Trip itinerary selected" << endl;
//             g.s_itin();
// 			}
// 			if (choice == "C") { 
//             cout << "Cheapest itinerary selected" << endl;
//             g.c_itin();
// 			}
//          if (choice == "P") { 
//             cout << "Printing daily flight schedule..." << endl;
//             g.print_flight_sched();
//          }
//          if (choice == "Quit") break;
//          if (choice == "New") {
//             choice == "";
//             menu(choice, g);
//          }
// 		}
//    }
//    return 1;
// }