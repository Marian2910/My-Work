from datetime import date, time
from typing import List
import method as method
from Domain.add_operation import AddOperation
from Domain.delete_operation import DeleteOperation
from Domain.delete_operation_loop import DeleteOperationLoop
from Domain.film import Film
from Domain.rezervare import Rezervare
from Domain.rezervare_validator import RezervareValidator
from Domain.update_operation import UpdateOperation
from Repository.repository import Repository
from Service.undo_redo_service import UndoRedoService
from ViewModels.rezervari_in_interval import RezervariInInterval


class RezervareService:
    def __init__(self, rezervare_repository: Repository,
                 rezervare_validator: RezervareValidator,
                 film_repository: Repository,
                 card_client_repository: Repository,
                 undo_redo_service: UndoRedoService):
        self.card_client_repository = card_client_repository
        self.film_repository = film_repository
        self.rezervare_repository = rezervare_repository
        self.rezervare_validator = rezervare_validator
        self.undo_redo_service = undo_redo_service

    def add_rezervare(self, id_rezervare: str, id_film: str,
                      id_card_client: str, data: date, ora: time) -> None:
        """
        adauga o rezervare
        :param id_rezervare:
        :param id_film:
        :param id_card_client:
        :param data:
        :param ora:
        :return:
        """

        rezervare = Rezervare(id_rezervare, id_film, id_card_client, data, ora)
        card_client = self.card_client_repository.read(id_card_client)
        card_client.puncte_acumulate = self.add_points(id_film, id_card_client)
        self.card_client_repository.update(card_client)
        self.rezervare_validator.program_film(id_film)
        self.rezervare_validator.validate(rezervare, id_film, id_card_client)
        self.rezervare_repository.create(rezervare)

        self.undo_redo_service.clear_redo()
        add_operation = AddOperation(self.rezervare_repository, rezervare)
        self.undo_redo_service.add_to_undo(add_operation)

    def update_rezervare(self, id_rezervare: str, id_film: str,
                         id_card_client: str, data: date, ora: time) -> None:
        """
        Modificarea unei rezervari
        :param id_rezervare:
        :param id_film:
        :param id_card_client:
        :param data:
        :param ora:
        :return:
        """
        rezervare_before = self.rezervare_repository.read(id_rezervare)
        rezervare = Rezervare(id_rezervare, id_film, id_card_client, data, ora)
        self.rezervare_validator.validate(rezervare, id_film, id_card_client)
        self.rezervare_repository.update(rezervare)

        self.undo_redo_service.clear_redo()
        updated_operation = UpdateOperation(self.rezervare_repository,
                                            rezervare, rezervare_before)
        self.undo_redo_service.add_to_undo(updated_operation)

    def get_all_rezervare(self) -> List[Rezervare]:
        """
        returneaaza toate cardurile
        :return:
        """
        return self.rezervare_repository.read()

    def delete_rezervare(self, id_rezervare: str) -> None:
        """
        Stergerea unui film
        :param id_rezervare: str
        :return:
        """
        self.rezervare_repository.delete(id_rezervare)

        self.undo_redo_service.clear_redo()
        delete_operation = DeleteOperation(self.rezervare_repository,
                                           self.rezervare_repository.read(id_rezervare))
        self.undo_redo_service.add_to_undo(delete_operation)

    def add_points(self, id_film: str, id_card_client: str) -> int:
        """
        Clientul acumulează pe card 10% (parte întreagă) din prețul filmului.
        :param id_film:
        :param id_card_client:
        :return:
        """
        film = self.film_repository.read(id_film)
        card_client = self.card_client_repository.read(id_card_client)
        puncte = card_client.puncte_acumulate + int(0.1 * film.pret_bilet)
        return puncte

    def search_rezervare(self, string: str):
        """
        cautare full text rezervare
        :param string:
        :return:
        """
        result = []
        rezervari = self.get_all_rezervare()
        search_rezervrare = map(lambda x: {str(x.id_entity), str(x.id_film),
                                           str(x.id_card_client), x.data.strftime("%d.%m.%Y"),
                                           x.ora.strftime("%H.%M")}, rezervari)
        nr = 0
        for rezervare in search_rezervrare:
            nr += 1
            for r in rezervare:
                if r.find(string) != -1:
                    result.append(rezervari[nr - 1])
                    break
        return result

    def search_movie(self, string: str):
        """
        cautare full text filme
        :param string: string-ul cautat
        :return: o lista cu enititatiile care contin parametrul string
        """
        result = []
        filme = self.film_repository.read()
        search_film = map(lambda x: {str(x.id_entity), str(x.titlu),
                                     str(x.an_aparitie), str(x.pret_bilet), str(x.in_program)}, filme)
        nf = 0
        for film in search_film:
            nf += 1
            for f in film:
                if f.find(string) != -1:
                    result.append(filme[nf - 1])
                    break

        for rez in self.search_rezervare(string):
            result.append(rez)

        if not result:
            result.append("Not found!")
        return result

    def search_card(self, string: str):
        """
        cautare full text clienti
        :param string: string-ul cautat
        :return: o lista cu enititatiile care contin parametrul string
        """
        result = []
        card_clienti = self.card_client_repository.read()

        search_card_clienti = map(lambda x: {str(x.id_entity), str(x.nume),
                                             str(x.prenume), str(x.CNP),
                                             x.data_nasterii.strftime("%d.%m.%Y"),
                                             x.data_inregistrarii.strftime("%d.%m.%Y"),
                                             str(x.puncte_acumulate)},
                                  card_clienti)
        lc = 0
        for card_client in search_card_clienti:
            lc += 1
            for c in card_client:
                if c.find(string) != -1:
                    result.append(card_clienti[lc - 1])
                    break

        for rez in self.search_rezervare(string):
            result.append(rez)

        if not result:
            result.append("Not found!")
        return result

    def rezervari_interval_ore(self, ora_start: time, ora_stop: time) -> List[RezervariInInterval]:
        """
        Afișarea tuturor rezervărilor dintr-un interval de ore dat,
         indiferent de zi.
        :param ora_start:
        :param ora_stop:
        :return:
        """
        rezervari = self.get_all_rezervare()
        rezervari_de_determinat = map(lambda rez:
                                      RezervariInInterval(rez.id_entity, rez.id_film,
                                                          rez.id_card_client, rez.ora), rezervari)

        result = [rezervare for rezervare in rezervari_de_determinat
                  if ora_start <= rezervare.ora_rezervare <= ora_stop]
        return result

    def number_of_bookings(self, film: Film) -> int:
        """
        :param film:
        :return: numarul de rezervari ale unui film
        """
        rezervari = self.get_all_rezervare()
        nr = 0
        for i in range(len(rezervari)):
            if film.id_entity == rezervari[i].id_film:
                nr += 1
        return nr

    def number_of_bookings_recursiv(self, film: Film, rez, i) -> int:
        if i == len(rez):
            return 0
        if film.id_entity == rez[i].id_film:
            return 1 + self.number_of_bookings_recursiv(film, rez, i + 1)
        return self.number_of_bookings_recursiv(film, rez, i + 1)

    @staticmethod
    def sorted_method(vector: list, function: method):
        """
        metoda prorpie de sortare
        :param vector: sir
        :param function: method (criteriu de sortare)
        :return:
        """
        for i in range(len(vector) - 1):
            for j in range(i + 1, len(vector)):
                if function(vector[i]) < function(vector[j]):
                    vector[i], vector[j] = vector[j], vector[i]
        return vector

    def ordered_movies_by_number_of_bookings(self) -> List[Film]:
        """
        :return: filmele ordonate dupa nr de rezervari
        """
        filme = self.film_repository.read()
        return self.sorted_method(filme, self.number_of_bookings)

    def stergere_rezervari_interval_zile(self, day_start: date, day_stop: date) -> None:
        """
        stergerea tuturor rezervarilor dintr-ul interval de zile
        :param day_start:
        :param day_stop:
        :return:
        """
        rezervari = self.get_all_rezervare()
        if day_stop < day_start:
            raise ValueError("Date introduse gresit!")

        rezervari_de_sters = [rezervare for rezervare in rezervari
                              if day_start <= rezervare.data <= day_stop]
        for rezervare in rezervari_de_sters:
            self.rezervare_repository.delete(rezervare.id_entity)

        self.undo_redo_service.clear_redo()
        delete_operation = DeleteOperationLoop(self.rezervare_repository,
                                               rezervari_de_sters)
        self.undo_redo_service.add_to_undo(delete_operation)

    def stergere_in_cascada_film(self, id_film_sters: str):
        """
        stergere in cascada
        :param id_film_sters:
        :return: sterge toate rezervarile cu id-ul id_film_sters
        """
        rezervari = self.get_all_rezervare()
        result_list = [rezervare for rezervare in rezervari
                       if rezervare.id_film == id_film_sters]
        for rezervare in result_list:
            self.rezervare_repository.delete(rezervare.id_entity)

        self.undo_redo_service.clear_redo()
        delete_operation = DeleteOperationLoop(self.rezervare_repository,
                                               result_list)
        self.undo_redo_service.add_to_undo(delete_operation)

    def stergere_in_cascada_card_client(self, id_card_sters: str):
        """
        stergere in cascada
        :param id_card_sters:
        :return: sterge toate rezervarile cu id-ul id_card_sters
        """
        rezervari = self.get_all_rezervare()
        result_list = [rezervare for rezervare in rezervari
                       if rezervare.id_card_client == id_card_sters]
        for rezervare in result_list:
            self.rezervare_repository.delete(rezervare.id_entity)

        self.undo_redo_service.clear_redo()
        delete_operation = DeleteOperationLoop(self.rezervare_repository,
                                               result_list)
        self.undo_redo_service.add_to_undo(delete_operation)
