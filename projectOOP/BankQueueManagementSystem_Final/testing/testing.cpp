#include <iostream>
#include <queue>
#include <vector>
#include <random>

struct Customer {
    std::string name;
    int arrivalTime;
    int serviceTime;
    int waitingTime;
    int leaveTime;
};

struct Teller {
    bool isAvailable;
};

class BankQueueManagementSystem {
private:
    std::queue<Customer> customerQueue;
    std::vector<Teller> tellers;
    std::random_device rd;
    std::mt19937 gen;

public:
    BankQueueManagementSystem(int numTellers) : gen(rd()) {
        tellers.resize(numTellers, { true });
    }

    void enqueueCustomer(const Customer& customer) {
        customerQueue.push(customer);
    }

    void dequeueCustomer() {
        if (customerQueue.empty()) {
            std::cout << "No customers in the queue." << std::endl;
            return;
        }

        Customer customer = customerQueue.front();
        customerQueue.pop();
        Teller* teller = getAvailableTeller();

        if (teller != nullptr) {
            teller->isAvailable = false;
            customer.waitingTime = 0;
            customer.leaveTime = customer.arrivalTime + customer.serviceTime;
        }
        else {
            int waitingTime = customerQueue.size();
            customer.waitingTime = waitingTime;
            customer.leaveTime = customer.arrivalTime + waitingTime + customer.serviceTime;
        }

        std::cout << "Customer " << customer.name << ": Waiting Time = " << customer.waitingTime
            << ", Leave Time = " << customer.leaveTime << std::endl;
    }

    void simulateService() {
        while (!customerQueue.empty()) {
            std::uniform_int_distribution<> dis(0, customerQueue.size() - 1);
            int index = dis(gen);
            dequeueCustomer();
            for (auto& teller : tellers) {
                teller.isAvailable = true;
            }
        }
    }

private:
    Teller* getAvailableTeller() {
        for (auto& teller : tellers) {
            if (teller.isAvailable) {
                return &teller;
            }
        }
        return nullptr;
    }
};

int main() {
    BankQueueManagementSystem bqms(3);

    Customer c1 = { "Ashraf", 35, 62 };
    Customer c2 = { "Leo", 39, 57 };
    Customer c3 = { "Messi", 78, 124 };
    Customer c4 = { "mohammed", 79, 32 };
    Customer c5 = { "mm", 80, 15 };
    Customer c6 = { "dd", 90, 10 };
    Customer c7 = { "ss", 95, 20 };
    Customer c8 = { "gg", 107, 20 };

    bqms.enqueueCustomer(c1);
    bqms.enqueueCustomer(c2);
    bqms.enqueueCustomer(c3);
    bqms.enqueueCustomer(c4);
    bqms.enqueueCustomer(c5);
    bqms.enqueueCustomer(c6);
    bqms.enqueueCustomer(c7);
    bqms.enqueueCustomer(c8);

    bqms.simulateService();

    return 0;
}