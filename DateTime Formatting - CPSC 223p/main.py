import flights

flight_list = flights.Flights("flight_info.txt")

while True:
    print(" *** TUFFY TITAN FLIGHT SCHEDULE MAIN MENU ***")
    user_input = input("1. Add flight\n2. Print flight schedule\n3. Set flight schedule filename\n9. Exit the program\n\nEnter menu choice: ")

    if user_input == '1':
        origin = input("Enter origin: ")
        destination = input("Enter destination: ")
        flight_no = input("Enter flight number: ")
        departure = input("Enter departure time: ")
        arrival = input("Enter arrival time: ")
        next_day = input("Is arrival next day: ")
        flight_list.add_flight(origin, destination, flight_no, departure, next_day, arrival)
    elif user_input == '2':
        print("================== FLIGHT SCHEDULE ==================")
        print("Origin Destination Number Departure  Arrival Duration")
        print("====== =========== ====== ========= ======== ========")
        for flight in flight_list.get_flights():
            print('{:<7}'.format(flight[0]) + '{:<12}'.format(flight[1]) + '{:<7}'.format(flight[2]) + '{:<10}'.format(flight[3]) + '{:<9}'.format(flight[4]) + '{:<8}'.format(flight[5]))
    elif user_input == '3':
        flight_list.filename_ = input("Enter file name: ")
    elif user_input == '9':
        break