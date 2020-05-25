#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Task
{
private:
    int timestamp, pages;

public:
    Task(int time = 0);
    int getStamp()
    {
        return timestamp;
    }
    int getPages()
    {
        return pages;
    }
    int waitTime(int currenttime)
    {
        return currenttime - timestamp;
    }
};

Task::Task(int times)
{
    timestamp = times;
    pages = rand() % 20 + 1;
}

class Printer
{
private:
    int pagerate;
    Task currentTask;
    bool work = false;
    int timeRemaining = 0;

public:
    Printer(int ppm) : pagerate(ppm) {}
    void tick();
    bool busy()
    {
        return work;
    }
    void startNext(Task newtask);
};

void Printer::tick()
{
    if (work)
    {
        timeRemaining -= 1;
        if (timeRemaining <= 0)
        {
            work = false;
        }
    }
}
void Printer::startNext(Task newtask)
{
    currentTask = newtask;
    timeRemaining = newtask.getPages() * 60 / pagerate;
    work = true;
}

bool newPrintTask()
{

    int num = rand() % 180 + 1;
    if (num == 1)
        return true;
    else
        return false;
}

void simulation(int numSeconds, int pagesPerMinte)
{
    Printer labprint(pagesPerMinte);
    vector<Task> printQueue;
    vector<int> waitingtimes;
    for (int currentSecond = 0; currentSecond < numSeconds; currentSecond++)
    {
        if (newPrintTask())
        {
            Task task(currentSecond);
            printQueue.insert(printQueue.begin(), task);
        }
        if (!labprint.busy() && !printQueue.empty())
        {
            waitingtimes.push_back(printQueue.back().waitTime(currentSecond));
            //cout << printQueue.back().waitTime(currentSecond) << endl;
            labprint.startNext(printQueue.back());
            printQueue.pop_back();
        }
        labprint.tick();
    }
    int sum = 0;
    for (vector<int>::iterator x1 = waitingtimes.begin(); x1 != waitingtimes.end(); x1++)
    {
        sum += *x1;
    }
    double averageWait = sum / waitingtimes.size();
    cout << averageWait << "    " << printQueue.size() << endl;
}

int main()
{
    unsigned seed;
    seed = time(0);
    srand(seed);
    for (int i = 0; i < 10; i++)
    {
        simulation(3600, 10);
    }
}