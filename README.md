# Ride Booking System

A console-based C++ application that simulates a ride-sharing service. This project serves as a demonstration of fundamental and advanced Object-Oriented Programming (OOP) principles.

## 🚀 Features

- **Rider & Driver Management**: Classes to handle user and driver profiles.
- **Dynamic Fare Calculation**: Automated fare estimation based on distance, group size, and taxes.
- **Rating System**: Interactive feedback loop allowing riders to rate drivers.
- **Persistent History**: Ride details are saved to `RideHistory.txt` for future reference.
- **Console Interface**: User-friendly menu for booking rides and viewing history.

## 💻 OOP Concepts Demonstrated

This project showcases the following core Object-Oriented Programming concepts:

1.  **Abstraction**: Used an abstract base class `Person` with a pure virtual function `displayDetails()`.
2.  **Inheritance**: `Rider` and `Driver` classes inherit from the `Person` base class.
3.  **Polymorphism**: Implemented through virtual function overriding in derived classes.
4.  **Encapsulation**: Data members are protected or private, with access provided via public methods.
5.  **Operator Overloading**: Overloaded the `+` operator to calculate the total fare (Base Fare + Distance Fare).
6.  **Friend Functions**: Used a friend function for the `+` operator overload to access private members of the `Ride` class.

## 🛠️ How to Run

### Prerequisites
- A C++ compiler (like GCC/g++) installed on your system.

### Compilation
Open your terminal/command prompt and run:
```bash
g++ "Assignment_OOP (1).cpp" -o RideBookingSystem
```

### Execution
Run the compiled executable:
```bash
./RideBookingSystem
```

## 📁 Project Structure

- `Assignment_OOP (1).cpp`: Main source code file containing all classes and logic.
- `RideHistory.txt`: (Auto-generated) Stores the history of completed rides.

## 📝 License
This project is for educational purposes.
