
#pragma once
#include <string>
#include "Customer.h"
#include <iostream>
#include <queue>
#include <windows.h>
#include <deque>
using namespace std;

struct compareEventTime {
public:
    bool operator()(const Customer& lhs, const Customer& rhs) const {
        // Compare based on state enum values
        if (lhs.getHasVIP() != rhs.getHasVIP() ){
            return lhs.getHasVIP()  < rhs.getHasVIP();
        }
        else {
           
            return lhs.getArrivalTime() > rhs.getArrivalTime();
        }
    }
};
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
struct teller
{
    bool isAvailable;
    int tellerNumber;
    int numofserved;
    int availableTime;
    int totalTimeServed;
};

class Bank
{
private:
  
    int teller_num = 3;

    deque<Customer> customerDeque;
   
    int currentTime = 0;
    teller* tellers;
    int totalWaitingTime = 0;
    int totalServiceTime = 0;
public:
    Bank()
    {
        tellers = new teller[teller_num];
        for (int i = 0; i < teller_num; ++i)
        {
            tellers[i].isAvailable = true;
            tellers[i].tellerNumber = i + 1;
            tellers[i].numofserved = 0;
            tellers[i].availableTime = 0;
            tellers[i].totalTimeServed = 0;

        }
    }

    ~Bank()
    {
        delete[] tellers;
    }

   

    void addCustomerToDeque(Customer c)
    {
       
        customerDeque.push_back(c);
        sort(customerDeque.begin(), customerDeque.end(), [](const Customer& a, const Customer& b) {
            return a.getArrivalTime() < b.getArrivalTime();
            });
    }
    

    teller* findNearestAvailableTeller()
    {
        teller* nearestTeller = nullptr;
        int earliestAvailableTime = INT_MAX;

        for (int i = 0; i < teller_num; i++)
        {
            if (tellers[i].availableTime < earliestAvailableTime)
            {
                nearestTeller = &tellers[i];
                earliestAvailableTime = tellers[i].availableTime;
            }
        }

        return nearestTeller;
    }
    void displayCustomers(Customer c, teller t)
    {
        
        string type;
        if (c.getHasVIP() == true)
        {
            type = "special";
        }
        else {
            type = "Normal";
        }
        cout << " customer name : "; SetColor(13); 
        cout << c.getName(); SetColor(11);
        cout << " Waiting Time : "; SetColor(13);
        cout << c.getWaitingTime(); SetColor(11);
        cout << " Service Time : "; SetColor(13);
        cout << c.getServiceTime(); SetColor(11);
        cout << " Leave Time : "; SetColor(13); 
        cout << c.getLeaveTime(); SetColor(11);
        cout << " Type: "; SetColor(13); 
        cout << type << endl; SetColor(11);
        cout << " served with teller number : "; SetColor(13);
        cout << t.tellerNumber << endl; SetColor(11);
       
       
    }

    void displayTellers()
    {
        SetColor(11);
        cout << endl;
        cout <<"Tellers Details : " << endl;
        SetColor(13);
        for (int i = 0; i < teller_num; i++)
        {
            cout<<"    Teller Num : " <<tellers[i].tellerNumber 
                << " Total Time served : "  << tellers[i].totalTimeServed
                <<" and he served : " << tellers[i].numofserved <<" customers" 
                << endl;
            
        }
        
    }

    void displayTotal()
    {
        cout << endl;
        SetColor(13);
        cout << "Service and Waiting Details : " << endl;
        SetColor(11);
        cout << "    Total Service Time is : " << totalServiceTime 
             << " and Total Waiting Time is : " << totalWaitingTime << endl;
       

    }
  

   

    void simulate()
    {
        cout << endl;
        SetColor(13);
        cout << "Customers Details : " << endl;
        SetColor(11);
        while (!customerDeque.empty())
        {
            Customer cuurentCustomer = customerDeque.front();
            bool served = false;
            for (int i = 0; i < teller_num; i++)
            {
                if (tellers[i].isAvailable)
                {
                    cuurentCustomer.setWaitingTime(cuurentCustomer.getArrivalTime() - cuurentCustomer.getArrivalTime());
                    cuurentCustomer.setLeaveTime(cuurentCustomer.getArrivalTime() + cuurentCustomer.getServiceTime());
                    displayCustomers(cuurentCustomer, tellers[i]);
                    tellers[i].isAvailable = false;
                    tellers[i].availableTime = cuurentCustomer.getLeaveTime();
                    tellers[i].numofserved++;
                    tellers[i].totalTimeServed += cuurentCustomer.getServiceTime();
                    totalServiceTime += cuurentCustomer.getServiceTime();
                    totalWaitingTime += cuurentCustomer.getWaitingTime();
                    customerDeque.pop_front();
                    served = true;
                    break;
                }
            }

            if (!served)
            {
                teller* nearestTeller = findNearestAvailableTeller();

                bool vipServed = false;
                int indexToRemove = customerDeque.size();  

                for (int i = 0; i < customerDeque.size() && customerDeque[i].getArrivalTime() <= nearestTeller->availableTime; i++)
                {
                    if (customerDeque[i].getHasVIP())
                    {
                        cuurentCustomer = customerDeque[i];
                        nearestTeller->isAvailable = true;
                        nearestTeller->numofserved++;
                        if (nearestTeller->availableTime < cuurentCustomer.getArrivalTime())
                        {
                            cuurentCustomer.setWaitingTime(0);
                        }
                        else {
                            cuurentCustomer.setWaitingTime(nearestTeller->availableTime - cuurentCustomer.getArrivalTime());

                        }
                        cuurentCustomer.setLeaveTime(cuurentCustomer.getArrivalTime() + cuurentCustomer.getWaitingTime() + cuurentCustomer.getServiceTime());
                        displayCustomers(cuurentCustomer, *nearestTeller);
                        totalServiceTime += cuurentCustomer.getServiceTime();
                        totalWaitingTime += cuurentCustomer.getWaitingTime();
                        nearestTeller->totalTimeServed += cuurentCustomer.getServiceTime();
                        nearestTeller->availableTime = cuurentCustomer.getLeaveTime();
                        nearestTeller->isAvailable = false;

                        // Store the index to remove after the loop
                        indexToRemove = i;
                        vipServed = true;
                        break;
                    }
                }

                // Delete the current customer after the loop
                if (vipServed && indexToRemove != customerDeque.size())
                {
                    customerDeque.erase(customerDeque.begin() + indexToRemove);
                }

                if (!vipServed)
                {
                    nearestTeller->isAvailable = true;
                    nearestTeller->numofserved++;
                    if (nearestTeller->availableTime < cuurentCustomer.getArrivalTime())
                    {
                        cuurentCustomer.setWaitingTime(0);
                    }
                    else {
                        cuurentCustomer.setWaitingTime(nearestTeller->availableTime - cuurentCustomer.getArrivalTime());

                    }
                    // cuurentCustomer.setWaitingTime(nearestTeller->availableTime - cuurentCustomer.getArrivalTime());
                    cuurentCustomer.setLeaveTime(cuurentCustomer.getArrivalTime() + cuurentCustomer.getWaitingTime() + cuurentCustomer.getServiceTime());
                    displayCustomers(cuurentCustomer, *nearestTeller);
                    totalServiceTime += cuurentCustomer.getServiceTime();
                    totalWaitingTime += cuurentCustomer.getWaitingTime();
                    nearestTeller->totalTimeServed += cuurentCustomer.getServiceTime();
                    nearestTeller->availableTime = cuurentCustomer.getLeaveTime();
                    nearestTeller->isAvailable = false;
                    customerDeque.pop_front();
                }




            }
        }
        displayTellers();
        displayTotal();
    }

};



