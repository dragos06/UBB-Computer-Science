from src.domain.person_domain import PersonDomain
from src.domain.validators import PersonValidator
import random


class PersonService:
    def __init__(self, person_repository, activity_repository, person_validator: PersonValidator):
        self.__person_repository = person_repository
        self.__activity_repository = activity_repository
        self.__person_validator = person_validator

    def add_person(self, person_id: str, name: str, phone_number: str) -> None:
        """
        Add person to repository
        :param person_id: Person's id
        :param name: Person's name
        :param phone_number: Person's phone number
        :raises: DuplicateIDException if person with same ID exists
        """
        person = PersonDomain(person_id, name, phone_number)
        self.__person_validator.validate(person)
        self.__person_repository.store(person)

    def delete_person(self, person_id: str) -> PersonDomain:
        """
        Remove person from repository
        :param person_id: person to remove
        :return: removed person
        :raises: PersonDoesNotExistException if person with given id does not exist
        """
        self.__activity_repository.search_all_activities_for_person_id(person_id)
        return self.__person_repository.delete(person_id)

    def update_person(self, person_id: str, name: str, phone_number: str):
        """
        Update person to repository
        :param person_id: person to update
        :param name: new name
        :param phone_number: new phone number
        :raises: PersonDoesNotExistException if person with given id does not exist
        """
        person = PersonDomain(person_id, name, phone_number)
        self.__person_validator.validate(person)
        self.__person_repository.update(person_id, name, phone_number)

    def get_all_persons(self):
        """
        Gets all persons from repository
        :return: all persons from repository
        """
        return self.__person_repository.get_all()

    def search_person_using_name(self, name):
        return self.__person_repository.search_using_name(name)

    def search_person_using_phone_number(self, phone_number):
        return self.__person_repository.search_using_phone_number(phone_number)

    def length_person_list(self):
        return self.__person_repository.size

    def generate_20_persons(self):
        name_list = ["Andrei", "Elena", "Vlad", "Ioana", "Mihai", "Ana", "Alexandru", "Maria", "Stefan", "Andreea",
                     "Cristian", "Roxana", "Radu", "Laura", "Bogdan", "Diana", "Florin", "Gabriela", "Sorin", "Adriana"]
        for person_id in range(1, 21):
            name = name_list[random.randint(0, 19)]
            phone_number = '07'
            for phone_digit in range(0, 8):
                phone_number += str(random.randint(0, 9))
            self.add_person(str(person_id), name, phone_number)
