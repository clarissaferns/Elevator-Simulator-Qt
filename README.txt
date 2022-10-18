Team 3 Final Project
----------------------

CES Device Simulator Application

Team Members and Responsibilities
-----------------------------------

- Myron Huang 101140721
    - App Design
    - UI
    - Session Recording feature
    - Programming
    - Use Cases
    - Traceability Matrix
    - Device Configuration Menu features (i.e. Time Scale toggle, recharge battery)
    - Testing and various bug fixes
    - Readme
    
- Clarissa Dayle Fernandes 101131520
    - App Design
    - UI
    - Battery
    - Session Timer
    - Intensity
    - Programming
    - Sequence Diagrams
    
- Bruce Brad Fernandes 101067817
    - App Design
    - Session Class
    - Battery
    - Timer
    - Programming
    - UML
    
- Liam Armes 101012562
    - App Design
    - Device class
    - Programming
    - Traceability Matrix
    - Readme


File Organization
----------------------
Inside the main submission folder (3004FinalProject), there are two sub-directories:
  1. DesignDocuments: This folder contains all design documents for this project. File names reflect their contents.
        
  2. comp3004-team3: this folder contains the project source code
        - images folder for visual assets
        - source files: 
            - session.h/cpp 
            - Device.h/cpp 
            - record.h/cpp 
            - records.h/cpp 
            - main.cpp
            - mainwindow.h/cpp
            - Project.pro
            - resources.qrc

Installation and Setup
----------------------
- Open the comp3004-team3 folder in QT.
- build and run app in QT

Instructions for Use
----------------------

Turn Device On/Off
  1. press the power button.

Run a Therapy Session
  1. Press "Apply to Skin" button to simulate putting on electrodes.
  2. Turn on device.
  3. Select a session group (25 min, 40min or User Designed).
        3a1. If User Designed is selected, a custom time input will appear.
        3a2. Enter a custom time into the time input field.
        3a3. Press "Submit" to confirm custom time entry.
        3a4. The timer will update to show the custom time.
        3a5. continue to Step 4.
  4. Select a session type (Alpha, Beta, Delta or Theta).
  5. Press the Start button (the one labeled with a checkmark button).
  6. Device automatically runs connection test.
        6a1. If connection test gives a "no connection" result, session cannot start.
        6a2. Press the "Appy to Skin" button to simulate taking Electrodes off.
        6a3. Press the "Apply to Skin" button again to simulate putting the Electrodes back on.
        6a4. Press the Start Button again to redo the connection test.
        6a5. If connection test gives a "no connection" result again, repeat Steps 6a1 to 6a4.
        6a6. If connection test gives a medium or strong connection result, continue to step 7.
  7. Intensity indicator shows numerical result of connection test for 2 seconds.
  8. After 2 seconds, the intensity indicator changes to show the current intensity.
  9. Session begins and session timer starts.
 
End a Session
  1. Press "End Session" button to end a session early.
  
Save a Session to Records
  1. After a session ends, Records window displays a message asking the User if they want to save the last session.
  2. Press the "Yes" button under the window to save and "No" to cancel.

Recharge Battery
  1. If there is a currently running session, end the session first then continue to Step 2.
  2. Press "Recharge Battery" button to recharge battery back to 100%.

Change Time Scale
  - By default, the app runs in real time.
  - Real Time: 1 second in app is 1 second in real life.
  - Relative Time: 1 minute in app is 1 second in real life.
  1. If there is a currently running session, end the session first then continue to Step 2.
  2. Use the radio buttons under Time Scale to switch between Real Time and Relative Time.
  
Clear Saved Session Records
  1. Press the "Clear all Records" button.

Tested Scenarios
----------------------

Test: App Builds and Runs in QT.
Result: Passsed

Test: Pressing power button turns the device on and off.
Result: Passed

Test: User can close application by clicking close window button.
Result: Passed

Test: User can run therapy sessions with any group and type selection combination.
Result: Passed

Test: User can end a running session.
Result: Passed

Test: User can choose to record therapy sessions.
Result: Passed

Test: Device battery depletes as a function of session length, intensity and skin contact.
Result: Passed

Test: Connection test runs prior to the start of a session.
Result: Passed

Test: Session dosen't start if there is no electrode connection to the skin.
Result: Passed

Test: Intensity of a session can be adjusted.
Result: Passed

Test: Session timer works.
Result: Passed
