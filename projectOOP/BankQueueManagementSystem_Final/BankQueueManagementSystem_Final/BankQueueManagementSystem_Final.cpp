#include <iostream>
#include "WaitingQueue.h"
#include "Bank.h"
using namespace std;
int main()
{
    Bank b1;
    
        int numOfCusromers;
        
        cout << "Enter Number of Customers that You Want to Simulate : ";
        SetColor(13);
        cin >> numOfCusromers;
        for (int i = 0; i < numOfCusromers; i++)
        {
            string name;
            int arrivalTime, serviceTime;
            char vip;
            SetColor(15);
            cout << "Enter Details of Customer " << i + 1 << ":" << endl;
            SetColor(10);
            cout << "Name : ";
            SetColor(7);
            cin >> name;
            SetColor(10);
            cout << "Arrival Time : ";
            SetColor(7);
            cin >> arrivalTime;
            SetColor(10);
            cout << "Service Time : ";
            SetColor(7);
            cin >> serviceTime;
            bool isVIP;
            SetColor(10);
            cout << "Are you Special customer y|n : ";
            SetColor(7);
            cin >> vip;
            if (vip == 'y')
            {
                isVIP = true;
            }
            else {
                isVIP = false;
            }

            Customer customer(name, arrivalTime, serviceTime, isVIP);
            b1.addCustomerToDeque(customer);


        }
        b1.simulate();
    }



