#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Language selection enum
enum Language { ENGLISH, AFAN_OROMO };

// Patient class
class Patient {
private:
    string id;
    string name;
    int age;

public:
    // Constructor
    Patient(const string& id = "", const string& name = "", int age = 0)
        : id(id), name(name), age(age) {
    }

    // Getters
    string getID() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }

    // Setters for editing
    void setName(const string& newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }

    // Validation method
    bool isValid() const {
        return !id.empty() && !name.empty() && age > 0;
    }

    // Display patient info
    void display(Language lang) const {
        string idLabel = (lang == ENGLISH) ? "ID: " : "Lakka Waraqaa Eenyumaa: ";
        string nameLabel = (lang == ENGLISH) ? "Name: " : "Maqaa: ";
        string ageLabel = (lang == ENGLISH) ? "Age: " : "Umurii: ";
        cout << idLabel << id << ", " << nameLabel << name << ", " << ageLabel << age << endl;
    }
};

// ClinicalSystem class
class ClinicalSystem {
private:
    vector<Patient> patients;
    Language currentLanguage;

    // Clear input buffer
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Get language-specific message
    string getMessage(const string& english, const string& afanOromo) const {
        return (currentLanguage == ENGLISH) ? english : afanOromo;
    }

    // Check for duplicate ID
    bool isDuplicateID(const string& id) const {
        for (const auto& patient : patients) {
            if (patient.getID() == id) {
                return true;
            }
        }
        return false;
    }

    // Find patient index by ID
    int findPatientIndex(const string& id) const {
        for (size_t i = 0; i < patients.size(); ++i) {
            if (patients[i].getID() == id) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    // Constructor
    ClinicalSystem() : currentLanguage(ENGLISH) {}

    // Select language
    bool selectLanguage() {
        int choice;
        cout << getMessage("Select Language:\n1. English\n2. Afan Oromo\n", "Afaan Filadhaa: ") << endl;
        if (cin >> choice) {
            clearInputBuffer();
            if (choice == 1) {
                currentLanguage = ENGLISH;
                return true;
            }
            else if (choice == 2) {
                currentLanguage = AFAN_OROMO;
                return true;
            }
            else {
                cout << getMessage("Invalid choice. Please enter 1 or 2.", "Filannoo Dogoggoraa. 1 ykn 2 Galchaa: ") << endl;
                return false;
            }
        }
        else {
            clearInputBuffer();
            cout << getMessage("Invalid input. Please enter a number.", "Galchii Dogoggoraa. Lakkoofsa Galchaa: ") << endl;
            return false;
        }
    }

    // Add a new patient
    void addPatient() {
        string id, name;
        int age;

        // Input ID
        while (true) {
            cout << getMessage("Enter Patient ID: ", "Lakka Waraqaa Eenyummaa Dhukkubsataa Galchaa: ") << endl;
            cin >> id;
            clearInputBuffer();
            if (id.empty()) {
                cout << getMessage("Patient ID cannot be empty.", "Waraqaan Eenyummaa Duwwaa hin Tahu.") << endl;
                continue;
            }
            if (isDuplicateID(id)) {
                cout << getMessage("Patient ID already exists. Please use a unique ID.", "Lakki Waraqaa Eenyummaa Dhukkubsataa Duraan Jira. Aadda Tahuu Qaba. ") << endl;
                continue;
            }
            break;
        }

        // Input name
        while (true) {
            cout << getMessage("Enter Patient Name: ", "Maqaa Dhukkubsataa Galchaa: ") << endl;
            getline(cin, name);
            if (name.empty()) {
                cout << getMessage("Patient name cannot be empty.", "Maqaan Dhukkubsataa Duwwaa hin Tahu.") << endl;
                continue;
            }
            break;
        }

        // Input age
        while (true) {
            cout << getMessage("Enter Patient Age: ", "Umurii Dhukkubsataa Galchaa: ") << endl;
            if (cin >> age && age > 0) {
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            cout << getMessage("Invalid age. Please enter a positive number.", "Umurii Dogoggoraa. Lakkobsa Posotiivaa Galchaa: ") << endl;
        }

        Patient newPatient(id, name, age);
        if (newPatient.isValid()) {
            patients.push_back(newPatient);
            cout << getMessage("Patient added successfully!", "Dhukkubsataan Milkaa'inaan Dabalameera: ") << endl;
        }
        else {
            cout << getMessage("Failed to add patient due to invalid data.", "Sababa Odeeffannoo Sirrii hin taanen Dhukkubsataan hin Dabalamne.") << endl;
        }
    }

    // Display all patients
    void displayPatients() const {
        if (patients.empty()) {
            cout << getMessage("No patients registered yet.", "Dhukkubsataan Homtuu Hin Galmoofne.") << endl;
            return;
        }
        cout << getMessage("List of Patients:", "Tarreefama Dhukkubsattootaa:") << endl;
        for (const auto& patient : patients) {
            patient.display(currentLanguage);
        }
    }

    // Delete patient by ID
    void deletePatient() {
        string id;
        cout << getMessage("Enter Patient ID to delete: ", "Haquuf, lakka Waraqaa Eenyumaa Galchaa: ") << endl;
        cin >> id;
        clearInputBuffer();

        int index = findPatientIndex(id);
        if (index != -1) {
            patients.erase(patients.begin() + index);
            cout << getMessage("Patient deleted successfully!", "Dhukkubsataan Milkaa'inaan Haqameera!") << endl;
        }
        else {
            cout << getMessage("No patient found with ID: ", "Dhukkbsataan Lakka Kanaa hin Argamne:") << id << endl;
        }
    }

    // Edit patient information
    void editPatient() {
        string id;
        cout << getMessage("Enter Patient ID to edit: ", "Haaromsuuf, Lakka waraqaa Eenyummaa Dhukkubsataa Galchaa: ") << endl;
        cin >> id;
        clearInputBuffer();

        int index = findPatientIndex(id);
        if (index == -1) {
            cout << getMessage("No patient found with ID: ", "Dhukkbsataan Lakka Kanaa hin Argamne:") << id << endl;
            return;
        }

        cout << getMessage("Current patient details:", "Odeeffannoo dhukkubsataa Ammaa: ") << endl;
        patients[index].display(currentLanguage);

        // Edit name
        string name;
        cout << getMessage("Enter new Patient Name (press Enter to keep current): ", "Maqaa Haaraa Dhukkubsataa Galchi(Maqaa Ammaa Tursiisuf ' Enter' Chuqaasi:") << endl;
        getline(cin, name);
        if (!name.empty()) {
            patients[index].setName(name);
        }

        // Edit age
        string ageInput;
        cout << getMessage("Enter new Patient Age (press Enter to keep current): ", "Umurii Haaraa Dhukkubsataa Galchi(Umurii Ammaa Tursiisuf ' Enter' Chuqaasi: ") << endl;
        getline(cin, ageInput);
        if (!ageInput.empty()) {
            int age;
            try {
                age = stoi(ageInput);
                if (age > 0) {
                    patients[index].setAge(age);
                }
                else {
                    cout << getMessage("Invalid age. Keeping current age.", "Umirii Dogoggoraa.Umiriii Ammaa Tursiisi") << endl;
                }
            }
            catch (...) {
                cout << getMessage("Invalid input. Keeping current age.", "Galchii Dogoggoraa. Umurii Ammaa Tursiisi") << endl;
            }
        }

        cout << getMessage("Patient updated successfully!", "Dhukkubsataan Milkaa'inaan Haaromfameera!") << endl;
    }

    // Run the system
    void run() {
        cout << getMessage("Welcome to the Simple Clinical Management System!", "Baga Nagaan Gara Sirna Bulchiinsa Kilinikaa Salphaatti Nagaan Dhuftan!") << endl;

        while (!selectLanguage());

        int choice;
        do {
            cout << "\n" << getMessage("Menu:", "Tarreefama:") << endl;
            cout << "1. " << getMessage("Add Patient", "Dhukkubsataa Dabali") << endl;
            cout << "2. " << getMessage("Display Patients", "Dhukkubsattoota Agarsiisi") << endl;
            cout << "3. " << getMessage("Delete Patient", "Dhukkubsataa Haqi") << endl;
            cout << "4. " << getMessage("Edit Patient", "Dhukkubsataa Haaromsi") << endl;
            cout << "5. " << getMessage("Change Language", "Afaan Jijjiiri") << endl;
            cout << "6. " << getMessage("Exit", "Bahi!") << endl;
            cout << getMessage("Enter your choice: ", "Filanno Keessan Galchaa: ") << endl;

            if (cin >> choice) {
                clearInputBuffer();
                switch (choice) {
                case 1:
                    addPatient();
                    break;
                case 2:
                    displayPatients();
                    break;
                case 3:
                    deletePatient();
                    break;
                case 4:
                    editPatient();
                    break;
                case 5:
                    while (!selectLanguage());
                    break;
                case 6:
                    cout << getMessage("Exiting the system. Goodbye!", "Sirna keessaa Bahaa jirta. Nagaatti!") << endl;
                    break;
                default:
                    cout << getMessage("Invalid choice. Please try again.", "Filanno Dogoggoraa.Maaloo, Irra Deebi'un yaali.") << endl;
                }
            }
            else {
                clearInputBuffer();
                cout << getMessage("Invalid input. Please enter a number.", "Galchii Dogoggoraa.Lakkoofsa Galchaa Maaloo.") << endl;
                choice = 0;
            }
        } while (choice != 6);
    }
};

// Main function
int main() {
    ClinicalSystem system;
    system.run();
    return 0;
}
