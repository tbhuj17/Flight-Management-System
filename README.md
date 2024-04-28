Hello Friends, I am Tilak Bhujade. I am implementing **Flight Management Application** using C++. 
This is my project which invloves core concepts of Data Structures and Algorithms, Object Oriented Programming(OOPs). 
The description of project is given below:

In this project, I have implemented a Flight Records Management System that allows admin to
manage and manipulate flight records. The system provides a functionality for inserting, deleting, updating, and
retrieving flight records based on various criteria. I have chosen Linked List as a data structure for this project. You can choose your own.

A Flight Records Management System can be implemented using a data structure, where each element of the
chosen data structure represents a flight record and each record has fields like flight name, flight id, flight capacity,
flight arrival time, flight departure time, flight class (VIP, VVIP, public), and any other field you may want. The
combined pair of flight id and arrival time of the flight can be thought of as a key in the structure and represents a
unique record.The following functions have been implemented in the program:-

-insert
• Inserts (if the entry is not present in the records) or updates an element (if the entry is present in the
records)
• I/p parameters: flight name, flight id, flight capacity, flight arrival time, flight departure time, flight class
(VIP, VVIP, public).
• O/p – Entry should be added/updated appropriately. The return parameter can specify if the insert
operation is successful or not.

-delete
• Deletes an element
• i/p parameters: data structure (of records from which the entry needs to be deleted), flight id of the flight
whose records need to be deleted.
• o/p parameters: To know the operation is successful or not you have to print the appropriate message.

-getNumFlights
• i/p parameters: flight records
• o/p: number of flights in the records.

-isEmpty
• i/p parameters: flight records
• o/p: To know if records are empty or not.

-isFull
• i/p parameters: flight records
• o/p: To know if the records are fully occupied or not.

- geFlightWithtLongeststay
• i/p parameters: flight records
• o/p : flight(s) with max stay time (departure time – arrival time).

- getSortedOnArrivalTime
• i/p parameters: flight records
• o/p parameters : records sorted based on arrival time.

- getSortedOnDepartureTime
• i/p parameters: flight records
• o/p parameters : records sorted based on departure time.

- getSortedOnStayTime
• i/p parameters: flight records
• o/p parameters : records sorted based on stay time (departure time – arrival time).

- ShortestPathCalculator
• i/p paraments: A graph represented as cost adjacency matrix representing distances , source city for the
flight, destination city for the flight
• Output – Shortest distance between source to destination city that the the flight is expected to travel.
