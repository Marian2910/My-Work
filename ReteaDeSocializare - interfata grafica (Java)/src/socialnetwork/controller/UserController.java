package socialnetwork.controller;


import socialnetwork.HelloApplication;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.service.Service;
import socialnetwork.utils.events.FriendshipEntityChangeEvent;

import javax.swing.table.TableColumn;
import javax.swing.text.TableView;
import java.awt.event.ActionEvent;
import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UserController implements Observer<FriendshipEntityChangeEvent> {
    Service service;
    ObservableList<User> model= FXCollections.observableArrayList();

    @FXML
    public TableView<User> tableView;
    @FXML
    private TableColumn<User, String> emailColoana;
    @FXML
    public TableColumn<User, String> numeColoana;
    @FXML
    public TableColumn<User,String> prenumeColoana;

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
        Iterable<User> allUsers = service.obtineUtilizatoriPrieteni();
        List<User> users = StreamSupport.stream(allUsers.spliterator(), false)
                .collect(Collectors.toList());
        model.setAll(users);
    }

    //pt Observers
    @Override
    public void update(FriendshipEntityChangeEvent friendshipEntityChangeEvent) {
        initModel();
    }

    public void handleSterge(ActionEvent actionEvent) {
        try{
            String id1= service.getIdCurent();
            User selected= tableView.getSelectionModel().getSelectedItem();
            String id2= selected.getId();
            service.deleteFriend(id1, id2);
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "INFO", "The friendship has been deleted successfully!");
            //initModel();
        }catch (ValidationException e){
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

    public void handleAdauga(ActionEvent actionEvent) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/views/adaugaView.fxml"));
        Parent root = (Parent) fxmlLoader.load();
        Stage stage = new Stage();
        stage.setScene(new Scene(root));
        stage.setTitle("ADAUGA PAGE");
        AdaugaController adaugaController = fxmlLoader.getController();

        adaugaController.setService(service);
        stage.show();
    }

    public void handleAccepta(ActionEvent actionEvent) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/views/acceptaView.fxml"));
        Parent root = (Parent) fxmlLoader.load();
        Stage stage = new Stage();
        stage.setScene(new Scene(root));
        stage.setTitle("ACCEPTA PAGE");
        AcceptaController acceptaController = fxmlLoader.getController();

        acceptaController.setService(service);
        stage.show();
    }

    public void handleLogout(ActionEvent actionEvent) throws IOException {
        service.userLogOut();
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/views/startView.fxml"));
        Parent root = (Parent) fxmlLoader.load();
        Stage stage = new Stage();
        stage.setScene(new Scene(root));
        stage.setTitle("START PAGE");
        StartController startController = fxmlLoader.getController();

        startController.setService(service);
        stage.show();
        ((Node)(actionEvent.getSource())).getScene().getWindow().hide();
    }
}
