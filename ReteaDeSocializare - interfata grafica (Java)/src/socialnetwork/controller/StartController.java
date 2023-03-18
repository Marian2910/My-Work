package socialnetwork.controller;


import socialnetwork.HelloApplication;
import socialnetwork.service.Service;

import java.awt.event.ActionEvent;

public class StartController {
    Service service;

    public void setService(Service service) {
        this.service = service;
    }
    @FXML
    public void handleLoginButtonAction(ActionEvent actionEvent){
        try{
            FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/views/loginView.fxml"));
            Parent root = (Parent) fxmlLoader.load();
            Stage stage = new Stage();
            stage.setScene(new Scene(root));
            stage.setTitle("LOGIN PAGE");
            LoginController loginController = fxmlLoader.getController();

            loginController.setService(service);
            stage.show();
            ((Node)(actionEvent.getSource())).getScene().getWindow().hide();
        } catch(Exception e) {
            e.printStackTrace();
        }

    }

    @FXML
    public void handleSinginButtonAction(ActionEvent actionEvent){
        try{
            FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/views/singinView.fxml"));
            Parent root = (Parent) fxmlLoader.load();
            Stage stage = new Stage();
            stage.setScene(new Scene(root));
            stage.setTitle("SIGN IN PAGE");
            LoginController loginController = fxmlLoader.getController();

            loginController.setService(service);
            stage.show();
            ((Node)(actionEvent.getSource())).getScene().getWindow().hide(); //ca sa ascunda prima fereastra
        } catch(Exception e) {
            e.printStackTrace();
        }

    }
}
