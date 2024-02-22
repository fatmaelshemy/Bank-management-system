#pragma once

#include <string>
using namespace std;
class Customer
{
private:
    string name;
    int WaitingTime;
    int ServiceTime;
    int ArrivalTime, LeaveTime;
    bool hasVIP = false;

public:


    Customer(string name, int arrivalTime, int serviceTime)
    {
        this->name = name;
        this->ArrivalTime = arrivalTime;
        this->ServiceTime = serviceTime;

    }

    Customer(string name, int arrivalTime, int serviceTime, bool vip)
    {
        this->name = name;
        this->ArrivalTime = arrivalTime;
        this->ServiceTime = serviceTime;
        this->hasVIP = vip;

    }

    void setName(string newName) {
        name = newName;
    }

    void setWaitingTime(int newWaitingTime) {
        WaitingTime = newWaitingTime;
    }

    void setServiceTime(int newServiceTime) {
        ServiceTime = newServiceTime;
    }

    void setArrivalTime(int newArrivalTime) {
        ArrivalTime = newArrivalTime;
    }

    void setLeaveTime(int newLeaveTime) {
        LeaveTime = newLeaveTime;
    }

    void setHasVIP(bool newHasVIP) {
        hasVIP = newHasVIP;
    }


    string getName() const {
        return name;
    }

    int getWaitingTime() const {
        return WaitingTime;
    }

    int getServiceTime() const {
        return ServiceTime;
    }

    int getArrivalTime() const {
        return ArrivalTime;
    }

    int getLeaveTime() const {
        return LeaveTime;
    }

    bool getHasVIP() const {
        return hasVIP;
    }



};