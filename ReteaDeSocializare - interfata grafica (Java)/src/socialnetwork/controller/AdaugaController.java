package socialnetwork.controller;

import socialnetwork.domain.User;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.service.Service;
import socialnetwork.utils.events.FriendshipEntityChangeEvent;
import socialnetwork.utils.observer.Observer;

import java.awt.event.ActionEvent;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class AdaugaController implements Observer<FriendshipEntityChangeEvent> {
    Service service;
    @FXML
    public TableView<User> tableView;
    @FXML
    private TableColumn<User, String> usernameColoana;
    @FXML
    public TableColumn<User, String> numeColoana;
    @FXML
    public TableColumn<User,String> prenumeColoana;

    ObservableList<User> model= FXCollections.observableArrayList();

    public void setService(Service service) {
        this.service = service;
        initModel();
        service.addObserver(this);
    }

    @FXML
    public void initialize() {
        usernameColoana.setCellValueFactory(new PropertyValueFactory<User, String>("email"));
        numeColoana.setCellValueFactory(new PropertyValueFactory<User, String>("nume"));
        prenumeColoana.setCellValueFactory(new PropertyValueFactory<User, String>("prenume"));
        tableView.setItems(model);
    }
    private void initModel() {
        Iterable<User> allUsers = service.getUsersNotFriends();
        List<User> users = StreamSupport.stream(allUsers.spliterator(), false)
                .collect(Collectors.toList());
        model.setAll(users);
    }

    @Override
    public void update(FriendshipEntityChangeEvent friendshipEntityChangeEvent) {
        initModel();
    }

    public void handleAdauga(ActionEvent actionEvent) {

        try {
            User selected = tableView.getSelectionModel().getSelectedItem();
            String id = selected.getId();
            service.sendRequest(id);
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "INFO", "The request has been submitted!");
        }catch(ValidationException e){
            MessageAlert.showErrorMessage(null, e.getMessage());
        }

    }
}
