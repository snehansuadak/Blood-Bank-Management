BLOOD BANK MANAGEMENT SYSTEM (C++17)

FILES
- main.cpp: menu and program entry point
- Person.h/.cpp: abstract base class
- Donor.h/.cpp and Patient.h/.cpp: derived classes
- BloodUnit.h/.cpp: blood stock record
- Request.h/.cpp: patient blood request
- BloodBank.h/.cpp: business logic and menu operations
- FileManager.h/.cpp: persistence in text files
- Data/: created automatically on first run

VISUAL STUDIO SETUP
1. Create a Console App (C++) project.
2. Set language standard to C++17 or later:
   Project > Properties > C/C++ > Language > C++ Language Standard.
3. Add all .cpp and .h files to the project (Add > Existing Item).
4. Ensure every .cpp file is included in the project and compiled.
5. Build > Build Solution, then Ctrl+F5 to run.

DATA FORMAT
Data files use | as a separator. Do not type | in names/contact fields.
The Data directory is created relative to the program's working directory.

IMPORTANT LIMITATIONS
- This is an educational prototype, not a clinical blood-banking system.
- Request processing currently matches exact blood groups only and is not a
  clinical compatibility decision. Qualified medical staff must verify compatibility.
- Expiry dates are stored but this prototype does not automatically reject expired stock.
- The Update menu supports donor contact, patient contact, and blood stock quantity.
- Text fields containing | are not supported by this simple file format.
- Before real use, add authentication, audit logs, robust input validation,
  secure storage, expiry checking, and clinical review.
