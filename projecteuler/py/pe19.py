""" projecteuler.net problem 19. Counting Sundays.

You are given the following information, but you may prefer to do some research for yourself.

 * 1 Jan 1900 was a Monday.
 * Thirty days has September,
   April, June and November.
   All the rest have thirty-one,
   Saving February alone,
   Which has twenty-eight, rain or shine.
   And on leap years, twenty-nine.
 * A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
"""

days = []
for year in range(1901, 2001):
    leap_year_day = 0
    if year % 4 == 0:
        leap_year_day = 1

    month_lengths = (
        31,  # January
        28 + leap_year_day,  # February
        31,  # March
        30,  # April
        31,  # May
        30,  # June
        31,  # July
        31,  # August
        30,  # September
        31,  # October
        30,  # November
        31,  # December
    )

    for month_length in month_lengths:
        index = len(days)
        days.extend([False] * month_length)
        days[index] = True

total_sundays = 0
for x in range(0, len(days), 7):
    if days[x]:
        total_sundays += 1

print(total_sundays)
