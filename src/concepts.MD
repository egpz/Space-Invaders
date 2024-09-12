documentation for this project explaining basic programming concepts, cause why not
------------------------------------------------

1. #pragma once
This is a preprocessor directive in C++. It tells the compiler to include this header file only once during compilation, even if it's included multiple times in different files. It's a way to prevent multiple definitions of the same class or functions (which can cause errors).

In simple terms: it's a safety measure to make sure the file is not included more than once.
------------------------------------------------

2. Header Guards and Header Files
 Header file usually ending in .h or .hpp. Header files declare the structure of your class but don’t usually contain the full implementation of the functions (like what those functions actually do). The full implementation is often found in a .cpp(source) file.

Header file: Declares what a class can do (its structure and function prototypes).
Source file (.cpp): Defines how those things happen (actual function implementation).
------------------------------------------------

3. Class
A class is a blueprint for creating objects. It defines what data (variables) and behavior (functions/methods) an object will have. The class "Laser" is a blueprint for creating Laser objects. see below:

class Laser{
    public:
        Laser(Vector2 position, int speed);
        void Update();
        void Draw();

    private:
        Vector2 position;
        int speed;
};

in Laser class:

Data members (aka "member variables") hold information about each object created from the class. For example, each laser has a position and speed.
Methods (aka "member functions") define the behavior or actions the object can perform, like Update() or Draw().
------------------------------------------------

4. Public and Private
Public: Anything declared as public can be accessed by anyone, even outside the class. These are typically methods (functions) you want to call on the object.
Private: Anything declared as private can only be accessed from within the class itself. These are usually variables or helper methods you don’t want outside code to modify directly.
see below:

class Laser{
    public:
        Laser(Vector2 position, int speed);
        void Update();
        void Draw();

    private:
        Vector2 position;
        int speed;
};

Laser(Vector2 position, int speed) and the methods Update() and Draw() are public, so anyone using the Laser class can call these methods.
position and speed are private, so no one outside of the Laser class can directly access or change them.
------------------------------------------------

