import pandas as pd
import math
import csv

teams_map = {'NCLL SantoriniDave.com' : 'SantoriniDave.com',
             'NCLL Harjo Construction': 'Harjo Construction',
             'NCLL Dynamite': 'TNT Taqueria Dynamite'}

def get_team_name(team_name):
    if team_name in teams_map:
        return teams_map[team_name]
    return team_name

class Event:
    def __init__(self, away_team, home_team, date, start_time, end_time, location, field):
        self.away_team = away_team
        self.home_team = home_team
        self.date = date
        self.start_time = start_time
        self.end_time = end_time
        self.location = location
        self.field = field

def create_csv_from_events(events, filename):
    with open(filename, 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(['Away Team', 'Home Team', 'Date', 'Start Time', 'End Time', 'Location', 'Field'])
        for e in events:
            w.writerow([e.away_team, e.home_team, f'{e.date.month}/{e.date.day}/{e.date.year}', e.start_time.strftime("%H:%M"), e.end_time.strftime("%H:%M"), e.location, e.field])

def split_location_and_field(combined_location):
    location = combined_location.strip()
    field = "1"
    s = combined_location.split('#')
    if len(s) == 2:
        location = s[0].strip()
        field = s[1].strip()
    fields_map = {'West Queen Anne Playfield': 'Queen Anne',
                  'Lawton Park': 'Lawton',
                  'Lower Woodland Playfield': 'Lower Woodland Cloverleaf',
                  'Gilman Playfield': 'Gilman',
                  'Magnolia Playfield': 'Magnolia',
                  'Loyal Heights Playfield': 'Loyal Heights'}
    if location in fields_map:
        location = fields_map[location]
    if location == 'Ballard Community Center' and field == '2':
        field = "2 (West)"
    return (location, "Field " + field)

def get_softball_events(filename):
    df = pd.read_excel(filename)

    events = []
    for row in df.values.tolist():
        if math.isfinite(row[0]):
            away_team = row[6]
            home_team = row[7]
            if away_team in teams_map or home_team in teams_map:
                location, field = split_location_and_field(row[3])
                events.append(Event(get_team_name(away_team),
                       get_team_name(home_team),
                       date = pd.to_datetime(row[2]),
                       start_time = row[4],
                       end_time = row[5],
                       location = location,
                       field = field))
    return events

if __name__ == '__main__':
    events = get_softball_events("../../../NCLL/game schedules/district 8 city softball aaa game schedule - rev a.xlsx")
    create_csv_from_events(events, "softball_aaa_games.csv")
