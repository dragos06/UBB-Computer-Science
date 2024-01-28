from src.domain.validators import PersonValidator, ActivityValidator
from src.repository.person_repository import PersonMemoryRepository
from src.repository.activity_repository import ActivityMemoryRepository
from src.services.person_service import PersonService
from src.services.activity_service import ActivityService
from src.ui.ui import UI

person_repository = PersonMemoryRepository()
activity_repository = ActivityMemoryRepository()

person_validator = PersonValidator()
activity_validator = ActivityValidator()

person_service = PersonService(person_repository, activity_repository, person_validator)
activity_service = ActivityService(activity_repository, person_repository, activity_validator)

ui = UI(person_service, activity_service)
ui.start()
