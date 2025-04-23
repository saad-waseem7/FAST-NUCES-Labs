class Train:
    def __init__(self, train_number, train_name, total_seats, fare_per_seat):
        self.train_number = train_number
        self.train_name = train_name
        self.total_seats = total_seats
        self.available_seats = total_seats
        self.fare_per_seat = fare_per_seat
        self.bookings = {}

    def book_ticket(self, passenger_name, num_seats=1):
        if num_seats <= self.available_seats:
            self.available_seats -= num_seats
            if passenger_name in self.bookings:
                self.bookings[passenger_name] += num_seats
            else:
                self.bookings[passenger_name] = num_seats
            print(
                f"Successfully booked {num_seats} ticket(s) for {passenger_name} on {self.train_name} ({self.train_number})."
            )
            return True
        else:
            print(
                f"Sorry, only {self.available_seats} seats are available on {self.train_name} ({self.train_number}). Cannot book {num_seats} tickets."
            )
            return False

    def get_status(self):
        return self.available_seats

    def get_fare(self, num_seats=1):
        return self.fare_per_seat * num_seats


first_Train = Train("12301", "Green Line", 100, 1500.00)
print(
    f"Train Name: {first_Train.train_name}, Number: {first_Train.train_number}, Total Seats: {first_Train.total_seats}, Fare per seat: {first_Train.fare_per_seat}"
)

print(f"Available seats before booking: {first_Train.get_status()}")

first_Train.book_ticket("Saadi", 2)
first_Train.book_ticket("Billy")
first_Train.book_ticket("Abdullah", 3)

print(f"Available seats after booking: {first_Train.get_status()}")

print(f"Fare for 1 ticket on {first_Train.train_name}: {first_Train.get_fare()}")
print(f"Fare for 3 tickets on {first_Train.train_name}: {first_Train.get_fare(3)}")

first_Train.book_ticket("Sami", 96)
