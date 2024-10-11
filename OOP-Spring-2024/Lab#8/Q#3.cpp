#include <iostream>
#include <string>

using namespace std;

class Device 
{
private:
    int device_Id;
    string device_Type;
    bool device_status;

public:
    Device(int device_Id, string device_Type, bool device_status)
    {
        this->device_Id = device_Id;
        this->device_Type = device_Type;
        this->device_status = device_status;
    }

    int getDeviceId() const 
    { 
        return this->device_Id; 
    }
    string getDeviceType() const 
    { 
        return this->device_Type; 
    }
    bool getStatus() const 
    { 
        return this->device_status; 
    }

    void toggleStatus() 
    {
        device_status = !device_status;
    }
    ~Device()
    {
        cout << "Destructor Called" << endl;
    }
};

class SmartHome 
{
private:
    static const int Max = 8;
    Device* devices[Max]; 
    int deviceCount;

public:
    SmartHome()
    {
        deviceCount = 0;
    }

    void addDevice(Device* device) 
    {
        if (deviceCount < Max) 
        {
            devices[deviceCount++] = device;
        }
        else 
        {
            cout << "Cannot add more devices. Limit reached." << endl;
        }
    }

    void removeDevice(int deviceId) 
    {
        for (int i = 0; i < deviceCount; ++i) 
        {
            if (devices[i]->getDeviceId() == deviceId) 
            {
                delete devices[i];
                for (int j = i; j < deviceCount - 1; ++j) 
                {
                    devices[j] = devices[j + 1];
                }
                deviceCount--;
                break;
            }
        }
    }

    void displayDevices() const 
    {
        cout << "Devices in Smart Home System:" << endl;
        for (int i = 0; i < deviceCount; ++i) 
        {
            cout << "Device ID: " << devices[i]->getDeviceId() << ", Type: " << devices[i]->getDeviceType() << ", Status: ";
            if (devices[i]->getStatus()) 
            {
                cout << "On";
            }
            else 
            {
                cout << "Off";
            }
            cout << endl;
        }
    }
    void toggle_status(int deviceId) {
        for (int i = 0; i < deviceCount; ++i) 
        {
            if (devices[i]->getDeviceId() == deviceId) 
            {
                devices[i]->toggleStatus();
                break;
                
            }
            
        }
        
    }
    ~SmartHome()
    {
        cout << "Destructor Called" << endl;
    }
};

int main() 
{
    SmartHome smartHome;

    smartHome.addDevice(new Device(1, "Light", true));
    smartHome.addDevice(new Device(2, "Oven", false));
    smartHome.addDevice(new Device(3, "Washing Machine", true));
    smartHome.addDevice(new Device(4, "Camera", false));

    smartHome.displayDevices();
    cout << "\nEnter Device You want to Toggle: ";
    int m;
    cin >> m;
    cout << "endl";
    smartHome.toggle_status(m);
    smartHome.displayDevices();
    cout << "\nEnter Device number you want to remove from above devices: ";
    int k;
    cin >> k;
    cout << endl;
    smartHome.removeDevice(k);
    smartHome.displayDevices();

    return 0;
}