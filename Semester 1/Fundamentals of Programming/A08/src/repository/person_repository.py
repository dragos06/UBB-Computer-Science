from src.domain.person_domain import PersonDomain
from src.repository.repo_exceptions import DuplicateIDException, PersonDoesNotExistException


class PersonMemoryRepository:
    def __init__(self):
        self.__persons = {}

    def store(self, person: PersonDomain) -> None:
        """
        Store person to repository
        :param person: person to add
        :raises: DuplicateIDException if person with same ID exists
        """
        if person.person_id in self.__persons:
            raise DuplicateIDException()
        self.__persons[person.person_id] = person

    def get(self, person_id: str) -> PersonDomain:
        """
        Gets person from repository
        :param person_id: person to get
        :return: Person with given person_id
        :raises: PersonDoesNotExistException if person with given id does not exist
        """
        if person_id in self.__persons:
            return self.__persons[person_id]
        raise PersonDoesNotExistException()

    def delete(self, person_id: str) -> PersonDomain:
        """
        Remove person from repository
        :param person_id: person to remove
        :return: removed person
        :raises: PersonDoesNotExistException if person with given id does not exist
        """
        if person_id not in self.__persons:
            raise PersonDoesNotExistException()
        deleted_person = self.__persons[person_id]
        del self.__persons[person_id]
        return deleted_person

    def update(self, person_id: str, name: str, phone_number: str) -> None:
        """
        Update person to repository
        :param person_id: person to update
        :param name: new name
        :param phone_number: new phone number
        :raises: PersonDoesNotExistException if person with given id does not exist
        """
        if person_id not in self.__persons:
            raise PersonDoesNotExistException
        person = self.get(person_id)
        person.name = name
        person.phone_number = phone_number
        self.__persons[person_id] = person

    def get_all(self) -> list:
        """
        Gets all persons from repository
        :return: all persons from repository
        """
        return list(self.__persons.values())

    def search_using_name(self, name):
        searched_persons = []
        for person in self.get_all():
            if name.lower().strip() in person.name.lower().strip():
                searched_persons.append(person)
        if searched_persons:
            return searched_persons
        else:
            raise PersonDoesNotExistException

    def search_using_phone_number(self, phone_number):
        searched_persons = []
        for person in self.get_all():
            if phone_number.lower().strip() in person.phone_number.lower().strip():
                searched_persons.append(person)
        if searched_persons:
            return searched_persons
        else:
            raise PersonDoesNotExistException

    @property
    def size(self):
        return len(self.get_all())
