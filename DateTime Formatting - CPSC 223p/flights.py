import json
import re
import datetime

class Flights:
    def __init__(self, filename):
        self.filename_ = filename
        self.data_ = []
        
        try:
            with open(self.filename_, 'r') as input:
                self.data_ = list(json.load(input))
        except FileNotFoundError:
            print("(╯°□°)╯︵ ┻━┻")
            
    def add_flight(self, origin, destination, flight_number, departure, next_day, arrival):
        if not re.match("[0-9][0-9][0-9][0-9]", departure) or not re.match("[0-9][0-9][0-9][0-9]", arrival):
            return False
        else:
            self.data_.append([origin, destination, flight_number, departure, next_day, arrival])
            with open(self.filename_, 'w') as output:
                json.dump(self.data_, output)
            return True
        
    def get_flights(self):
        flights = []
        for flight in self.data_:
            formatted = []
            formatted.append(flight[0])
            formatted.append(flight[1])
            formatted.append(flight[2])

            

            departure_dt = datetime.datetime.strptime(flight[3], "%H%M")
            depart_hr_str = departure_dt.strftime('%I').lstrip('0')
            depart_min_str = departure_dt.strftime('%M')
            depart_ampm = departure_dt.strftime('%p').lower()
            formatted.append(depart_hr_str + ":" + depart_min_str + depart_ampm)
            
            arrival_dt = datetime.datetime.strptime(flight[5], "%H%M")
            arrive_hr_str = arrival_dt.strftime('%I').lstrip('0')
            arrive_min_str = arrival_dt.strftime('%M')
            arrive_ampm = arrival_dt.strftime('%p').lower()
                
            if flight[4] == 'Y':
                formatted.append("+" + arrive_hr_str + ":" + arrive_min_str + arrive_ampm)
            else:
                formatted.append(arrive_hr_str + ":" + arrive_min_str + arrive_ampm)

            duration_td = arrival_dt - departure_dt
            duration = datetime.datetime.strptime(str(duration_td.seconds // 3600) + str((duration_td.seconds//60) % 60), "%H%M")
            duration_hr_str = duration.strftime('%H').lstrip('0')
            duration_min_str = duration.strftime('%M')
            formatted.append(duration_hr_str + ":" + duration_min_str)

            flights.append(formatted)

        return flights