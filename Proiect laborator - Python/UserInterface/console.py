from datetime import datetime
from Domain.card_client_validator import CardValdiationError
from Domain.film_validator import FilmValidationError
from Domain.rezervare_validator import RezervareValidationError
from Repository.exceptions import NoSuchIdError, DuplicateIdError
from Service.card_client_service import CardClientService
from Service.film_service import FilmService
from Service.rezervare_service import RezervareService
from Service.undo_redo_service import UndoRedoService


class Console:
    def __init__(self, film_service: FilmService,
                 card_client_service: CardClientService,
                 rezervare_service: RezervareService,
                 undo_redo_service: UndoRedoService):
        self.rezervare_service = rezervare_service
        self.card_client_service = card_client_service
        self.film_service = film_service
        self.undo_redo_service = undo_redo_service

    @staticmethod
    def show_menu():
        print("""
        a[film|card|rezervare] - adaugare film, card client sau rezervare
        m[film|card|rezervare] - modificare film, card client sau rezervare
        d[film|card|rezervare] - stergere film, card client sau rezervare
        s[film|card|rezervare|puncte] - afisarea tuturor filmelor, cardurilor, rezervarilor, punctelor de pe card
        live[8] - generare n entitati cu date valide
        c[film|client] - Cautare full text filme si clienti
        o[card|film] - ordonare card client dupa punctele acumulate pe card sau ordonare film dupa nr de rezervari
        sr[rezervare] - afisare rezervari dint-un interval de ore dat
        dz[rezervare] - stergerea tutror rezervarilor dintr-un anumit interval de zile
        i[card] - incrementarea cu o valoare data a tuturor
         clientilor a caror zi de nastere se afla intr-un interval dat
        undo - efectueaza un undo
        redo - efetueaza un redo
        x. iesire
        """)

    def run_console(self):
        while True:
            self.show_menu()
            cmd = input("Introduceti o comanda: ")
            if cmd == "afilm":
                self.handle_add_film()
            elif cmd == "mfilm":
                self.handle_update_film()
            elif cmd == "dfilm":
                self.handle_delete_film()
            elif cmd == "sfilm":
                self.handle_show_all(self.film_service.get_all_film())
            elif cmd == "acard":
                self.handle_add_card()
            elif cmd == "mcard":
                self.handle_update_card()
            elif cmd == "dcard":
                self.handle_delete_card()
            elif cmd == "scard":
                self.handle_show_all(self.card_client_service.get_all_card())
            elif cmd == "arezervare":
                self.handle_add_rezervare()
            elif cmd == "mrezervare":
                self.handle_update_rezervare()
            elif cmd == "drezervare":
                self.handle_delete_rezervare()
            elif cmd == "srezervare":
                self.handle_show_all(self.rezervare_service.get_all_rezervare())
            elif cmd == "spuncte":
                self.handle_show_card_points()
            elif cmd == "live8":
                self.handle_live()
            elif cmd == "cfilm":
                self.handle_search_movie_full_text()
            elif cmd == "ccard":
                self.handle_search_card_full_text()
            elif cmd == "ocard":
                self.handle_show_all(self.card_client_service.get_ordered_descending_by_card_points())
            elif cmd == "ofilm":
                self.handle_order_by_bookings(self.rezervare_service.ordered_movies_by_number_of_bookings())
            elif cmd == "srrezervare":
                self.handle_show_rezervare_by_range_of_hour()
            elif cmd == "dzrezervare":
                self.handle_delete_rezervare_in_range_of_day()
            elif cmd == "icard":
                self.handle_incrementare_puncte()
            elif cmd == "undo":
                self.undo_redo_service.do_undo()
            elif cmd == "redo":
                self.undo_redo_service.de_redo()
            elif cmd == "x":
                break
            else:
                print("Comanda invalida!")

    def handle_add_film(self):
        try:
            id_film = input("Introduceti ID-ul filmului: ")
            titlu = input("Introduceti numele filmului: ")
            an_aparitie = int(input("Introduceti anul de aparatie al filmului: "))
            pret_bilet = float(input("Introduceti pretul biletului: "))
            in_program = int(input("Introduceti 1/0 daca filmul este sau nu in program: "))
            in_program = bool(in_program)
            self.film_service.add_film(id_film, titlu, an_aparitie, pret_bilet, in_program)
        except FilmValidationError as fe:
            print("Eroare de validare: ", fe)
        except DuplicateIdError as de:
            print("ID duplicat: ", de)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_update_film(self):
        try:
            id_film = input("Introduceti ID-ul filmului pe care doriti sa-l modificati: ")
            titlu_new = input("Introduceti noul nume al filmului: ")
            an_aparitie_new = int(input("Introduceti noul an de aparatie al filmului: "))
            pret_bilet_new = float(input("Introduceti noul pret al biletului: "))
            in_program_new = int(input("Introduceti 1/0 daca noul filmul este sau nu in program: "))
            in_program_new = bool(in_program_new)
            self.film_service.update_film(id_film, titlu_new,
                                          an_aparitie_new, pret_bilet_new, in_program_new)
        except FilmValidationError as fe:
            print("Eroare de validare: ", fe)
        except NoSuchIdError as ne:
            print("Eroare de ID: ", ne)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_delete_film(self):
        try:
            id_film = input("Introduceti ID-ul filmului "
                            "pe care doriti sa-l stergeti: ")
            self.film_service.delete_film(id_film)
            self.rezervare_service.stergere_in_cascada_film(id_film)
        except NoSuchIdError as ne:
            print("Eroare de ID: ", ne)
        except Exception as ex:
            print("Eroare: ", ex)

    @staticmethod
    def handle_show_all(objects):
        for obj in objects:
            print(obj)

    def handle_add_card(self):
        try:
            id_card = input("Introduceti ID-ul cardului: ")
            nume = input("Introduceti numele clientului: ")
            prenume = input("Introduceti prenumele clientului: ")
            cnp = int(input("Introduceti CNP-ul clientului: "))
            data_nasterii = input("Introduceti data de nastere a clientului: ")
            data_inregistrarii = input("Introduceti data inregistrarii clientului: ")
            data_nasterii = datetime.strptime(data_nasterii, '%d.%m.%Y').date()
            data_inregistrarii = datetime.strptime(data_inregistrarii, '%d.%m.%Y').date()
            puncte_acumulate = 0
            self.card_client_service.add_card(id_card, nume, prenume,
                                              cnp, data_nasterii, data_inregistrarii, puncte_acumulate)
        except CardValdiationError as ce:
            print("Eroare de validare: ", ce)
        except DuplicateIdError as de:
            print("ID duplicat: ", de)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_update_card(self):
        try:
            id_card = input("Introduceti ID-ul cardului pe care doriti sa-l modificati: ")
            nume = input("Introduceti numele noului client: ")
            prenume = input("Introduceti prenumele noului client: ")
            cnp = int(input("Introduceti CNP-ul noului client: "))
            data_nasterii = input("Introduceti data de nastere a noului client: ")
            data_inregistrarii = input("Introduceti data iregistrarii noului client: ")
            puncte_acumulate_new = 0
            data_nasterii = datetime.strptime(data_nasterii, '%d.%m.%Y').date()
            data_inregistrarii = datetime.strptime(data_inregistrarii,
                                                   "%d.%m.%Y").date()
            self.card_client_service.update_card(id_card, nume, prenume,
                                                 cnp, data_nasterii, data_inregistrarii, puncte_acumulate_new)
            self.card_client_service.update_card(id_card, nume, prenume,
                                                 cnp, data_nasterii, data_inregistrarii, puncte_acumulate_new)
        except CardValdiationError as ce:
            print("Eroare de validare: ", ce)
        except NoSuchIdError as ne:
            print("Eroare de ID: ", ne)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_delete_card(self):
        try:
            id_card = input("Introduceti ID-ul cardului "
                            "pe care doriti sa-l stergeti: ")
            self.card_client_service.delete_card(id_card)
            self.rezervare_service.stergere_in_cascada_card_client(id_card)
        except NoSuchIdError as ne:
            print("Eroare de ID: ", ne)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_add_rezervare(self):
        try:
            id_rezervare = input("Introduceti ID-ul rezervarii: ")
            id_film = input("Introduceti ID-ul filmului: ")
            id_client = input("Introduceti ID-ul cardului client: ")
            data = input("Introduceti data: ")
            ora = input("Introduceti ora: ")
            data = datetime.strptime(data, '%d.%m.%Y').date()
            ora = datetime.strptime(ora, '%H.%M').time()
            self.rezervare_service.add_rezervare(id_rezervare,
                                                 id_film, id_client, data, ora)
        except RezervareValidationError as re:
            print("Eroare de validare: ", re)
        except DuplicateIdError as de:
            print("ID duplicat: ", de)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_update_rezervare(self):
        try:
            id_rezervare = input("Introduceti ID-ul rezervarii pe care doriti sa o modificati: ")
            id_film = input("Introduceti ID-ul noului film: ")
            id_client = input("Introduceti ID-ul noului card client: ")
            data = input("Introduceti noua data: ")
            ora = input("Introduceti noua ora: ")
            data = datetime.strptime(data, '%d.%m.%Y').date()
            ora = datetime.strptime(ora, '%H.%M').time()
            self.rezervare_service.update_rezervare(id_rezervare, id_film,
                                                    id_client, data, ora)
        except RezervareValidationError as re:
            print("Eroare de validare: ", re)
        except NoSuchIdError as ne:
            print("Eroare de ID: ", ne)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_delete_rezervare(self):
        try:
            id_rezervare = input("Introduceti ID-ul rezervarii pe care doriti sa o stergeti: ")
            self.rezervare_service.delete_rezervare(id_rezervare)
        except NoSuchIdError as ne:
            print("Eroare de ID: ", ne)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_show_card_points(self):
        try:
            id_card = input("Introduceti id-ul cardului de la care doriti sa se afiseze punctele: ")
            puncte = self.card_client_service.get_puncte_card(id_card)
            print(f"Clientul cu ID-ul {id_card} are: {puncte}"
                  f" puncte acumulate pe card.")

        except NoSuchIdError as ne:
            print("Eroare de ID: ", ne)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_live(self):
        try:
            n = int(input("introduceti n: "))
            while n:
                self.handle_add_film()
                n -= 1

        except RezervareValidationError as re:
            print("Eroare de validare: ", re)
        except DuplicateIdError as de:
            print("ID duplicat: ", de)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_search_movie_full_text(self):
        try:
            string = input("Cautati...")
            self.handle_show_all(self.rezervare_service.search_movie(string))
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_search_card_full_text(self):
        try:
            string = input("Cautati...")
            self.handle_show_all(self.rezervare_service.search_card(string))
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_show_rezervare_by_range_of_hour(self):
        try:
            ora_start = input("Introduceti ora de inceput:")
            ora_stop = input("introduceti ora de stop: ")
            ora_start = datetime.strptime(ora_start, '%H.%M').time()
            ora_stop = datetime.strptime(ora_stop, '%H.%M').time()
            result_list = self.rezervare_service. \
                rezervari_interval_ore(ora_start, ora_stop)
            self.handle_show_all(result_list)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_order_by_bookings(self, list_movie: list):
        for obj in list_movie:
            print(self.rezervare_service.number_of_bookings_recursiv(obj,
                                                                     self.rezervare_service.get_all_rezervare(),
                                                                     0), obj)

    def handle_delete_rezervare_in_range_of_day(self):
        try:
            day_start = input("Introduceti ziua de start: ")
            day_stop = input("Introduceti ziua de stop: ")
            day_start = datetime.strptime(day_start, "%d.%m.%Y").date()
            day_stop = datetime.strptime(day_stop, "%d.%m.%Y").date()
            self.rezervare_service.stergere_rezervari_interval_zile(day_start, day_stop)
        except Exception as ex:
            print("Eroare: ", ex)

    def handle_incrementare_puncte(self):
        try:
            date_start = input("Introduceti data de start: ")
            date_stop = input("Introduceti data de stop: ")
            date_start = datetime.strptime(date_start, "%d.%m.%Y").date()
            date_stop = datetime.strptime(date_stop, "%d.%m.%Y").date()
            val = int(input("Introduceti valoarea: "))
            self.card_client_service.incrementare_puncte_card(date_start, date_stop, val)
        except Exception as ex:
            print("Eroare: ", ex)
