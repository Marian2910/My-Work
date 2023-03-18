package socialnetwork;

import javafx.application.Application;
import socialnetwork.controller.StartController;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.repository.database.FriendshipDBRepository;
import socialnetwork.repository.database.UserDbRepository;
import socialnetwork.service.Service;

import java.io.IOException;

public class HelloApplication extends Application {
    Service service;

    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage primaryStage) throws IOException {

        repository.Repository<String, User> userRepository = new UserDbRepository("jdbc:postgresql://localhost:5432/UP","postgres","482655");
        repository.Repository<String, Friendship> friendshipRepository = new FriendshipDBRepository("jdbc:postgresql://localhost:5432/UP","postgres","482655");
        this.service = new Service(userRepository, friendshipRepository);

        primaryStage.setTitle("START PAGE");
        startView(primaryStage);
        primaryStage.show();
    }

    private void startView(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/views/startView.fxml"));
        AnchorPane Layout = fxmlLoader.load();
        stage.setScene(new Scene(Layout));

        StartController startController = fxmlLoader.getController();
        startController.setService(service);
    }
}
