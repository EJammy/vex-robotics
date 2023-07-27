# Getting started {#starting}
This is a markdown page for the getting started on code base.

## Basic 
The Lift class represents a lift. Here's an example.

```cpp
Lift mainLift(
    okapi::Motor(4, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    {0, 500, 950}
);

while (true) {
    mainLift.drive(control.R1(), control.R2());
    pros::delay(4);
}
```

Here we use the [Lift](@ref Lift) class to operate in opcontrol. Take a look at the [Lift constructor](@ref Lift::Lift) and the [drive](@ref Lift::drive) function.
