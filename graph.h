
Class Interactions:


Current Implementation:
Customer
MovieStore 
	MovieFactories
		ComedyFactory
			Comedy
		DramaFactory
			Drama
		ClassicsFactory
			Classics
File Input Reading Input
1. data4movies.txt - Initialize Map of MovieTypes
2. data4customers.txt - Initialize Hash Map of Customer (ID to name)
3. data4commands.txt - Call relevant functions, create Factories & relevant objects per class
			
Future Implementation:
MediaFactories
	DVDFactories
		DVD
	VideoFactories
		Videos
	MovieFactories
		ComedyFactory
			Comedy
		DramaFactory
			Drama
		ClassicsFactory
			Classics

Class Implementations:
MovieStore
- Hash Map of Customers
- Map of all MovieTypes
- Read in all files (Commands, Customers, Movies)
- Methods for each System Action (overrided in specific subclasses)
	Borrow
	Return
	Inventory
	History
-Static variable count for MovieStock

MovieFactories
- Contains create method for each Factory subclass to be overloaded
- Self-registration method implemented for each Factory subclass

ComedyFactory
- Override create method from MovieFactory
- Self-registration
- Create Comedy class objects

Comedy
- Initializes a Map to keep track of movies
- Reads functions from data4commands.txt




