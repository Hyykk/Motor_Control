# ⚙️Motor_Control

## System Modeling
- Circuit Configuration

  + ![image](https://github.com/Hyykk/Motor_Control/assets/114062987/c76a7a36-172e-4808-b27b-82150e47fce5)
  + ![image](https://github.com/Hyykk/Motor_Control/assets/114062987/bb6f1a23-6821-4654-a3c5-db2d62e775cd)
  + We can find the angle in LS7366 as follows:![image](https://github.com/Hyykk/Motor_Control/assets/114062987/6ce5e6a0-5f81-427c-a869-0d8e9efb4490)


- Electrical Equation

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/f2142b04-853a-4243-b5b8-d731d34d52a4)
- Motion Equation of load system

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/32fe14a7-823e-4106-b301-834d1d4fbbbf)
- Block Diagram

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/8a126dc5-9f46-45c0-ad50-851ddf1e06c4)
- Transfer Function

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/ae4bb6e5-9c9d-4800-8060-d7eeb7e7f035)

## Load Inertia
- Parameters

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/34ac642b-9010-432f-a50d-4902605eab59)

Bar plate : m = 175[g],   L = 300[mm], H = 25[mm]

Circular plate : m = 340[g], R = 50[mm], L = 300[mm]

- Momentum of inertia of Bar plate

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/900013c1-a72e-4651-b2d2-40a1b273c4c2)
- Momentum of inertia of Circular plate

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/79617257-83b6-4046-ae2e-34a709d18ea4)

## Position-Speed-Current Controller Configuration
### Closed Loop Control
To reduce vulnerability to external disturbances and minimize errors, utilizing a feedback structure is effective.
This feedback structure is a closed-loop system, where the output signal directly influences the control operation.
The difference between the input signal and the feedback signal serves as the error control signal.
This signal is transmitted to the controller to decrease the error, ultimately enabling the system's output to reach the desired setpoint.
### Controller
- Cascade

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/c589d592-0640-4713-a0b0-5a7f3e6991c6)
- Current Controller (PI Control)  

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/168691e3-d59b-4604-8dee-afca0e5e946f)
- Speed Controller (PI Control)

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/ecc2cf00-9851-4fce-802c-ab42aeb3d591)
- Position Controller (PD Control)

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/c60dcd90-945e-4ca9-aa2b-a4af68845d55)

## Result
## Simulation
- Forward Kinematics

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/4f042f05-e3a7-494a-be2d-97770e77242a)
- Inverse Kinematics

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/853fd13e-e16f-49bc-9f62-8be4acfd396f)
## DC Motor
When entering 90deg in ODE,

![image](https://github.com/Hyykk/Motor_Control/assets/114062987/781b76e7-918c-47ed-993d-6f643efaa0b9)

## Environment
### Simulation
- ODE-0.13
- Visual Studio 2017
- Windows 11
### MCU
- Atmega128
- Microchip Studio
### Motor
- Maxon DCX35L Motor
### Communication
The UART communication utilized a circular queue to prevent packet loss.
While in AVR, the data type 'int' has a size of 16 bits, it should be noted that in ODE's cpp, the size of the 'int' data type is 32 bits.
***Therefore, it is essential to use the 'int32' data type in AVR.***

## 👪Collaborator
   <table>
  <tbody>
    <tr>
      <td align="center"><a href="https://github.com/Hyykk"><img src="https://avatars.githubusercontent.com/Hyykk" width="100px;" alt=""/><br /><sub><b> Yoonkyo Hong </b></sub></a><br /></td>
      <td align="center"><a href="https://github.com/dltnasl"><img src="https://avatars.githubusercontent.com/dltnasl" width="100px;" alt=""/><br /><sub><b> Sumin Lee </b></sub></a><br /></td>
  </tbody>
</table>
