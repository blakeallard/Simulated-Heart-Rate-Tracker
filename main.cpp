/*
* Program: Simulated Heart Rate Tracker
 * Description: This program generates simulated heart rate readings, logs them to a file,
 *              and analyzes the readings to determine if the heart rate is too low, normal, or too high.
 * Author: Blake Allard
 * Date: 2025-02-06
 */

#include <iostream>       /* cout, cin               */
#include <iomanip>        /* formatting output       */
#include <string>         /* string                  */
#include <cstdlib>        /* random number generator */
#include <ctime>          /* seed                    */
#include <fstream>        /* file reading            */
#include <chrono>         /* time functions          */
#include <thread>         /* sleep_for function      */
using namespace std;

// FUNCTION PROTOTYPES - declare prototypes
int GenerateHeartRate();
void LogHeartRate(int bpm, string timestamp);
string AnalyzeHeartRate(int bpm);
string GetCurrentTimestamp();


int main()
{
    // FORMATTING - declare seed for random bpm
    srand(time(0));


    while (true)
    {
        // FUNCTION CALL - PROCESSING - generates a random heart rate between 50 - 120
        int bpm = GenerateHeartRate();

        // FUNCTION CALL - PROCESSING - get current timestamp
        string timestamp = GetCurrentTimestamp();

        // FUNCTION CALL - PROCESSING - writes to heart_rate_log.txt each heartbeat bpm
        LogHeartRate(bpm, timestamp);

        // FUNCTION CALL - OUTPUT - outputs "Low", "High", or "Normal" heart rate analysis
        cout << timestamp << " | Heart Rate: " << bpm << " BPM - " << AnalyzeHeartRate(bpm) << endl;

        // PROCESSING - Delay for 1 second to simulate real-time monitoring
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;

} // end main

/*
 * Function: GenerateHeartRate
 * Description: Simulates a random heart rate between 50 and 120 BPM.
 * Returns: An integer representing the heart rate.
 */

int GenerateHeartRate()
{
    return rand() % 71 + 50; // Random number between 50 and 120
}

/*
 * Function: LogHeartRate
 * Description: Logs the heart rate reading to a file.
 * Parameters: bpm (integer) - The heart rate value.
 */

void LogHeartRate(int bpm, string timestamp)
{
    ofstream file("heart_rate_log.txt", ios::app);
    if (file)
    {
        file << timestamp << " | Heart Rate: " << bpm << "\n";
        file.close();
    }
    else
    {
        cerr << "Error: Unable to open file for logging." << endl;
    }
}

/*
 * Function: AnalyzeHeartRate
 * Description: Determines if the heart rate is low, normal, or high.
 * Parameters: bpm (integer) - The heart rate value.
 * Returns: A string indicating the heart rate condition.
 */

string AnalyzeHeartRate(int bpm)
{
    if (bpm < 60)
    {
        return "Low (Bradycardia)";
    }

    else if (bpm > 100)
    {
        return "High (Tachycardia)";
    }

    else
    {
        return "Normal";
    }
}

string GetCurrentTimestamp()
{
    auto now = chrono::system_clock::now();
    time_t timeNow = chrono::system_clock::to_time_t(now);
    tm *localTime = localtime(&timeNow);

    // Format timestamp as [YYYY-MM-DD HH:MM:SS]
    ostringstream oss;
    oss << "[" << (localTime->tm_year + 1900) << "-"
        << setw(2) << setfill('0') << (localTime->tm_mon + 1) << "-"
        << setw(2) << setfill('0') << localTime->tm_mday << " "
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec << "]";

    return oss.str();
}