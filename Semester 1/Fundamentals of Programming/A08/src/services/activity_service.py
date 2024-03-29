import random

from src.domain.activity_domain import ActivityDomain
from src.repository.repo_exceptions import PersonDoesNotExistException, \
    ActivityDoesNotExistException
from src.domain.validators import ActivityValidator


class ActivityService:

    def __init__(self, activity_repository, person_repository, activity_validator: ActivityValidator):
        self.__activity_repository = activity_repository
        self.__person_repository = person_repository
        self.__activity_validator = activity_validator

    def add_activity(self, activity_id: str, person_id: list, date: str, time: str, description: str) -> None:
        """
        Adds activity to repository
        :param activity_id: id of given activity
        :param person_id: list of persons participating to activity
        :param date: date of activity
        :param time: time of activity
        :param description: description of activity
        :raises: ActivityAlreadyExistsException if activity with same ID exists
        """
        activity = ActivityDomain(activity_id, person_id, date, time, description)
        self.__activity_validator.validate(activity)
        self.__activity_repository.store(activity)

    def delete_activity(self, activity_id: str) -> ActivityDomain:
        """
        Remove activity from repository
        :param activity_id: activity to remove
        :return: removed activity
        :raises: ActivityDoesNotExistException if activity with given id does not exist
        """
        return self.__activity_repository.delete(activity_id)

    def update_activity(self, activity_id: str, person_id: list, date: str, time: str, description: str) -> None:
        """
        Update activity to repository
        :param activity_id: activity to update
        :param person_id: new person_id list
        :param date: new date
        :param time: new time
        :param description: new description
        :raises: ActivityDoesNotExistException if activity with given id does not exist
        """
        activity = ActivityDomain(activity_id, person_id, date, time, description)
        self.__activity_validator.validate(activity)
        self.__activity_repository.update(activity_id, person_id, date, time, description)

    def get_all_activities(self) -> list:
        """
        Gets all activities from repository
        :return: all activities from repository
        """
        return self.__activity_repository.get_all()

    def search_activity_using_date(self, date):
        return self.__activity_repository.search_using_date(date)

    def search_activity_using_time(self, time):
        return self.__activity_repository.search_using_time(time)

    def search_activity_using_description(self, description):
        return self.__activity_repository.search_using_description(description)

    def length_activity_list(self):
        return self.__activity_repository.size

    def tie_person_to_activity(self, activity_id, person_id):
        try:
            self.__person_repository.get(person_id)
        except KeyError:
            raise PersonDoesNotExistException
        self.__activity_repository.tie_person_to_activity(activity_id, person_id)

    def remove_person_from_activity(self, activity_id, person_id):
        try:
            self.__person_repository.get(person_id)
        except KeyError:
            raise PersonDoesNotExistException
        self.__activity_repository.remove_person_from_activity(activity_id, person_id)

    def statistic_given_date(self, given_date):
        statistic_list = []
        for activity in self.get_all_activities():
            if activity.date == given_date:
                statistic_list.append(activity)
        for i in range(len(statistic_list) - 1):
            for j in range(i + 1, len(statistic_list)):
                if statistic_list[i].time > statistic_list[j].time:
                    statistic_list[i], statistic_list[j] = statistic_list[j], statistic_list[i]
        if statistic_list:
            return statistic_list
        else:
            raise ActivityDoesNotExistException

    def busiest_day(self):
        dates_list = []
        for activity in self.get_all_activities():
            if activity.date not in dates_list:
                dates_list.append(activity.date)
        for i in range(len(dates_list) - 1):
            for j in range(i + 1, len(dates_list)):
                if len(self.search_activity_using_date(dates_list[i])) < len(
                        self.search_activity_using_date(dates_list[j])):
                    dates_list[i], dates_list[j] = dates_list[j], dates_list[i]
        statistic_list = []
        for date in dates_list:
            for activity in self.search_activity_using_date(date):
                statistic_list.append(activity)
        return statistic_list

    def statistic_given_person(self, person_id):
        statistic_list = []
        for activity in self.get_all_activities():
            if person_id in activity.person_id:
                statistic_list.append(activity)
        if statistic_list:
            return statistic_list
        else:
            raise PersonDoesNotExistException

    def generate_20_activities(self):
        description_list = ["Swimming", "Reading", "Writing", "Hiking", "Painting", "Cooking", "Dancing", "Cycling",
                            "Yoga", "Game night", "Volunteering", "Day trip", "Fishing", "Running", "Photography",
                            "Concert", "Skiing", "Coffe", "Book Club", "Gardening"]
        for activity_id in range(1, 21):
            person_id = []
            description = description_list[random.randint(0, 19)]
            while len(person_id) <= 5:
                i = str(random.randint(1, 20))
                if i not in person_id:
                    person_id.append(i)
            date_day = str(random.randint(1, 15))
            if len(date_day) < 2:
                date_day = '0' + date_day
            date_month = str(random.randint(1, 3))
            if len(date_month) < 2:
                date_month = '0' + date_month
            date = date_day + '/' + date_month
            time_hour = str(random.randint(0, 23))
            if len(time_hour) < 2:
                time_hour = '0' + time_hour
            time_minute = str(random.randint(0, 59))
            if len(time_minute) < 2:
                time_minute = '0' + time_minute
            time = time_hour + ":" + time_minute
            self.add_activity(str(activity_id), person_id, date, time, description)
