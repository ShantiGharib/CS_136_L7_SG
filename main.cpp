//Shanti Gharib
//Lab 7


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>


class StudentRecord {

	std::string studentId{"n/a"}, firstName{"n/a"}, lastName{"n/a"};

	size_t unitsTaken{0};
	
	bool active{false}, initialized{false};

public:

	StudentRecord();
	
	StudentRecord(const std::string &newStudentId, const std::string &newFirstName, const std::string &newLastName, const size_t newUnitsTaken);
	
	void SetStudentInfo(const std::string &newStudentId, const std::string &newFirstName, const std::string &newLastName, const size_t newUnitsTaken);

	std::string ToString() const;

	inline const std::string &GetStudentId() const;
	inline const std::string &GetFirstName() const;
	inline const std::string &GetLastName() const;
	inline const size_t GetUnitsTaken() const;
	inline void ArchiveRecord();
	inline bool IsActive() const;
	inline bool IsInitialized() const;

};

class HashTable {
	
private:

	static constexpr const int LIMIT{1000}, OVERFLOW_LIMIT{200}, ORDERS_OF_MAGNITUDE_MAX{3};

	StudentRecord* pHashTable{nullptr}, *pOverflowTable{nullptr};
	int hashMaxSize{LIMIT}, overflowMaxSize{OVERFLOW_LIMIT}, 
		hashUsedSize{0}, overflowUsedSize{0}, magnitudeOrder{0};
	
	bool unsavedRecords{false}, isInitialized{false};
	
	
	bool IsTableBuilt() const;
	
	void LoadRecords();

	void CopyFunction(const HashTable &source);

	bool AllocateMemory(StudentRecord* &pTable, const int size);

	void DeallocateMemory(StudentRecord* &pTable);

	std::string GetStuIdFromUser();

	int HashFunc(const std::string &stuId) const;

	StudentRecord* SearchRecord(const std::string &stuId);

public:

	HashTable();

	HashTable(const HashTable &source);

	void operator=(const HashTable &source);

	~HashTable();

	inline int GetHashSize() const;
	inline int GetHashCapacity() const;
	inline int GetOverflowSize() const;
	inline int GetOverflowCapacity() const;
	
	void BuildHashTable();

	bool InsertElement(const std::string &record);

	void SearchRecordHelper();

	bool ArchiveRecord();

	std::string PrintActiveRecords() const;

	std::string PrintDeletedRecords() const;

	std::string PrintUnprocessedRecords() const;

};


enum class MenuOptions {

	BUILD_HASH_TABLE = 1, SEARCH_TABLE, ARCHIVE_RECORD, 
	PRINT_ACTIVE_RECORDS, PRINT_DELETED_RECORDS, 
	PRINT_UNPROCESSED_RECORDS,
	QUIT,

};


void DisplayMenu();
void HandleDefaultMenuCase();


static const std::string INPUT_FILE{"in_records.txt"};
static const std::string ERROR_FILE{"err_unprocessed.txt"};


int main() {
	

	HashTable hash;

	int option{0};
	
	while (option != static_cast<int>(MenuOptions::QUIT)) {
	
		DisplayMenu();
		
		std::cin >> option;

		std::cout << "\n\n";

		switch (option) {

			case static_cast<int>(MenuOptions::BUILD_HASH_TABLE): {
				
				hash.BuildHashTable();

				break;
			}

			case static_cast<int>(MenuOptions::SEARCH_TABLE): {
				
				hash.SearchRecordHelper();

				break;
			}

			case static_cast<int>(MenuOptions::ARCHIVE_RECORD): {
				
				hash.ArchiveRecord();
			
				break;
			
			}

			case static_cast<int>(MenuOptions::PRINT_ACTIVE_RECORDS): {
				
				std::cout << hash.PrintActiveRecords();

				break;
			
			}

			case static_cast<int>(MenuOptions::PRINT_DELETED_RECORDS): {
		
				std::cout << hash.PrintDeletedRecords();

				break;

			}

			case static_cast<int>(MenuOptions::PRINT_UNPROCESSED_RECORDS): {
		
				std::cout << hash.PrintUnprocessedRecords();

				break;

			}

			case static_cast<int>(MenuOptions::QUIT): {
				
				std::cout << "Program now closed\n\n";
				
				break;
			}

			default: {
			
				HandleDefaultMenuCase();
				
				break;	
			}

		
		}


	
	
	
	}



}



StudentRecord::StudentRecord() {}

StudentRecord::StudentRecord(const std::string &newStudentId, const std::string &newFirstName, const std::string &newLastName, const size_t newUnitsTaken) {
		
		SetStudentInfo(newStudentId, newFirstName, newLastName, newUnitsTaken);
	
	}

void StudentRecord::SetStudentInfo(const std::string &newStudentId, const std::string &newFirstName, const std::string &newLastName, const size_t newUnitsTaken) {
	
		
		studentId = newStudentId;

		firstName = newFirstName;

		lastName = newLastName;

		unitsTaken = newUnitsTaken;

		active = initialized = true;
	
	}

std::string StudentRecord::ToString() const {
	
		std::ostringstream result;

		result << studentId << " " << firstName << " " << lastName << " " << unitsTaken << "\n";

		return result.str();
	
	}

inline const std::string& StudentRecord::GetStudentId() const { 

	return studentId; 

}

inline const std::string& StudentRecord::GetFirstName() const { 

	return firstName;

}

inline const std::string& StudentRecord::GetLastName() const { 

	return lastName;

}

inline const size_t StudentRecord::GetUnitsTaken() const { 

	return unitsTaken; 

}

inline void StudentRecord::ArchiveRecord() { 

	active = false; 

}

inline bool	StudentRecord::IsActive() const { 

	return active; 

}

inline bool	StudentRecord::IsInitialized() const { 

	return initialized; 

}






HashTable::HashTable() {}

void HashTable::CopyFunction(const HashTable &source) {

	DeallocateMemory(pHashTable);
	DeallocateMemory(pOverflowTable);

	if (!AllocateMemory(pHashTable, source.hashMaxSize) || 
		!AllocateMemory(pOverflowTable, source.overflowMaxSize)) {
		
		DeallocateMemory(pHashTable);
		DeallocateMemory(pOverflowTable);

		isInitialized = false;

		std::cout << "Please rebuild the hash table\n\n";

	}

	else {
		
		hashMaxSize = source.hashMaxSize;
		overflowMaxSize = source.overflowMaxSize;
		hashUsedSize = source.hashUsedSize;
		overflowUsedSize = source.overflowUsedSize;
		magnitudeOrder = source.magnitudeOrder;
		unsavedRecords = source.unsavedRecords;
		isInitialized = source.isInitialized;

		for (int i = 0; i < hashMaxSize; ++i) {
		
			pHashTable[i] = source.pHashTable[i];
		
		}

		for (int i = 0; i < overflowUsedSize; ++i) {
		
			pOverflowTable[i] = source.pOverflowTable[i];

		}
	
	}

}

HashTable::HashTable(const HashTable &source) {

	CopyFunction(source);	

}

void HashTable::operator=(const HashTable &source) {

	CopyFunction(source);

}

HashTable::~HashTable() {

	DeallocateMemory(pHashTable);
	DeallocateMemory(pOverflowTable);
	
	pHashTable = pOverflowTable = nullptr;

}

inline int HashTable::GetHashSize() const { 

	return hashUsedSize; 

}

inline int HashTable::GetHashCapacity() const { 

	return hashMaxSize; 

}

inline int HashTable::GetOverflowSize() const { 

	return overflowUsedSize; 

}

inline int HashTable::GetOverflowCapacity() const { 

	return overflowMaxSize; 

}

bool HashTable::IsTableBuilt() const  {
	
	if (!isInitialized) {
		
		std::cout << "Before any other functionality may be used, the hash table must first be built.\nThis message will persist until the aforementioned condition is satisfied\n";
		
	}

	return isInitialized;
	
}

void HashTable::LoadRecords() {
	
	std::ifstream inStream(INPUT_FILE);
	std::ofstream errorStream(ERROR_FILE);

	if (inStream.is_open()) {
		
		std::string record;
			
		while (std::getline(inStream, record)) {
			
			if (!InsertElement(record)) {

				if (errorStream.is_open()) {
				
					errorStream << record << "\n";
				
				}


				else {
				
					unsavedRecords = true;
				
				}

			}
			
		}
		
		if (unsavedRecords) {
				
			std::cout << "The file used to store unprocessed records could not be accessed, rendering some records skipped\n";
			
		}


		inStream.close();

	}

	else {
		
		std::cout << "Could not open input file to load records.\nProgram will close\n";

		exit(EXIT_FAILURE);
		
	}

}

bool HashTable::AllocateMemory(StudentRecord* &pTable, const int size) {
	
	if (pTable == nullptr) {

		try {
	
			pTable = new StudentRecord[size];
	
		}

		catch (std::bad_alloc) {
	
			std::cout << "Could not allocate memory for the hash table\n"
				"Please free up memory and try again\n";
	
		}
	
	}

	else {
	
		std::cout << "Memory must be deleted first before reallocating\n\n";
	
	}
	

	return (pTable != nullptr);

}

void HashTable::DeallocateMemory(StudentRecord* &pTable) {
	
	if (pTable != nullptr) {
	
		delete[] pTable;
	
	}

}

void HashTable::BuildHashTable() {

	if (!isInitialized) {
	
		int orderOfMagntitude{0};
	
		while (orderOfMagntitude <= 0 || orderOfMagntitude > ORDERS_OF_MAGNITUDE_MAX) {
	
			std::cout << "Select the hash table's size\n1. 10\n2. 100\n3. 1000\n\n";

			std::cin >> orderOfMagntitude;

			if (orderOfMagntitude >= 0 && orderOfMagntitude <= ORDERS_OF_MAGNITUDE_MAX) {
		
				magnitudeOrder = orderOfMagntitude;

			}

			else {
			
				HandleDefaultMenuCase();
		
			}
	
		}

		hashMaxSize = static_cast<int>(pow(10, magnitudeOrder));
		overflowMaxSize = static_cast<int>(0.2 * hashMaxSize);

		if (!AllocateMemory(pHashTable, hashMaxSize) || !AllocateMemory(pOverflowTable, overflowMaxSize)) {
	
			DeallocateMemory(pHashTable);
			DeallocateMemory(pOverflowTable);
	
		}

		else {
	
			LoadRecords();

			isInitialized = true;
	
		}

	
	}

	else {
	
		std::cout << "Hash Table is already built. No need to rebuild it\n\n";
	
	}
	
}

int HashTable::HashFunc(const std::string &stuId) const {
	
		//1, 2, |3, 4, 5,| 6, 7, 8, 9
		int sumL{0};

		for (int i = 4, magnitude = 1; i >= 2; --i, magnitude *= 10) {
			
			sumL += (stuId[i] - '0') * magnitude;
			
		}

		int sumR{0};

		for (int i = 8, magnitude = 1; i >= 5; --i, magnitude *= 10) {
			
			sumR += (stuId[i] - '0') * magnitude;

		}

		const int SUM = sumL + sumR;
			
		std::string midSquaredStr;
		
		{		
			int midSquared = SUM * SUM;

			while (midSquared != 0) {
			
				midSquaredStr.push_back('0' + (midSquared % 10));
				midSquared/= 10;
			
			}
		}

		int mid = midSquaredStr.size() / 2;
		int idx = 0;
		for (int i = mid, magnitude = 1; mid - i < magnitudeOrder; --i, magnitude *= 10) {
			
			idx += (midSquaredStr[i] - '0') * magnitude;

		}

		return idx;

}

StudentRecord* HashTable::SearchRecord(const std::string &stuId) {
	
	const int hashIndex = HashFunc(stuId);

	StudentRecord* foundMatch{nullptr};

	if (pHashTable[hashIndex].IsActive() && pHashTable[hashIndex].GetStudentId() == stuId) {
			
		foundMatch = &pHashTable[hashIndex];

	}

	for (int i = 0; !foundMatch && i < overflowUsedSize; ++i) {
			
		if (pOverflowTable[i].IsActive() && pOverflowTable[i].GetStudentId() == stuId) {
					
			foundMatch = &pOverflowTable[i];
				
		}
			
	}

	return foundMatch;
	
}

std::string HashTable::GetStuIdFromUser() {
	
	std::string stuId;
		
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "\nEnter Student Id: \n";
	std::getline(std::cin, stuId);

	return stuId;
	
}

bool HashTable::InsertElement(const std::string &record) {
	
		
		std::istringstream recordStream(record);

		std::string id, firstName, lastName;

		size_t unitsTaken{0};

		recordStream >> id >> firstName >> lastName >> unitsTaken;

		int hashIndex = HashFunc(id);

		bool inserted{true};

		if (!pHashTable[hashIndex].IsActive()) {
				
			pHashTable[hashIndex] = StudentRecord(id, firstName, lastName, unitsTaken);

			++hashUsedSize;
				
		}

		else if (overflowUsedSize < overflowMaxSize) {

			pOverflowTable[overflowUsedSize] = StudentRecord(id, firstName, lastName, unitsTaken);

			++overflowUsedSize;

		}

		else {
		
			inserted = false;
		
		}

		return inserted;
	
	}

void HashTable::SearchRecordHelper() {
			
			if (IsTableBuilt()) {
				
				const std::string stuId = GetStuIdFromUser();

				StudentRecord* record = SearchRecord(stuId);

				if (record == nullptr) {
			
					std::cout << "Record could not be found\n";
			
				}
			
				else {
				
					const int MEMORY_GAP =  record - pHashTable;
					std::cout << "Location: " << ((0 <= MEMORY_GAP && MEMORY_GAP < LIMIT) ? "Hash" : "Overflow") << " Table\n" << record->ToString();
			
				}
			
			}
	
	}

bool HashTable::ArchiveRecord() {
	
		StudentRecord* foundMatch = nullptr;

		if (IsTableBuilt()) {
		
			const std::string stuId = GetStuIdFromUser();

			foundMatch = SearchRecord(stuId);

			if (foundMatch) {
		
				foundMatch->ArchiveRecord();
		
		
			}
		
		}

		return (foundMatch != nullptr);

	}

std::string HashTable::PrintActiveRecords() const {
	
		std::ostringstream result;

		if (IsTableBuilt()) {
		
			for (int i = 0; i < hashMaxSize; ++i) {
		
				if (pHashTable[i].IsActive()) {
			
					result << pHashTable[i].ToString();
			
				}
		
			}
		
		}

		return result.str();

	}

std::string HashTable::PrintDeletedRecords() const {
	
		std::ostringstream result;

		if (IsTableBuilt()) {
		
			for (int i = 0; i < hashMaxSize; ++i) {
		
				if (pHashTable[i].IsInitialized() && !pHashTable[i].IsActive()) {
			
					result << pHashTable[i].ToString();
			
				}
		
			}
		
		}


		return result.str();

	}

std::string HashTable::PrintUnprocessedRecords() const {
	
		std::ostringstream result;

		if (IsTableBuilt() && !unsavedRecords) {
		
			std::ifstream errorStream(ERROR_FILE);
			
			if (errorStream.is_open()) {
				
				std::string record;

				while (std::getline(errorStream, record)) {
				
					result << record << "\n";
				
				}

				errorStream.close();
			
			}
		
		}

		return result.str();
	
	}





void DisplayMenu() {

	std::cout << "\nSelect Option"
		"\n1. Create Hash"
		"\n2. Search Record by ID"
		"\n3. Archive record"
		"\n4. Print active records"
		"\n5. Print deleted records"
		"\n6. Print unprocessed records"
		"\n7. Quit"
		"\n\n";

}

void HandleDefaultMenuCase() {


    std::cout << "\nInvalid option selected\n";
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


}



//Output

//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//2
//
//
//Before any other functionality may be used, the hash table must first be built.
//This message will persist until the aforementioned condition is satisfied
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//3
//
//
//Before any other functionality may be used, the hash table must first be built.
//This message will persist until the aforementioned condition is satisfied
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//4
//
//
//Before any other functionality may be used, the hash table must first be built.
//This message will persist until the aforementioned condition is satisfied
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//5
//
//
//Before any other functionality may be used, the hash table must first be built.
//This message will persist until the aforementioned condition is satisfied
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//6
//
//
//Before any other functionality may be used, the hash table must first be built.
//This message will persist until the aforementioned condition is satisfied
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//7
//
//
//Program now closed



//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//1
//
//
//Select the hash table's size
//1. 10
//2. 100
//3. 1000
//
//2
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//3
//
//
//
//Enter Student Id:
//881234590
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//6
//
//
//881234658 Mary Marcos 25
//881234659 Mary Marcos 25
//881234660 Mary Marcos 25
//881234661 Mary Marcos 25
//881234662 Mary Marcos 25
//881234663 Mary Marcos 25
//881234664 Mary Marcos 25
//881234665 Mary Marcos 25
//881234666 Mary Marcos 25
//881234667 Mary Marcos 25
//881234668 Mary Marcos 25
//881234669 Mary Marcos 25
//881234670 Mary Marcos 25
//881234671 Mary Marcos 25
//881234673 Mary Marcos 25
//881234675 Mary Marcos 25
//881234677 Mary Marcos 25
//881234679 Mary Marcos 25
//881234680 Mary Marcos 25
//881234681 Mary Marcos 25
//881234683 Mary Marcos 25
//881234685 Mary Marcos 25
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//5
//
//
//881234590 Mary Marcos 25
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//4
//
//
//881234631 Mary Marcos 25
//881234611 Mary Marcos 25
//881234612 Mary Marcos 25
//881234676 Mary Marcos 25
//881234593 Mary Marcos 25
//881234594 Mary Marcos 25
//881234610 Mary Marcos 25
//881234674 Mary Marcos 25
//881234591 Mary Marcos 25
//881234592 Mary Marcos 25
//881234649 Mary Marcos 25
//881234629 Mary Marcos 25
//881234609 Mary Marcos 25
//881234647 Mary Marcos 25
//881234627 Mary Marcos 25
//881234607 Mary Marcos 25
//881234608 Mary Marcos 25
//881234672 Mary Marcos 25
//881234645 Mary Marcos 25
//881234625 Mary Marcos 25
//881234605 Mary Marcos 25
//881234606 Mary Marcos 25
//881234643 Mary Marcos 25
//881234623 Mary Marcos 25
//881234624 Mary Marcos 25
//881234604 Mary Marcos 25
//881234621 Mary Marcos 25
//881234622 Mary Marcos 25
//881234602 Mary Marcos 25
//881234603 Mary Marcos 25
//881234688 Mary Marcos 25
//881234689 Mary Marcos 25
//881234641 Mary Marcos 25
//881234600 Mary Marcos 25
//881234601 Mary Marcos 25
//881234686 Mary Marcos 25
//881234687 Mary Marcos 25
//881234639 Mary Marcos 25
//881234619 Mary Marcos 25
//881234620 Mary Marcos 25
//881234684 Mary Marcos 25
//881234637 Mary Marcos 25
//881234617 Mary Marcos 25
//881234618 Mary Marcos 25
//881234598 Mary Marcos 25
//881234599 Mary Marcos 25
//881234635 Mary Marcos 25
//881234615 Mary Marcos 25
//881234616 Mary Marcos 25
//881234596 Mary Marcos 25
//881234597 Mary Marcos 25
//881234682 Mary Marcos 25
//881234633 Mary Marcos 25
//881234613 Mary Marcos 25
//881234614 Mary Marcos 25
//881234678 Mary Marcos 25
//881234595 Mary Marcos 25
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//2
//
//
//
//Enter Student Id:
//881234590
//Record could not be found
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//1
//
//
//Select the hash table's size
//1. 10
//2. 100
//3. 1000
//
//1
//Memory must be deleted first before reallocating
//
//Memory must be deleted first before reallocating
//
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//7
//
//
//Program now closed
//


//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//1
//
//
//Select the hash table's size
//1. 10
//2. 100
//3. 1000
//
//2
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//1
//
//
//Hash Table is already built. No need to rebuild it
//
//
//Select Option
//1. Create Hash
//2. Search Record by ID
//3. Archive record
//4. Print active records
//5. Print deleted records
//6. Print unprocessed records
//7. Quit
//
//7
//
//
//Program now closed
