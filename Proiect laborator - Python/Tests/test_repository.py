from Domain.film import Film
from Repository.json_repository import RepositoryJson
from utiles import clear_file


def test_repository():
    filename = 'test_film.json'
    clear_file(filename)
    film_repository = RepositoryJson(filename)
    added = Film('123', 'Troy', 1990, 34.99, True)
    film_repository.create(added)
    assert film_repository.read(added.id_entity) == added
