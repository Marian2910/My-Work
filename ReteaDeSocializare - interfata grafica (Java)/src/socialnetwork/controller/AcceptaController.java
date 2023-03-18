package socialnetwork.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import socialnetwork.domain.User;
import socialnetwork.service.Service;
import socialnetwork.utils.events.FriendshipEntityChangeEvent;

import java.awt.event.ActionEvent;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class AcceptaController implements Observer<FriendshipEntityChangeEvent> {
    Service service;
    @FXML
    public TableView<User> tableView;
    @FXML
    private TableColumn<User, String> emailColoana;
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
        emailColoana.setCellValueFactory(new PropertyValueFactory<User, String>("username"));
        numeColoana.setCellValueFactory(new PropertyValueFactory<User, String>("nume"));
        prenumeColoana.setCellValueFactory(new PropertyValueFactory<User, String>("prenume"));
        tableView.setItems(model);
    }
    private void initModel() {
        Iterable<User> allUsers = service.obtineUtilizatoriCereri();
        List<User> users = StreamSupport.stream(allUsers.spliterator(), false)
                .collect(Collectors.toList());
        model.setAll(users);
    }
    @Override
    public void update(FriendshipEntityChangeEvent friendshipEntityChangeEvent) {
        initModel();
    }

    public void handleAccepta(ActionEvent actionEvent) {
            User selected = tableView.getSelectionModel().getSelectedItem();
            String id = selected.getId();
            service.acceptRequest(id);
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "INFO", "The request has been accepted successfully!");

    }
}
