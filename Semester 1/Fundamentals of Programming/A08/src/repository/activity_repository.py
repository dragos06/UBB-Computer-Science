from src.domain.activity_domain import ActivityDomain
from src.repository.repo_exceptions import ActivityAlreadyExistsException, ActivityDoesNotExistException, \
    ActivityOverlapException, PersonDoesNotExistException


class ActivityMemoryRepository:

    def __init__(self):
        self.__activities = {}

    def store(self, activity: ActivityDomain) -> None:
        """
        Store activity to repository
        :param activity: activity to add
        :raises: ActivityAlreadyExistsException if activity with same ID exists
        """
        if activity.activity_id in self.__activities:
            raise ActivityAlreadyExistsException
        self.__activities[activity.activity_id] = activity

    def get(self, activity_id: str) -> ActivityDomain:
        """
        Gets activity from repository
        :param activity_id: activity to get
        :return: Activity with given activity_id
        :raises: ActivityDoesNotExistException if activity with given id does not exist
        """
        if activity_id in self.__activities:
            return self.__activities[activity_id]
        raise ActivityDoesNotExistException

    def delete(self, activity_id: str) -> ActivityDomain:
        """
        Remove activity from repository
        :param activity_id: activity to remove
        :return: removed activity
        :raises: ActivityDoesNotExistException if activity with given id does not exist
        """
        if activity_id not in self.__activities:
            raise ActivityDoesNotExistException
        deleted_activity = self.__activities[activity_id]
        del self.__activities[activity_id]
        return deleted_activity

    def update(self, activity_id: str, person_id: list, date: str, time: str, description: str) -> None:
        """
        Update activity to repository
        :param activity_id: activity to update
        :param person_id: new person_id list
        :param date: new date
        :param time: new time
        :param description: new description
        :raises: ActivityDoesNotExistException if activity with given id does not exist
        """
        if activity_id not in self.__activities:
            raise ActivityDoesNotExistException
        activity = self.get(activity_id)
        activity.person_id = person_id[:]
        activity.date = date
        activity.time = time
        activity.description = description
        self.__activities[activity_id] = activity

    def get_all(self) -> list:
        """
        Gets all activities from repository
        :return: all activities from repository
        """
        return list(self.__activities.values())

    def search_using_date(self, date):
        searched_activities = []
        for activity in self.get_all():
            if date.lower().strip() in activity.date.lower().strip():
                searched_activities.append(activity)
        if searched_activities:
            return searched_activities
        else:
            raise ActivityDoesNotExistException

    def search_using_time(self, time):
        searched_activities = []
        for activity in self.get_all():
            if time.lower().strip() in activity.time.lower().strip():
                searched_activities.append(activity)
        if searched_activities:
            return searched_activities
        else:
            raise ActivityDoesNotExistException

    def search_using_description(self, description):
        searched_activities = []
        for activity in self.get_all():
            if description.lower().strip() in activity.description.lower().strip():
                searched_activities.append(activity)
        if searched_activities:
            return searched_activities
        else:
            raise ActivityDoesNotExistException

    def tie_person_to_activity(self, activity_id, person_id):
        if activity_id not in self.__activities:
            raise ActivityDoesNotExistException
        activity = self.get(activity_id)
        for other_activity in self.get_all():
            if person_id in other_activity.person_id:
                if other_activity.date == activity.date and other_activity.time == activity.time:
                    raise ActivityOverlapException
        activity.person_id.append(person_id)
        self.__activities[activity_id] = activity

    def search_all_activities_for_person_id(self, person_id):
        for activity in self.get_all():
            if person_id in activity.person_id:
                self.remove_person_from_activity(activity.activity_id, person_id)

    def remove_person_from_activity(self, activity_id, person_id):
        if activity_id not in self.__activities:
            raise ActivityDoesNotExistException
        if person_id not in self.get(activity_id).person_id:
            raise PersonDoesNotExistException
        activity = self.get(activity_id)
        activity.person_id.remove(person_id)
        self.__activities[activity_id] = activity

    @property
    def size(self):
        return len(self.get_all())
