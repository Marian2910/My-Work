package socialnetwork.controller;


import socialnetwork.service.Service;

public class LoginController {
    Service service;
    @FXML
    private TextField usernameField;

    @FXML
    private TextField parolaField;
    @FXML
    private TextField numeField;
    @FXML
    private TextField prenumeField;


    public void setService(Service service) {
        this.service = service;
    }

    @FXML
    public void handleLoginButtonAction(ActionEvent actionEvent) {
        if(service.conectareUtilizator(usernameField.getText(),parolaField.getText())!=false) {
            try{
                FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/views/utilizatorView.fxml"));
                Parent root = (Parent) fxmlLoader.load();
                Stage stage = new Stage();
                stage.setScene(new Scene(root));
                UserController userController = fxmlLoader.getController();
                userController.setService(service);
                stage.show();
                ((Node)(actionEvent.getSource())).getScene().getWindow().hide();
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
        else{
            MessageAlert.showErrorMessage(null, "There is no user with this username or this password!");
        }
    }

    @FXML
    public void handleSinginButtonAction(ActionEvent actionEvent) {
        if(service.creareUtilizator(numeField.getText(),prenumeField.getText(),emailField.getText(),parolaField.getText())==true) {
            try{
                FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/views/utilizatorView.fxml"));
                Parent root = (Parent) fxmlLoader.load();
                Stage stage = new Stage();
                stage.setScene(new Scene(root));
                UserController userController = fxmlLoader.getController();
                userController.setService(service);
                stage.show();
                ((Node)(actionEvent.getSource())).getScene().getWindow().hide();
            } catch(Exception e) {
                MessageAlert.showErrorMessage(null, e.getMessage());
            }
        }
        else{
            MessageAlert.showErrorMessage(null, "The username is not available!");
        }

    }
}
