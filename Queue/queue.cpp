#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enum to represent the state of traffic signal
enum SignalState
{
    RED,
    GREEN
};

class TrafficSimulator
{
private:
    queue<string> waitingCars;
    SignalState signalState;
    int currentTimeStep;

    const int NUM_ITERATIONS = 10; // Number of simulation time steps

public:
    TrafficSimulator() : signalState(RED), currentTimeStep(0) {}

    void simulate()
    {
        srand(time(0));

        for (currentTimeStep = 1; currentTimeStep <= NUM_ITERATIONS; ++currentTimeStep)
        {
            cout << "Time Step " << currentTimeStep << ":" << endl;

            simulateArrival();

            manageSignal();

            passThroughSignal();

            cout << endl;
        }
    }

private:
    void simulateArrival()
    {
        if (rand() % 2 == 1)
        {
            string carName = "Car" + to_string(currentTimeStep);
            cout << carName << " arrives." << endl;
            waitingCars.push(carName);
        }
    }

    void manageSignal()
    {
        if (signalState == RED && !waitingCars.empty())
        {
            cout << "Signal turns GREEN." << endl;
            signalState = GREEN;
        }
        else if (signalState == GREEN && waitingCars.empty())
        {
            cout << "Signal turns RED." << endl;
            signalState = RED;
        }
    }

    void passThroughSignal()
    {
        if (signalState == GREEN && !waitingCars.empty())
        {
            string currentCar = waitingCars.front();
            cout << currentCar << " passes through the signal." << endl;
            waitingCars.pop();
        }
    }
};

int main()
{
    TrafficSimulator simulator;
    simulator.simulate(); // Simulate for predefined number of time steps

    return 0;
}
